// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TestMmo.h"
#include "Blueprint/UserWidget.h"
#include "MessageWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTMMO_API UMessageWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void SetMessage(const FString& PlayerName, const FString MessageText);

private:


};
