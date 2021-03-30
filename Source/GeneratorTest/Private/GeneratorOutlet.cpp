// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratorOutlet.h"

#include "Powerable.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGeneratorOutlet::AGeneratorOutlet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called when the game starts or when spawned
void AGeneratorOutlet::BeginPlay()
{
	Super::BeginPlay();
	
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

