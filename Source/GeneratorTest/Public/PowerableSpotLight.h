// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Powerable.h"
#include "Components/SpotLightComponent.h"

#include "PowerableSpotLight.generated.h"

/**
 * 
 */
UCLASS()
class GENERATORTEST_API APowerableSpotLight final : public AActor, public IPowerable
{
	GENERATED_BODY()

	APowerableSpotLight();

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpotLightComponent* SpotLightComponent;
	
	virtual void SetPowered(bool IsPowered, FGuid SetterID) override;
};
