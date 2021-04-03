// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcticCharacter.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Generator.h"
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
	//TODO: Get generator actor and set the local variable
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
	if (UKismetMathLibrary::Vector_Distance(Generator.GetDefaultObject()->GetActorLocation(), GetActorLocation()) <= PickupRadius)
	{
		RotateToGenerator();
		bIsReachingForGenerator = true;
		//Might want a delay here
		//DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		Generator.GetDefaultObject()->bIsHeld = true;
		Generator.GetDefaultObject()->SetHeldBy(this);
		Generator.GetDefaultObject()->SetIsPickedUp(true);
		AttachGenerator();

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
	Generator.GetDefaultObject()->GetRootComponent()->DetachFromComponent(DetachmentRules);
	Generator.GetDefaultObject()->SetActorLocation(Generator.GetDefaultObject()->GetActorLocation() + GetActorForwardVector() * DropOffset);
	Generator.GetDefaultObject()->bIsHeld = false;
	Generator.GetDefaultObject()->SetHeldBy();
	Generator.GetDefaultObject()->SetIsPickedUp(false);
	bIsHoldingObject = bGeneratorInHand = bSwitchReachAnim = bIsReachingForGenerator = false;
	return 1;
}

void AArcticCharacter::TryRotateWire()
{
	//TODO: Implement function
}

void AArcticCharacter::RotateToGenerator()
{
	//TODO: Implement function
}

void AArcticCharacter::AttachGenerator()
{
	Generator.GetDefaultObject()->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "spine_02Socket");
	//Used delay in BP
	bIsHoldingObject = bGeneratorInHand = true;
	bIsReachingForGenerator = false;
}

void AArcticCharacter::SetCameraLocation(FVector Location)
{
	OwnedCamera.GetDefaultObject()->SetActorLocation(Location);
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

