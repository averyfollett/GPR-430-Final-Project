// Fill out your copyright notice in the Description page of Project Settings.


#include "PanCamera.h"


#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

APanCamera::APanCamera()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCameraComponent()->SetWorldRotation(FRotator(-40.0f, -90.0f, 0.0f));
}

void APanCamera::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->
		SetViewTargetWithBlend(this, 0.0f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f);

	TargetLocation = GetActorLocation();
	TargetRotation = GetActorRotation();
}

void APanCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->
        SetViewTargetWithBlend(this, 0.0f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f);

	if (!TargetLocation.Equals(GetActorLocation(), 0.1f))
	{
		UE_LOG(LogTemp, Log, TEXT("Moving Camera"));
		SetActorLocationAndRotation(FMath::Lerp(GetActorLocation(), TargetLocation, Speed), FRotator::ZeroRotator);
	}
}
