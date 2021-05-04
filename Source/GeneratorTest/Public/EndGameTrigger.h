// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "EndGameTrigger.generated.h"

UCLASS()
class GENERATORTEST_API AEndGameTrigger final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndGameTrigger();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* TriggerBox;

protected:
	UFUNCTION()
	void TriggerOverlap(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(Server, Reliable)
	void ServerEndGame();
};
