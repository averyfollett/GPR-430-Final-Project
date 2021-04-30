// Fill out your copyright notice in the Description page of Project Settings.

#define PRINT(text) UE_LOG(LogTemp, Log, TEXT(text), 0.1f)

#include "GeneratorOutlet.h"

#include "Powerable.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGeneratorOutlet::AGeneratorOutlet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OutletTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OutletTop"));
	OutletTop->SetupAttachment(RootComponent);

	OutletBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OutletBase"));
	OutletBase->SetupAttachment(RootComponent);

	OnActorBeginOverlap.AddDynamic(this, &AGeneratorOutlet::ActorOverlapped);
	OnActorEndOverlap.AddDynamic(this, &AGeneratorOutlet::ActorOverlapEnded);

	ThisGuid = FGuid::NewGuid();
}

void AGeneratorOutlet::GeneratorPickedUp()
{
	SetListPowerState(false);
}

void AGeneratorOutlet::SnapGeneratorToCenter(AGenerator* Generator)
{
	const FVector Offset = FVector(0.0f, 7.0f, 10.0f);
	Generator->SetActorLocation(GetActorLocation() + Offset);
	UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		SparksParticles,
		FTransform(GetActorLocation() + Offset),
		true,
		EPSCPoolMethod::None,
		true);
	ChangeToGreen();
	SetListPowerState(true);
}

void AGeneratorOutlet::ActorOverlapped(AActor* Self, AActor* OtherActor)
{
	PRINT("OVERLAP DETECTED");

	if (OtherActor->IsA(AGenerator::StaticClass()))
	{
		bIsPressed = true;

		AGenerator* Generator = Cast<AGenerator>(OtherActor);
		if (!Generator->bIsHeld)
		{
			SnapGeneratorToCenter(Generator);
		}
	}
}

void AGeneratorOutlet::ActorOverlapEnded(AActor* Self, AActor* OtherActor)
{
	/*
	if (OtherActor->IsA(AGenerator::StaticClass()))
	{
		if (bStaysPressed)
		{
			
		}
		else
		{
			bIsPressed = false;
			SetListPowerState(bIsPressed);
			ChangeToRed();
		}
	}
	*/
}

// Called when the game starts or when spawned
void AGeneratorOutlet::BeginPlay()
{
	Super::BeginPlay();

	GeneratorOutletMaterial = UMaterialInstanceDynamic::Create(nullptr, this);
}

void AGeneratorOutlet::SetListPowerState(const bool bIsPowered)
{
	for (AActor* Object : PoweredObjects)
	{
		Cast<IPowerable>(Object)->SetPowered(bIsPowered, ThisGuid);
	}
}

void AGeneratorOutlet::ChangeToGreen() const
{
	GeneratorOutletMaterial->SetVectorParameterValue(FName("Emissive Color"), FColor::Green);
}

void AGeneratorOutlet::ChangeToRed() const
{
	GeneratorOutletMaterial->SetVectorParameterValue(FName("Emissive Color"), FColor::Red);
}

// Called every frame
void AGeneratorOutlet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

