// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Generator.h"
#include "GameFramework/Actor.h"
#include "GeneratorOutlet.generated.h"

UCLASS()
class GENERATORTEST_API AGeneratorOutlet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneratorOutlet();

	UFUNCTION()
	void GeneratorPickedUp();

	UFUNCTION()
	void SnapGeneratorToCenter(AGenerator* Generator);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void SetListPowerState(bool bIsPowered);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> PoweredObjects;

	UPROPERTY()
	FGuid ThisGuid;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UParticleSystem* SparksParticles;

	UFUNCTION()
	void ChangeToGreen() const;
	UFUNCTION()
	void ChangeToRed() const;

	UPROPERTY()
	UMaterialInstanceDynamic* GeneratorOutletMaterial;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
