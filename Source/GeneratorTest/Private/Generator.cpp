// Fill out your copyright notice in the Description page of Project Settings.


#include "Generator.h"
#include "ArcticCharacter.h"
#include "GeneratorOutlet.h"

// Sets default values
AGenerator::AGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

int AGenerator::SetHeldBy(TSubclassOf<AArcticCharacter> Character)
{
	if (HeldBy && Character)
	{
		if (HeldBy != Character)
		{
			HeldBy.GetDefaultObject()->GeneratorStolen();
		}
		
		HeldBy = Character;
		return 1;
	}
	return 0;
}

int AGenerator::SetIsPickedUp(bool bPickUp)
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	
	for (AActor* Actor : OverlappingActors)
	{
		if (Actor->IsA(AGeneratorOutlet::StaticClass()))
		{
			if (bPickUp)
			{
				//TODO: Generator Picked Up function in Generator Outlet class
				return 1;
			}
			else
			{
				//TODO: Snap To Center function in Generator Outlet class
				return 0;
			}
		}
	}
	
	return -1;
}

