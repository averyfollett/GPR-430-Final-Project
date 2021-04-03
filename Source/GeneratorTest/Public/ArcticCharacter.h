// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "ArcticCharacter.generated.h"

class AGenerator;
class UPhysicsHandleComponent;

UCLASS()
class GENERATORTEST_API AArcticCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AArcticCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	int GeneratorStolen();

	UPROPERTY(EditAnywhere)
	USceneComponent* GrabLocation;

	UPROPERTY(EditAnywhere)
	UArrowComponent* ForwardArrow;

	UPROPERTY(EditAnywhere)
	UPhysicsHandleComponent* PhysicsHandle;

	UPROPERTY(EditAnywhere)
	float PickupRadius = 200.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	int SpawnCamera();

	UFUNCTION()
	int Client_UpdateColor();

	UFUNCTION()
	int SetTerrainBasedOnLevel();

	UFUNCTION()
	int Drop();
	UFUNCTION()
	int PickUp();

	UFUNCTION()
	int PlayerReleaseGenerator();

	UFUNCTION()
	void TryRotateWire();

	UFUNCTION()
	void RotateToGenerator();

	UFUNCTION()
	void AttachGenerator();

	UFUNCTION()
	void SetCameraLocation(FVector Location);

	UFUNCTION()
	void InputAxisTurnRate(float Value);
	UFUNCTION()
	void InputAxisLookUpRate(float Value);
	UFUNCTION()
	void InputAxisMoveForward(float Value);
	UFUNCTION()
	void InputAxisMoveRight(float Value);
	UFUNCTION()
	void InputActionInteractPressed();
	UFUNCTION()
	void InputActionInteractReleased();

	UPROPERTY(EditDefaultsOnly)
	float BaseTurnRate = 45.0f;
	UPROPERTY(EditDefaultsOnly)
	float BaseLookUpRate = 45.0f;

	UPROPERTY(EditAnywhere)
	bool bIsHoldingObject = false;

	UPROPERTY(EditAnywhere)
	float PlayerReachDistance = 200.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGenerator> Generator;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> IgnoreActorArray;

	UPROPERTY(EditAnywhere)
	bool bIsReachingForGenerator = false;

	UPROPERTY(EditAnywhere)
	bool bSwitchReachAnim = false;

	UPROPERTY(EditAnywhere)
	bool bGeneratorInHand = false;

	UPROPERTY(EditAnywhere)
	bool bExtendArms = false;

	UPROPERTY(EditAnywhere)
	bool bLeanForward;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACameraActor> OwnedCamera;

	UPROPERTY(EditAnywhere)
	bool bIsPoot = false;

	UPROPERTY(EditAnywhere)
	float DropOffset = 70.0f;

	UPROPERTY(EditAnywhere)
	bool bIsSpeedy = false;

	UPROPERTY(EditAnywhere)
	TArray<UMaterialInstance*> MaterialArray;

	UPROPERTY(EditAnywhere)
	int PlayerID = 0;

	UPROPERTY(EditAnywhere)
	int Terrain = 0;
};