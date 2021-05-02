// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingWire.h"

ARotatingWire::ARotatingWire()
{
	WireMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wire"));
	WireMeshComponent->SetupAttachment(GetStaticMeshComponent());

	BaseComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	BaseComponent->SetupAttachment(GetStaticMeshComponent());

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(GetStaticMeshComponent());

	ThisGuid = FGuid::NewGuid();
}

void ARotatingWire::BeginPlay()
{
	Super::BeginPlay();
}

void ARotatingWire::RotateWire()
{
}

void ARotatingWire::SetPowered(bool IsPowered, FGuid SetterID)
{
}

void ARotatingWire::SetNextPowered(bool Powered, FGuid PowerSource)
{
}
