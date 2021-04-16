// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CameraTrigger.generated.h"

/**
 * 
 */
UCLASS()
class GENERATORTEST_API ACameraTrigger : public ATriggerBox
{
	GENERATED_BODY()

	ACameraTrigger();

	void ActorBeginOverlap(AActor* Actor, AActor* OtherActor);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACameraActor* PlaceholderCamera;
};
