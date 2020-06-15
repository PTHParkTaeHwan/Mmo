// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstCharacter.h"
#include "CoreTypes.h"
#include <SpawnMine.h>
#include "Components/WidgetComponent.h"
#include "Components/TextRenderComponent.h"
#include "Animation/SkeletalMeshActor.h"
#include "MessageWidget.h"


// Sets default values
AFirstCharacter::AFirstCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//스켈레탈메시 설정
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CardBoard(TEXT("SkeletalMesh'/Game/ParagonShinbi/Characters/Heroes/Shinbi/Meshes/Shinbi.Shinbi'"));
	if (CardBoard.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CardBoard.Object);
	}
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> PlayerAnim(TEXT("AnimBlueprint'/Game/ParagonShinbi/Characters/Heroes/Shinbi/Shinbi_AnimBlueprint.Shinbi_AnimBlueprint_C'"));
	if (PlayerAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PlayerAnim.Class);
	}

	//카메라 설정
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	SpringArm->TargetArmLength = 410.0f;
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	//TestEffect
	TestEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SKILL_1"));
	TestEffect->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_SKILL_1(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Ambient/Fire/P_Fire_largeArea_Trans_mobile.P_Fire_largeArea_Trans_mobile'"));
	if (P_SKILL_1.Succeeded())
	{
		TestEffect->SetTemplate(P_SKILL_1.Object);
		TestEffect->bAutoActivate = false;
	}
	TestEffect->SetIsReplicated(true);

	/*ChattingWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("CHATTINGWIDGETT"));
	ChattingWidget->SetupAttachment(GetMesh());
	ChattingWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	ChattingWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_CHAT(TEXT("/Game/Dev/Chatting.Chatting_C"));
	if (UI_CHAT.Succeeded())
	{
		ChattingWidget->SetWidgetClass(UI_CHAT.Class);
		ChattingWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}
	ChattingWidget->SetHiddenInGame(false);*/

	ChatText = CreateDefaultSubobject<UTextRenderComponent>("ChatText");
	ChatText->SetRelativeLocation(FVector(0, 0, 100));
	ChatText->SetHorizontalAlignment(EHTA_Center);
	ChatText->SetupAttachment(RootComponent);


	/*MessageWidget = CreateDefaultSubobject<UMessageWidget>(TEXT("MESSAGEWIDGET"));
	static ConstructorHelpers::FClassFinder<UMessageWidget> UI_MESSAGE_C(TEXT("/Game/Dev/Message.Message_C"));
	if (UI_MESSAGE_C.Succeeded())
	{
		MessageWidgetClass = UI_MESSAGE_C.Class;
	}*/

}


// Called when the game starts or when spawned
void AFirstCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentMessage = "";	
}

// Called every frame
void AFirstCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFirstCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AFirstCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AFirstCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AFirstCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AFirstCharacter::Turn);
	PlayerInputComponent->BindAction(TEXT("Bomb"), EInputEvent::IE_Pressed, this, &AFirstCharacter::Bomb);
	

}
//캐릭터 움직임
void AFirstCharacter::UpDown(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
}
void AFirstCharacter::LeftRight(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
}
//카메라 움직임
void AFirstCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}
void AFirstCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}
//스폰
void AFirstCharacter::Bomb()
{
	ServerSpawn();

	if (HasAuthority())
	{
		ServerSpawn();
	}
}

void AFirstCharacter::ServerSpawn_Implementation()
{
	if (HasAuthority())
	{
		//ServerSpawn();
		ServerSpawnNetMulticast();
		TLOG(Warning, TEXT("bomb"));
	}
}

bool AFirstCharacter::ServerSpawn_Validate()
{
	return true;
}

void AFirstCharacter::ServerSpawnNetMulticast_Implementation()
{
	TestEffect->Activate(true);
}

bool AFirstCharacter::ServerSpawnNetMulticast_Validate()
{
	return true;
}


void AFirstCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFirstCharacter, CurrentMessage);
}


void AFirstCharacter::SendChatMessage(const FString& Message)
{
	CurrentMessage = Message;
	UpdateChatText();

	FTimerHandle DummyHandle;
	GetWorldTimerManager().SetTimer(DummyHandle, this, &AFirstCharacter::ChearChatMessage, 5.f);
}

void AFirstCharacter::AttemptToSendChatMessage(const FString& Message)
{
	TLOG(Warning, TEXT("AttemptToSendChatMessage"));
	if (!HasAuthority())
	{
		SeverSendChatMessage(Message);
	}
	else SendChatMessage(Message);
}


void AFirstCharacter::SeverSendChatMessage_Implementation(const FString& Message)
{
	SendChatMessage(Message);
}
bool AFirstCharacter::SeverSendChatMessage_Validate(const FString& Message)
{
	if (Message.Len() < 255)
	{
		return true;
	}
	else return false;
}

void AFirstCharacter::SeverSendChatMessage2_Implementation(const FString& Message)
{
	ServerChatMessageMulticast(Message);
}
bool AFirstCharacter::SeverSendChatMessage2_Validate(const FString& Message)
{
	if (Message.Len() < 255)
	{
		return true;
	}
	else return false;
}

void AFirstCharacter::ServerChatMessageMulticast_Implementation(const FString& Message)
{
	/*for (TActorIterator<AFirstCharacter> It(GetWorld()); It; ++It)
	{
		
	}
	*/

	//MessageWidget = CreateWidget<UMessageWidget>(GetController(), MessageWidgetClass);
	//MessageWidget->AddToViewport(3);
	//MessageWidget->SetMessage(GetName() ,Message);


}

bool AFirstCharacter::ServerChatMessageMulticast_Validate(const FString& Message)
{
	if (Message.Len() < 255)
	{
		return true;
	}
	else return false;
}


void AFirstCharacter::OnRep_CurrentMessage()
{
	UpdateChatText();
}

void AFirstCharacter::ChearChatMessage()
{
	CurrentMessage = "";
	UpdateChatText();
}

void AFirstCharacter::UpdateChatText()
{
	ChatText->SetText(FText::FromString(CurrentMessage));
}