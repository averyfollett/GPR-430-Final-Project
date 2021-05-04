// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingWire.h"

#include "Net/UnrealNetwork.h"

ARotatingWire::ARotatingWire()
{
	WireMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wire"));
	WireMeshComponent->SetupAttachment(GetStaticMeshComponent());

	BaseComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	BaseComponent->SetupAttachment(GetStaticMeshComponent());

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(GetStaticMeshComponent());

	ThisGuid = FGuid::NewGuid();

	bReplicates = true;
	AActor::SetReplicateMovement(true);
}

void ARotatingWire::BeginPlay()
{
	Super::BeginPlay();

	StartingRotation = GetActorRotation();
	WireMaterialInstance = WireMeshComponent->CreateDynamicMaterialInstance(0);
	
	TArray<AActor*> InputKeyArray;
	InputsAndOutputs.GenerateKeyArray(InputKeyArray);

	for (AActor* Actor : InputKeyArray)
	{
		InputIdToOutput.Add(Cast<IPowerable>(Actor)->GetGUID(), *InputsAndOutputs.Find(Actor));
	}

	if (Cast<IPowerable>(FirstPowerSource))
	{
		CurrentPowerSource = Cast<IPowerable>(FirstPowerSource)->GetGUID();
	}

	AnglesToInputs.GenerateKeyArray(AngleList);
}

void ARotatingWire::RotateWire_Implementation()
{
	if (CurrentPowerSource.IsValid())
	{
		SetNextPowered(false, CurrentPowerSource);
	}
	
	CurrentAngleIndex = (CurrentAngleIndex + 1) % AngleList.Num();
	SetActorRotation(FRotator(0.0f, StartingRotation.Yaw + AngleList[CurrentAngleIndex], 0.0f));
	if (Cast<IPowerable>(*AnglesToInputs.Find(AngleList[CurrentAngleIndex])))
	{
		CurrentPowerSource = Cast<IPowerable>(*AnglesToInputs.Find(AngleList[CurrentAngleIndex]))->GetGUID();
	}
	else
	{
		CurrentPowerSource.Invalidate();
	}

	if (CurrentPowerSource.IsValid() && (LastReportedPowerState.Num() > 0))
	{
		SetPowered(*LastReportedPowerState.Find(CurrentPowerSource), CurrentPowerSource);
	}
}

void ARotatingWire::SetPowered_Implementation(const bool IsPowered, const FGuid SetterID)
{
	LastReportedPowerState.Add(SetterID, IsPowered);

	if (SetterID == CurrentPowerSource)
	{
		SetAppearance(IsPowered);
		SetNextPowered(IsPowered, SetterID);
	}
}

void ARotatingWire::SetNextPowered_Implementation(const bool Powered, const FGuid PowerSource)
{
	Cast<IPowerable>(*InputIdToOutput.Find(PowerSource))->SetPowered(Powered, ThisGuid);
}

void ARotatingWire::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARotatingWire, CurrentAngleIndex);
}

void ARotatingWire::SetAppearance_Implementation(const bool Powered) const
{
	WireMaterialInstance->SetScalarParameterValue(FName("On/Off"), Powered);
	WireMeshComponent->SetMaterial(0, WireMaterialInstance);
}
