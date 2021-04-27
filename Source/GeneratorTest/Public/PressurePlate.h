// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Powerable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

UCLASS()
class GENERATORTEST_API APressurePlate : public AActor, public IPowerable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePlate();

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ButtonBase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ButtonTop;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTriggerOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	UFUNCTION()
	void EndTriggerOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex);

	virtual void SetPowered(bool IsPowered, FGuid SetterID) override;

	UFUNCTION()
	void SetNextPowered(bool bPowered);

	UFUNCTION(BlueprintImplementableEvent)
	void AnimatePressed();
	UFUNCTION(BlueprintImplementableEvent)
	void AnimateUnpressed();

	UFUNCTION()
	void ChangeColor(FLinearColor Color) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid ThisGuid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<AActor*> CurrentlyPressedBy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* BottomMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* TopMaterial;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPressed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bStaysPressed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> NextPowerables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Delay = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPowered = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector PressurePlateStart = FVector(0.0f, 0.0f, 15.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector PressurePlateEnd = FVector(0.0f, 0.0f, 0.0f);
};
