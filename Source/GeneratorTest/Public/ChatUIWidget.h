// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class GENERATORTEST_API UChatUIWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
	class AArcticCharacter* Player;

	void BeginPlay();

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OpenCloseChat(ESlateVisibility IsVisible);
	
};
