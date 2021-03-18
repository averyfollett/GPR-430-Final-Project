// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AMultiplayerManager.generated.h"

/**
 * 
 */
UCLASS()
class SOCKETSUBSYSTEMTEST_API AMultiplayerManager final : public AActor
{
	GENERATED_BODY()
	
public:
	AMultiplayerManager();
	~AMultiplayerManager();

	virtual void BeginPlay() override;

	// Connects to IP and Port and returns created socket
	FSocket* Connect();

	// Listens for incoming packets
	UFUNCTION()
	void ListenForPackets();

	//UFUNCTION(BlueprintCallable)
	//void SendPacket();

	// The active socket we are connecting to
	FSocket* Socket;

	FTimerHandle TimerHandle;
};
