// Fill out your copyright notice in the Description page of Project Settings.


#include "AndGateLight.h"

AAndGateLight::AAndGateLight()
{
	ThisGuid = FGuid::NewGuid();
}

void AAndGateLight::BeginPlay()
{
	Super::BeginPlay();

	DynamicMaterialInstance = UMaterialInstanceDynamic::Create(LightMaterialInstance, this);
	SetAppearance(false);
	PowerNext(false);
	bHasFinishedSetup = true;
}

void AAndGateLight::SetAppearance(const bool Powered) const
{
	if (Powered)
	{
		DynamicMaterialInstance->SetScalarParameterValue(FName("Emission"), 50.0f);
		GetStaticMeshComponent()->SetMaterial(0, DynamicMaterialInstance);
	}
}

void AAndGateLight::PowerNext(const bool PowerState)
{
	for (AActor* Actor : NextPowerables)
	{
		if (Cast<IPowerable>(Actor))
		{
			Cast<IPowerable>(Actor)->SetPowered(PowerState, ThisGuid);
		}
	}
}

void AAndGateLight::SetPowered(bool IsPowered, FGuid SetterID)
{
	PowerStateOfInputs.Add(SetterID, IsPowered);
	TArray<bool> ValueArray;
	PowerStateOfInputs.GenerateValueArray(ValueArray);
	bIsPowered = ValueArray[0];

	for (bool PoweredState : ValueArray)
	{
		bIsPowered = PoweredState && bIsPowered;
	}

	bIsPowered = (bStayPowered && bWasPowered) || bIsPowered;

	SetAppearance(bIsPowered);
	//This is where you would add a delay if you wanted
	PowerNext(bIsPowered);
	bWasPowered = bIsPowered || bWasPowered;
}
