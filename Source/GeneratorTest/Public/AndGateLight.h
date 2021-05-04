// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Powerable.h"
#include "Engine/StaticMeshActor.h"
#include "AndGateLight.generated.h"

/**
 * 
 */
UCLASS()
class GENERATORTEST_API AAndGateLight : public AStaticMeshActor, public IPowerable
{
	GENERATED_BODY()

	AAndGateLight();

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> NextPowerables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bStayPowered = true;

protected:
	UFUNCTION()
	void SetAppearance(bool Powered) const;

	UFUNCTION()
	void PowerNext(bool PowerState);

	virtual void SetPowered(bool IsPowered, FGuid SetterID) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGuid, bool> PowerStateOfInputs;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
	FGuid ThisGuid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance* LightMaterialInstance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInstanceDynamic* DynamicMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PowerDelay = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsPowered = false;
	UPROPERTY()
	bool bHasFinishedSetup = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bWasPowered = false;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
