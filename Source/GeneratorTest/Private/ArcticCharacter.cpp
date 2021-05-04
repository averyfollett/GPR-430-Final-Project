// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcticCharacter.h"

#include "ChatLineUIWidget.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Generator.h"
#include "PanCamera.h"
#include "WireInterface.h"
#include "Camera/CameraActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "NWGameInstance.h"

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

	bReplicates = true;
    ACharacter::SetReplicateMovement(true);
	bNetLoadOnClient = true;
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

	LoadChatUI();
}

void AArcticCharacter::LoadChatUI()
{
	ChatUI = CreateWidget<UChatUIWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), ChatUIClass);
	
	ChatUI->AddToViewport();
	ChatUI->OpenCloseChat(ESlateVisibility::Hidden);
}

int AArcticCharacter::SpawnCamera()
{
	const FTransform SpawnTransform = FTransform(FVector(800.0f, 800.0f, 910.0f));
	const FActorSpawnParameters SpawnParameters;
	OwnedCamera = GetWorld()->SpawnActor<APanCamera>(APanCamera::StaticClass(), SpawnTransform, SpawnParameters);
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

void AArcticCharacter::Drop_Implementation()
{
	bExtendArms = false;
	bIsReachingForGenerator = bSwitchReachAnim = true;
	PlayerReleaseGenerator();
}

void AArcticCharacter::PickUp_Implementation()
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
		}
	}
}

void AArcticCharacter::PlayerHoldingGenerator_Implementation()
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
	}
}

void AArcticCharacter::PlayerReleaseGenerator_Implementation()
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

void AArcticCharacter::InputActionUseChat()
{
	PlayerOpenCloseChat();
}

void AArcticCharacter::PlayerOpenCloseChat()
{
	if(isUsingChat)
	{
		ChatUI->OpenCloseChat(ESlateVisibility::Hidden);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
	}
	else
	{
		ChatUI->OpenCloseChat(ESlateVisibility::Visible);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameAndUI());
		ChatUI->SetFocus();
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
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
	PlayerInputComponent->BindAction("UseChat", IE_Released, this, &AArcticCharacter::InputActionUseChat);
}

void AArcticCharacter::GeneratorStolen_Implementation()
{
	bIsHoldingObject = bGeneratorInHand = bSwitchReachAnim = bIsReachingForGenerator = false;
}

void AArcticCharacter::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AArcticCharacter, bIsHoldingObject);
	DOREPLIFETIME(AArcticCharacter, bIsReachingForGenerator);
	DOREPLIFETIME(AArcticCharacter, bSwitchReachAnim);
	DOREPLIFETIME(AArcticCharacter, bGeneratorInHand);
	DOREPLIFETIME(AArcticCharacter, bExtendArms);
	DOREPLIFETIME(AArcticCharacter, bLeanForward);
	DOREPLIFETIME(AArcticCharacter, PlayerID);
	DOREPLIFETIME(AArcticCharacter, Terrain);
}

void AArcticCharacter::UseChat_Implementation(const FString& PlayerName, const FString& Text)
{
	TArray<AActor*> allActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArcticCharacter::StaticClass(), allActors);

	for (AActor* Actor : allActors)
	{
		EnterText(PlayerName, Text);
	}
}

void AArcticCharacter::EnterText_Implementation(const FString& PlayerName, const FString& Text)
{
	if(IsValid(ChatUI))
	{
		ChatLine = CreateWidget<UChatLineUIWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		ChatLine->PlayerName = PlayerName;
		ChatLine->Text = Text;
	}
}

