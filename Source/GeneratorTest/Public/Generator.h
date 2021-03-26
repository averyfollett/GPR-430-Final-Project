// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Generator.generated.h"

class AArcticCharacter;

UCLASS()
class GENERATORTEST_API AGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerator();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	int SetHeldBy(TSubclassOf<AArcticCharacter> Character);

	UFUNCTION()
	int SetIsPickedUp(bool bPickUp);

	UPROPERTY(EditAnywhere)
	bool bIsHeld = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AArcticCharacter> HeldBy;

	UPROPERTY(EditAnywhere)
	bool bBeingPlaced = false;
};
