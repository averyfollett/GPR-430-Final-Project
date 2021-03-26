// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BlackoutGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GENERATORTEST_API ABlackoutGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
};
