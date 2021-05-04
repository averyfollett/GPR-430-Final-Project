// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Powerable.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "GameFramework/Actor.h"
#include "SplineWire.generated.h"

UCLASS()
class GENERATORTEST_API ASplineWire final : public AActor, public IPowerable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineWire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* SplineWireComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(NetMulticast, Reliable)
	void SetAppearance(bool Powered);

	UFUNCTION()
	void SetPowerNext(bool Powered);

	virtual void SetPowered(bool IsPowered, FGuid SetterID) override;
	virtual FGuid GetGUID() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	bool bIsPowered = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> NextPowerable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SetNextDelay = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsForward = true;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	FGuid ThisGuid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UMaterialInstanceDynamic*> DynamicMaterials;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* CurrentMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int I = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USplineMeshComponent*> SplineMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSetupDone = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* WireMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance* WireMaterialInstance;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
