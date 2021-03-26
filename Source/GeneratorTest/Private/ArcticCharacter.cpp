// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcticCharacter.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Generator.h"

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
	bIsReachingForGenerator = true;
	bSwitchReachAnim = true;
	if (PlayerReleaseGenerator())
	{
		return 1;
	}
	return 0;
}

int AArcticCharacter::PlayerReleaseGenerator()
{
	const FDetachmentTransformRules DetachmentRules = FDetachmentTransformRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepRelative, EDetachmentRule::KeepWorld, true);
	Generator.GetDefaultObject()->GetRootComponent()->DetachFromComponent(DetachmentRules);
	Generator.GetDefaultObject()->SetActorLocation(Generator.GetDefaultObject()->GetActorLocation() + GetActorForwardVector() * DropOffset);
	Generator.GetDefaultObject()->bIsHeld = false;
	//TODO: Finish this function call
	//Generator.GetDefaultObject()->SetHeldBy()
	return 1;
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

}

int AArcticCharacter::GeneratorStolen()
{
	bIsHoldingObject = false;
	bGeneratorInHand = false;
	bSwitchReachAnim = false;
	bIsReachingForGenerator = false;

	return 1;
}

