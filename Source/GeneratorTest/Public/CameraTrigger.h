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

	//void ActorBeginOverlap(AActor* Actor, AActor* OtherActor);

	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACameraActor* PlaceholderCamera;
};
