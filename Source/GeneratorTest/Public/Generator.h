// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/PointLight.h"
#include "GameFramework/Character.h"
#include "Generator.generated.h"

class AArcticCharacter;

UCLASS()
class GENERATORTEST_API AGenerator : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerator();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPointLightComponent* PointLightComponent;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	int SetHeldBy(AArcticCharacter* Character = nullptr);

	UFUNCTION(NetMulticast, Reliable)
	void SetIsPickedUp(bool bPickUp);

	UPROPERTY(EditAnywhere, Replicated)
	bool bIsHeld = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Replicated)
	AArcticCharacter* HeldBy;

	UPROPERTY(EditAnywhere)
	bool bBeingPlaced = false;

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const override;
};
