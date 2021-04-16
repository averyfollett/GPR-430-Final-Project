// Fill out your copyright notice in the Description page of Project Settings.


#include "PanCamera.h"

#include "Kismet/GameplayStatics.h"

void APanCamera::BeginPlay()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->
		SetViewTargetWithBlend(this, 0.0f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f);

	TargetLocation = GetActorLocation();
	TargetRotation = GetActorRotation();
}

void APanCamera::Tick(float DeltaSeconds)
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->
        SetViewTargetWithBlend(this, 0.0f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f);

	if (!TargetLocation.Equals(GetActorLocation(), 0.1f))
	{
		SetActorLocationAndRotation(FMath::Lerp(GetActorLocation(), TargetLocation, Speed), FRotator::ZeroRotator);
	}
}
