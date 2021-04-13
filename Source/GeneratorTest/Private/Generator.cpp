// Fill out your copyright notice in the Description page of Project Settings.


#include "Generator.h"
#include "ArcticCharacter.h"
#include "GeneratorOutlet.h"
#include "Components/PointLightComponent.h"

// Sets default values
AGenerator::AGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	PointLightComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AGenerator::SetHeldBy(AArcticCharacter* Character)
{
	if (IsValid(HeldBy) && IsValid(Character))
	{
		if (HeldBy != Character)
		{
			HeldBy->GeneratorStolen();
		}
		HeldBy = Character;
		return 1;
	}
	else
	{
		HeldBy = Character;
		return 0;
	}
}

int AGenerator::SetIsPickedUp(const bool bPickUp)
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	
	for (AActor* Actor : OverlappingActors)
	{
		if (Actor->IsA(AGeneratorOutlet::StaticClass()))
		{
			if (bPickUp)
			{
				Cast<AGeneratorOutlet>(Actor)->GeneratorPickedUp();
				return 1;
			}
			else
			{
				Cast<AGeneratorOutlet>(Actor)->SnapGeneratorToCenter(this);
				return 0;
			}
		}
	}
	
	return -1;
}

