// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"

#include "Powerable.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	BoxComponent->SetupAttachment(RootComponent);

	ButtonBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonBase"));
	ButtonBase->SetupAttachment(BoxComponent);

	ButtonTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonTop"));
	ButtonTop->SetupAttachment(ButtonBase);
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	BottomMaterial = ButtonBase->CreateDynamicMaterialInstance(0);
	TopMaterial = ButtonTop->CreateDynamicMaterialInstance(0);
	ThisGuid = FGuid::NewGuid();
	SetNextPowered(bIsPowered && bIsPressed);
}

void APressurePlate::SetNextPowered(const bool bPowered)
{
	for (AActor* Actor : NextPowerables)
	{
		Cast<IPowerable>(Actor)->SetPowered(bPowered, ThisGuid);
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

