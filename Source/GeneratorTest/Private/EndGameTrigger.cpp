// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameTrigger.h"

#include "ArcticCharacter.h"
#include "NWGameInstance.h"

// Sets default values
AEndGameTrigger::AEndGameTrigger()
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AEndGameTrigger::TriggerOverlap);
}

void AEndGameTrigger::TriggerOverlap(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AArcticCharacter::StaticClass()))
	{
		ServerEndGame();
	}
}

void AEndGameTrigger::ServerEndGame_Implementation()
{
	Cast<UNWGameInstance>(GetWorld()->GetGameInstance())->DestroySessionAndLeaveGame();
}
