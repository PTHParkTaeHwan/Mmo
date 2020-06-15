// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TestMmo.h"
//#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "FirstCharacter.generated.h"

class ASpawnMine;

UCLASS()
class TESTMMO_API AFirstCharacter : public ACharacter
{
	GENERATED_BODY()
	
	//==============
	//  함수 선언  //
	//==============

public:
	// Sets default values for this character's properties
	AFirstCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	//캐릭터 움직임
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	
	//카메라 움직임
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);

	//스폰
	void Bomb();

	//chat
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	
	UPROPERTY(EditAnywhere, Category = Fonts)
	class UTextRenderComponent* ChatText;
private:

	void SendChatMessage(const FString& Message);

	UFUNCTION(BlueprintCallable, Category = "Chat")
	void AttemptToSendChatMessage(const FString& Message);
	
	UFUNCTION(Reliable, Server, WithValidation)
	void SeverSendChatMessage(const FString& Message);
	void SeverSendChatMessage_Implementation(const FString& Message);
	bool SeverSendChatMessage_Validate(const FString& Message);
	
	UFUNCTION(Reliable, Server, WithValidation)
	void SeverSendChatMessage2(const FString& Message);
	void SeverSendChatMessage2_Implementation(const FString& Message);
	bool SeverSendChatMessage2_Validate(const FString& Message);

	UFUNCTION(Reliable, NetMulticast, WithValidation)
	void ServerChatMessageMulticast(const FString& Message);
	void ServerChatMessageMulticast_Implementation(const FString& Message);
	bool ServerChatMessageMulticast_Validate(const FString& Message);

	void CreatMessageWidget();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UMessageWidget> MessageWidgetClass;

	UPROPERTY()
	class UMessageWidget* MessageWidget;



	UFUNCTION()
	void OnRep_CurrentMessage();

	void ChearChatMessage();
	void UpdateChatText();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Transient, ReplicatedUsing = OnRep_CurrentMessage, Category = "Chat")
	FString CurrentMessage;

	//==============
	//  변수 선언  //
	//==============
public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(EditInstanceOnly, Category = Skill)
	TSubclassOf<ASpawnMine> MineClass;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* TestEffect;

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSpawn();
	void ServerSpawn_Implementation();
	bool ServerSpawn_Validate();

	UFUNCTION(Reliable, NetMulticast, WithValidation)
	void ServerSpawnNetMulticast();
	void ServerSpawnNetMulticast_Implementation();
	bool ServerSpawnNetMulticast_Validate();

	/*UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* ChattingWidget;*/


private:
	ASpawnMine* Mine;


};
