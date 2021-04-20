// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "PanCamera.generated.h"

/**
 * 
 */
UCLASS()
class GENERATORTEST_API APanCamera : public ACameraActor
{
	GENERATED_BODY()

	APanCamera();

	UFUNCTION()
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void Tick(float DeltaSeconds) override;
	
public:
	UFUNCTION()
	void SetTargetLocation(const FVector NewLocation) { TargetLocation = NewLocation; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 0.05f;
	
protected:
	UPROPERTY()
	FVector TargetLocation;
	UPROPERTY()
	FRotator TargetRotation;
	
};
