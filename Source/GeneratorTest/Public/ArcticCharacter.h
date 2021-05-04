// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ChatLineUIWidget.h"
#include "GameFramework/Character.h"
#include "ChatUIWidget.h"
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

	UFUNCTION(NetMulticast, Unreliable)
	void GeneratorStolen();

	UFUNCTION(BlueprintCallable)
	void PlayerOpenCloseChat();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void UseChat(const FString& PlayerName, const FString& Text);

	UFUNCTION(NetMulticast, Unreliable)
	void EnterText(const FString& PlayerName, const FString& Text);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=UI)
	TSubclassOf<UUserWidget> ChatLineClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UChatLineUIWidget* ChatLine;

	
	FORCEINLINE class UChatUIWidget* GetChatUI() const { return ChatUI; }
    
    UFUNCTION(BlueprintCallable)
    void LoadChatUI();
	
	UPROPERTY(EditAnywhere)
	USceneComponent* GrabLocation;

	UPROPERTY(EditAnywhere)
	UArrowComponent* ForwardArrow;

	UPROPERTY(EditAnywhere)
	UPhysicsHandleComponent* PhysicsHandle;

	UPROPERTY(EditAnywhere)
	float PickupRadius = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	int PlayerID = 0;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=UI)
	TSubclassOf<UUserWidget> ChatUIClass;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UChatUIWidget* ChatUI;
	
	
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

	UFUNCTION(Server, Reliable)
	void Drop();
	UFUNCTION(Server, Reliable)
	void PickUp();

	UFUNCTION(Server, Reliable)
	void PlayerHoldingGenerator();
	UFUNCTION(Server, Reliable)
	void PlayerReleaseGenerator();

	UFUNCTION()
	void TryRotateWire() const;
	UFUNCTION()
	void ServerRotateWire(AActor* Actor) const;
	UFUNCTION()
    void ClientRotateWire(AActor* Actor) const;

	UFUNCTION(BlueprintImplementableEvent)//, NetMulticast, Unreliable)
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
	UFUNCTION()
	void InputActionUseChat();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BaseTurnRate = 45.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BaseLookUpRate = 45.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	bool bIsHoldingObject = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerReachDistance = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGenerator* Generator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> IgnoreActorArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	bool bIsReachingForGenerator = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	bool bSwitchReachAnim = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	bool bGeneratorInHand = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	bool bExtendArms = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	int Terrain = 0;

	UPROPERTY()
	bool isUsingChat = false;

	UPROPERTY()
	UChatUIWidget* ChatInstance;

	void GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const;
};