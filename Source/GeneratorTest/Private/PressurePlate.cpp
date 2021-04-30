// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"

#include "ArcticCharacter.h"
#include "Powerable.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnTriggerOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::EndTriggerOverlap);

	ButtonBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonBase"));
	ButtonBase->SetupAttachment(BoxComponent);

	ButtonTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonTop"));
	ButtonTop->SetupAttachment(ButtonBase);

	ThisGuid = FGuid::NewGuid();
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	BottomMaterial = ButtonBase->CreateDynamicMaterialInstance(0);
	TopMaterial = ButtonTop->CreateDynamicMaterialInstance(0);
	SetNextPowered(bIsPowered && bIsPressed);
}

void APressurePlate::OnTriggerOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AArcticCharacter::StaticClass()))
	{
		bIsPressed = true;
		CurrentlyPressedBy.Add(OtherActor);
		SetPowered(bIsPowered, ThisGuid);
		AnimatePressed();
		ChangeColor(FLinearColor::Green);
	}
}

void APressurePlate::EndTriggerOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AArcticCharacter::StaticClass()))
	{
		if (CurrentlyPressedBy.Contains(OtherActor))
		{
			CurrentlyPressedBy.Remove(OtherActor);

			if (CurrentlyPressedBy.Num() == 0)
			{
				if (bStaysPressed)
				{
					bIsPressed = true;
					SetPowered(bIsPowered, ThisGuid);
				}
				else
				{
					bIsPressed = false;
					SetPowered(bIsPowered, ThisGuid);
					AnimateUnpressed();
					ChangeColor(FLinearColor::Red);
				}
			}
		}
	}
}

void APressurePlate::SetPowered(const bool IsPowered, FGuid SetterID)
{
	bIsPowered = IsPowered;
	SetNextPowered(bIsPressed && IsPowered);
}

void APressurePlate::SetNextPowered(const bool bPowered)
{
	for (AActor* Actor : NextPowerables)
	{
		if (Cast<IPowerable>(Actor))
		{
			Cast<IPowerable>(Actor)->SetPowered(bPowered, ThisGuid);
		}
	}
}

void APressurePlate::ChangeColor(const FLinearColor Color) const
{
	BottomMaterial->SetVectorParameterValue(FName("Emissive Color"), Color);
	TopMaterial->SetVectorParameterValue(FName("Emissive Color"), Color);
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

