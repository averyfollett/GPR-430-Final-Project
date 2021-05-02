// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Generator.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GeneratorOutlet.generated.h"

UCLASS()
class GENERATORTEST_API AGeneratorOutlet final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneratorOutlet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* OutletBase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* OutletTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* TriggerBox;

	UFUNCTION()
	void GeneratorPickedUp();

	UFUNCTION()
	void SnapGeneratorToCenter(AGenerator* Generator);

	UFUNCTION()
	void ActorOverlapped(AActor* Self, AActor* OtherActor);
	UFUNCTION()
	void ActorOverlapEnded(AActor* Self, AActor* OtherActor);

	UPROPERTY(EditAnywhere)
	bool bIsPressed = false;
	UPROPERTY(EditAnywhere)
	bool bStaysPressed = false;

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
