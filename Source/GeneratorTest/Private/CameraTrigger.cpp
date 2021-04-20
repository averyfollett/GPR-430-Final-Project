// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraTrigger.h"

#include "ArcticCharacter.h"
#include "PanCamera.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ACameraTrigger::ACameraTrigger()
{
	//OnActorBeginOverlap.AddDynamic(this, &ACameraTrigger::ActorBeginOverlap);
}

/*void ACameraTrigger::ActorBeginOverlap(AActor* Actor, AActor* OtherActor)
{
	AArcticCharacter* OverlapActor = Cast<AArcticCharacter>(OtherActor);
	AArcticCharacter* Player = Cast<AArcticCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if (IsValid(OverlapActor) && IsValid(Player) && IsValid(PlaceholderCamera))
	{
		if (OverlapActor == Player)
		{
			APanCamera* PanCamera = Cast<APanCamera>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewTarget());

			PanCamera->SetTargetLocation(PlaceholderCamera->GetActorLocation());
		}
	}
}*/

void ACameraTrigger::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
    bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	
}

void ACameraTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AArcticCharacter* OverlapActor = Cast<AArcticCharacter>(OtherActor);
	AArcticCharacter* Player = Cast<AArcticCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if (IsValid(OverlapActor) && IsValid(Player) && IsValid(PlaceholderCamera))
	{
		if (OverlapActor == Player)
		{
			UE_LOG(LogTemp, Log, TEXT("Camera trigger activated"));
			
			APanCamera* PanCamera = Cast<APanCamera>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewTarget());

			PanCamera->SetTargetLocation(PlaceholderCamera->GetActorLocation());
		}
	}
}
