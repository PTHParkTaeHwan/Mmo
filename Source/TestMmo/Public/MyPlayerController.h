// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TestMmo.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class TESTMMO_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();

	UFUNCTION(Reliable, Server, WithValidation)
	void WidgetSpawn();
	void WidgetSpawn_Implementation();
	bool WidgetSpawn_Validate();

	UFUNCTION(Reliable, NetMulticast, WithValidation)
	void WidgetSpawnNetMulticast();
	void WidgetSpawnNetMulticast_Implementation();
	bool WidgetSpawnNetMulticast_Validate();


protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UChatWidget> HUDChatWidgetClass;

private:
	UPROPERTY()
	class UChatWidget* HUDChatWidget;

	void OnChatPause();

	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;

	bool bChatMode;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UMessageWidget> MessageWidgetClass;

	UPROPERTY()
	class UMessageWidget* MessageWidget;
};
