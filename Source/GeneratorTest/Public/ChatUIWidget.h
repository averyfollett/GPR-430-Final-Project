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
	
	class AArcticCharacter* Player;
	

	//UPROPERTY(meta = (BindWidget))
	//class UMultiLineEditableText* MultiLineTextBox;

	void BeginPlay();

	public:
	UFUNCTION(BlueprintImplementableEvent)
	void OpenCloseChat(ESlateVisibility IsVisible);

	//virtual FEventReply OnPreviewKeyDown(FGeometry InGeometry, FKeyEvent InKeyEvent) override;
	
};
