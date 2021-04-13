// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcticCharacter.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Generator.h"
#include "WireInterface.h"
#include "Camera/CameraActor.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AArcticCharacter::AArcticCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GrabLocation = CreateDefaultSubobject<USceneComponent>(TEXT("GrabLocation"));
	GrabLocation->SetupAttachment(RootComponent);

	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ForwardArrow"));
	ForwardArrow->SetupAttachment(RootComponent);

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

	bUseControllerRotationYaw = false;

	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(42.0f);
}

// Called when the game starts or when spawned
void AArcticCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Find generator and set reference
	TArray<AActor*> FoundGenerators;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGenerator::StaticClass(), FoundGenerators);
	Generator = Cast<AGenerator>(FoundGenerators[0]);
	
	SpawnCamera();
	Client_UpdateColor();
	SetTerrainBasedOnLevel();
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(1.0f, 0.0f, 3.0f, FLinearColor::Black);
}

int AArcticCharacter::SpawnCamera()
{
	//TODO: Spawn custom PanCamera class
	//GetWorld()->SpawnActor()
	//TODO: Set owned camera local variable
	return 1;
}

int AArcticCharacter::Client_UpdateColor()
{
	GetMesh()->SetMaterial(0, MaterialArray[PlayerID]);
	return 1;
}

int AArcticCharacter::SetTerrainBasedOnLevel()
{
	//If we're in level 1
	if (GetWorld()->GetMapName() == "Level_1")
	{
		Terrain = 1;
		return Terrain;
	}
	else
	{
		Terrain = 0;
		return Terrain;
	}
}

int AArcticCharacter::Drop()
{
	bExtendArms = false;
	bIsReachingForGenerator = bSwitchReachAnim = true;
	if (PlayerReleaseGenerator())
	{
		return 1;
	}
	return 0;
}

int AArcticCharacter::PickUp()
{
	if (IsValid(Generator))
	{
		if (UKismetMathLibrary::Vector_Distance(Generator->GetActorLocation(), GetActorLocation()) <= PickupRadius)
		{
			RotateToGenerator();
			bIsReachingForGenerator = true;
			//Might want a delay here
			//DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			Generator->bIsHeld = true;
			Generator->SetHeldBy(this);
			Generator->SetIsPickedUp(true);
			PlayerHoldingGenerator();

			return 1;
		}
		
		return 0;
	}

	return -1;
}

int AArcticCharacter::PlayerHoldingGenerator()
{
	const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		true);
	if (Generator->GetRootComponent()->AttachToComponent(GetMesh(), AttachmentRules, "spine_02Socket"))
	{
		bIsHoldingObject = bGeneratorInHand = true;
		bIsReachingForGenerator = false;
		return 1;
	}
	return 0;
}

int AArcticCharacter::PlayerReleaseGenerator()
{
	const FDetachmentTransformRules DetachmentRules = FDetachmentTransformRules(
		EDetachmentRule::KeepWorld,
		EDetachmentRule::KeepRelative,
		EDetachmentRule::KeepWorld,
		true);
	Generator->GetRootComponent()->DetachFromComponent(DetachmentRules);
	Generator->SetActorLocation(Generator->GetActorLocation() + GetActorForwardVector() * DropOffset);
	Generator->bIsHeld = false;
	Generator->SetHeldBy();
	Generator->SetIsPickedUp(false);
	bIsHoldingObject = bGeneratorInHand = bSwitchReachAnim = bIsReachingForGenerator = false;
	return 1;
}

void AArcticCharacter::TryRotateWire() const
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Cast<IWireInterface>(Actor))
		{
			ServerRotateWire(Actor);

			if (!HasAuthority())
			{
				ClientRotateWire(Actor);
			}
		}
	}
}

void AArcticCharacter::ServerRotateWire(AActor* Actor) const
{
	Cast<IWireInterface>(Actor)->RotateWire();
}

void AArcticCharacter::ClientRotateWire(AActor* Actor) const
{
	Cast<IWireInterface>(Actor)->RotateWire();
}

void AArcticCharacter::SetCameraLocation(FVector Location) const
{
	OwnedCamera->SetActorLocation(Location);
}

void AArcticCharacter::InputAxisTurnRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AArcticCharacter::InputAxisLookUpRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AArcticCharacter::InputAxisMoveForward(float Value)
{
	const FRotator Rotator = FRotator(0.0f, 0.0f, GetControlRotation().Yaw);
	const FVector RightVector = UKismetMathLibrary::GetRightVector(Rotator);
	const FVector NegatedVector = UKismetMathLibrary::NegateVector(RightVector);
	AddMovementInput(NegatedVector, Value);
}

void AArcticCharacter::InputAxisMoveRight(float Value)
{
	const FRotator Rotator = FRotator(0.0f, 0.0f, GetControlRotation().Yaw);
	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(Rotator);
	AddMovementInput(ForwardVector, Value);
}

void AArcticCharacter::InputActionInteractPressed()
{
	bExtendArms = true;
	bLeanForward = true;
	TryRotateWire();
}

void AArcticCharacter::InputActionInteractReleased()
{
	bLeanForward = false;

	if (bGeneratorInHand)
	{
		Drop();
	}
	else
	{
		PickUp();
	}
}

// Called every frame
void AArcticCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PhysicsHandle->SetTargetLocation(GrabLocation->GetComponentLocation());
	bExtendArms = bGeneratorInHand;

	if (bIsSpeedy)
	{
		GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
	}

	Client_UpdateColor();
	
	//Idle();
}

// Called to bind functionality to input
void AArcticCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Axis
	PlayerInputComponent->BindAxis("TurnRate", this, &AArcticCharacter::InputAxisTurnRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AArcticCharacter::InputAxisLookUpRate);
	PlayerInputComponent->BindAxis("MoveForward", this, &AArcticCharacter::InputAxisMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AArcticCharacter::InputAxisMoveRight);

	//Action
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AArcticCharacter::InputActionInteractPressed);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AArcticCharacter::InputActionInteractReleased);
}

int AArcticCharacter::GeneratorStolen()
{
	bIsHoldingObject = bGeneratorInHand = bSwitchReachAnim = bIsReachingForGenerator = false;

	return 1;
}

