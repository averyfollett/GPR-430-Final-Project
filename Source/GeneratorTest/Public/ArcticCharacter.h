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

	//UFUNCTION()
	//void Idle();

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
	int PlayerHoldingGenerator();
	UFUNCTION()
	int PlayerReleaseGenerator();

	UFUNCTION()
	void TryRotateWire() const;
	UFUNCTION()
	void ServerRotateWire(AActor* Actor) const;
	UFUNCTION()
    void ClientRotateWire(AActor* Actor) const;

	UFUNCTION(BlueprintImplementableEvent)
	void RotateToGenerator();

	UFUNCTION()
	void SetCameraLocation(FVector Location) const;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BaseTurnRate = 45.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BaseLookUpRate = 45.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHoldingObject = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerReachDistance = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGenerator* Generator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> IgnoreActorArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsReachingForGenerator = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSwitchReachAnim = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bGeneratorInHand = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bExtendArms = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bLeanForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACameraActor* OwnedCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPoot = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DropOffset = 70.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSpeedy = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UMaterialInstance*> MaterialArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PlayerID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Terrain = 0;
};