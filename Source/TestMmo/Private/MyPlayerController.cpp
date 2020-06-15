// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Components/WidgetComponent.h"
#include "ChatWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "MessageWidget.h"



AMyPlayerController::AMyPlayerController()
{
	
	static ConstructorHelpers::FClassFinder<UChatWidget> UI_CHAT_C(TEXT("WidgetBlueprint'/Game/Dev/HUDWidget.HUDWidget_C'"));
	if (UI_CHAT_C.Succeeded())
	{
		HUDChatWidgetClass = UI_CHAT_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UMessageWidget> UI_MESSAGE_C(TEXT("/Game/Dev/Message.Message_C"));
	if (UI_MESSAGE_C.Succeeded())
	{
		MessageWidgetClass = UI_MESSAGE_C.Class;
	}

}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("Chat"), EInputEvent::IE_Pressed, this, &AMyPlayerController::OnChatPause);

}


void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//WidgetSpawn();	
	//HUDChatWidget = CreateWidget<UChatWidget>(this, HUDChatWidgetClass);
	//HUDChatWidget->AddToViewport();

}

void AMyPlayerController::WidgetSpawn_Implementation()
{
	if (HasAuthority())
	{
		WidgetSpawnNetMulticast();
	}
}

bool AMyPlayerController::WidgetSpawn_Validate()
{
	return true;
}

void AMyPlayerController::WidgetSpawnNetMulticast_Implementation()
{
	//if (HUDChatWidgetClass == nullptr)
		//TLOG(Warning, TEXT("HUDChatWidgetClass == nullptr"));
	//HUDChatWidget = CreateWidget<UChatWidget>(this, HUDChatWidgetClass);
	//HUDChatWidget->AddToViewport();
}

bool AMyPlayerController::WidgetSpawnNetMulticast_Validate()
{
	return true;
}

void AMyPlayerController::OnChatPause()
{
	HUDChatWidget = CreateWidget<UChatWidget>(this, HUDChatWidgetClass);
	HUDChatWidget->AddToViewport(3);
	SetInputMode(UIInputMode);
	bShowMouseCursor = true;

	MessageWidget = CreateWidget<UMessageWidget>(this, MessageWidgetClass);
	MessageWidget->AddToViewport(3);


}
