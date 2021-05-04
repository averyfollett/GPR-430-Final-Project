// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Powerable.h"
#include "PowerableSpotLight.h"
#include "GameFramework/Actor.h"
#include "SlidingDoor.generated.h"

UCLASS()
class GENERATORTEST_API ASlidingDoor final : public AActor, public IPowerable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlidingDoor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* LeftDoor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* RightDoor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* LeftDoorInverted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* RightDoorInverted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APowerableSpotLight*> LightArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void ActivateLights();

	virtual void SetPowered(bool IsPowered, FGuid SetterID) override;

	UFUNCTION(NetMulticast, Reliable)
	void MoveDoors();
	UFUNCTION(BlueprintImplementableEvent)
	void MoveLeftDoor();
	UFUNCTION(BlueprintImplementableEvent)
	void MoveRightDoor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LeftDoorStart = FVector(0, 50, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LeftDoorEnd = FVector(0, 150, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RightDoorStart = FVector(0, 0, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RightDoorEnd = FVector(0, -150, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LeftDoorInvertedStart = FVector(-80, 50, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LeftDoorInvertedEnd = FVector(-80, 150, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RightDoorInvertedStart = FVector(-80, 0, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RightDoorInvertedEnd = FVector(-80, -150, 0);

	UPROPERTY()
	FGuid ThisGuid;
};
