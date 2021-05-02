// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Powerable.h"
#include "WireInterface.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMeshActor.h"
#include "RotatingWire.generated.h"

/**
 * 
 */
UCLASS()
class GENERATORTEST_API ARotatingWire : public AStaticMeshActor, public IWireInterface, public IPowerable
{
	GENERATED_BODY()

	ARotatingWire();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* WireMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BaseComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<AActor*, AActor*> InputsAndOutputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* FirstPowerSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<float, AActor*> AnglesToInputs;

protected:
	virtual void BeginPlay() override;
	
	virtual void RotateWire() override;

	virtual void SetPowered(bool IsPowered, FGuid SetterID) override;

	UFUNCTION()
	void SetNextPowered(bool Powered, FGuid PowerSource);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGuid ThisGuid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Delay = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGuid, AActor*> InputIdToOutput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGuid CurrentPowerSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> AngleList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentAngleIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGuid, bool> LastReportedPowerState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Wire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInstanceDynamic* WireMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator StartingRotation;
};
