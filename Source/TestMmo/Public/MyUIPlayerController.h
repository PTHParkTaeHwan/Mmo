﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyUIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TESTMMO_API AMyUIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
protected:
	virtual void BeginPlay() override;
	
	/*UPROPERTY(EditDefaultsOnly, BlueprintReadwrite, Category = UI)
	TSubclassOf<class UUserWidget> UIWidgetClass;*/

	/*UPROPERTY()
	class UUserWidget* UIWidgetInstance;*/

};
