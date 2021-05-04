// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatUIWidget.h"
#include "Components/MultiLineEditableText.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/Text/SMultiLineEditableText.h"
#include "ArcticCharacter.h"

void UChatUIWidget::OpenCloseChat(ESlateVisibility isVisible)
{
	//MultiLineTextBox->SetVisibility(isVisible);
}

//FReply UChatUIWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
//{
//	if(InKeyEvent.GetKey() == EKeys().Enter)
//	{
//		FString text = MultiLineTextBox->GetText().ToString();
//
//		Player->PlayerOpenCloseChat();
//
//		FString playerNum = FString::FromInt(Player->PlayerID);
//		Player->UseChat(playerNum, text);
//
//		//MultiLineTextBox->SetText();
//
//		return true;
//	}
//
//	return false;
//}


void UChatUIWidget::BeginPlay()
{
	//ChatInstance = Cast<UNWGameInstance>(GetWorld()->GetGameInstance())->GetChatUI();
	Player = Cast<AArcticCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if(UGameplayStatics::GetPlayerController(GetWorld(), 0)->IsLocalController())
	{
		
	}
}
