// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraTrigger.h"

#include "ArcticCharacter.h"
#include "PanCamera.h"
#include "Kismet/GameplayStatics.h"

ACameraTrigger::ACameraTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ACameraTrigger::ActorBeginOverlap);
}

void ACameraTrigger::ActorBeginOverlap(AActor* Actor, AActor* OtherActor)
{
	AArcticCharacter* OverlapActor = Cast<AArcticCharacter>(OtherActor);
	AArcticCharacter* Player = Cast<AArcticCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if (IsValid(OverlapActor) && IsValid(Player))
	{
		if (OverlapActor == Player)
		{
			APanCamera* PanCamera = Cast<APanCamera>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewTarget());

			PanCamera->SetTargetLocation(PlaceholderCamera->GetActorLocation());
		}
	}
}
