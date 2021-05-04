// Fill out your copyright notice in the Description page of Project Settings.


#include "SlidingDoor.h"

// Sets default values
ASlidingDoor::ASlidingDoor()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetupAttachment(RootComponent);
	
	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	LeftDoor->SetupAttachment(Root);

	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
	RightDoor->SetupAttachment(Root);

	LeftDoorInverted = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoorInverted"));
	LeftDoorInverted->SetupAttachment(Root);

	RightDoorInverted = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoorInverted"));
	RightDoorInverted->SetupAttachment(Root);

	ThisGuid = FGuid::NewGuid();
}

// Called when the game starts or when spawned
void ASlidingDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASlidingDoor::ActivateLights()
{
	for (APowerableSpotLight* Light : LightArray)
	{
		Light->SetPowered(true, ThisGuid);
	}
}

void ASlidingDoor::SetPowered(const bool IsPowered, FGuid SetterID)
{
	if (IsPowered)
	{
		ActivateLights();
		SetActorEnableCollision(false);
		MoveDoors();
	}
}

void ASlidingDoor::MoveDoors_Implementation()
{
	MoveRightDoor();
	LeftDoor->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MoveLeftDoor();
}
