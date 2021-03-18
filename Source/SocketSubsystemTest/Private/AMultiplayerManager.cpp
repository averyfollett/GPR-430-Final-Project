// Fill out your copyright notice in the Description page of Project Settings.

#include "AMultiplayerManager.h"
#include "Networking/Public/Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

AMultiplayerManager::AMultiplayerManager()
{
}

AMultiplayerManager::~AMultiplayerManager()
{
}

void AMultiplayerManager::BeginPlay()
{
	Socket = Connect(); //Assign created socket to Socket member variable

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMultiplayerManager::ListenForPackets, 1.0f, true);
}

FSocket* AMultiplayerManager::Connect()
{
	UE_LOG(LogTemp, Warning, TEXT("Starting connection"));

	TSharedRef<FInternetAddr> Address = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	FIPv4Address IP;
	FIPv4Address::Parse("127.0.0.1", IP);
	Address->SetIp(IP.Value);
	Address->SetPort(7000);
	
	FSocket* TCPSocket = FTcpSocketBuilder("default").AsNonBlocking().AsReusable().Build();
	UE_LOG(LogTemp, Warning, TEXT("Socket created"));

	const bool bConnected = TCPSocket->Connect(*Address);
	if (bConnected)
	{
		UE_LOG(LogTemp, Warning, TEXT("Connected"));
		return TCPSocket;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to connect"));
		return nullptr;
	}
}

void AMultiplayerManager::ListenForPackets()
{
	if (!Socket)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Test"));

	int SendType = 1;
	int Sent;
	Socket->Send(reinterpret_cast<uint8*>(SendType), sizeof(SendType), Sent);

	uint32 Size = 0;
	while (Socket->HasPendingData(Size))
	{
		TArray<uint8> ReceivedData;
		//ReceivedData.Init() // This is where I stopped
	}
}
