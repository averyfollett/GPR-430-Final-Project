// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerableSpotLight.h"

#include "Components/SpotLightComponent.h"

APowerableSpotLight::APowerableSpotLight()
{
	
}

void APowerableSpotLight::BeginPlay()
{
	Super::BeginPlay();

	SpotLightComponent->SetVisibility(false);
}

void APowerableSpotLight::SetPowered(const bool IsPowered, FGuid SetterID)
{
	SpotLightComponent->SetVisibility(IsPowered);
}
