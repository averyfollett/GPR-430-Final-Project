// Fill out your copyright notice in the Description page of Project Settings.


//The code here and in the corresponding cpp file is following the tutorial at https://unreal.gg-labs.com/v/4.25/wiki-archives/networking/how-to-use-sessions-in-c++

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "NWGameInstance.generated.h"
UCLASS()
class GENERATORTEST_API UNWGameInstance : public UGameInstance
{
    GENERATED_BODY()

        /**
        *	Function to host a game!
        *
        *	@Param		UserID			User that started the request
        *	@Param		SessionName		Name of the Session
        *	@Param		bIsLAN			Is this is LAN Game?
        *	@Param		bIsPresence		"Is the Session to create a presence Session"
        *	@Param		MaxNumPlayers	        Number of Maximum allowed players on this "Session" (Server)
        */
        bool HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bISPresence, int32 MaxNumPlayers);

    //Delegate called when session created
    FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
    //Delegate called when session started
    FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
    //Delegate for searching for sessions
    FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;

    //Handles to registered delegates for creating/starting a session
    FDelegateHandle OnCreateSessionCompleteDelegateHandle;
    FDelegateHandle OnStartSessionCompleteDelegateHandle;
    //Handle to registered delegate for searching a session
    FDelegateHandle OnFindSessionsCompleteDelegateHandle;

    
    TSharedPtr<class FOnlineSessionSettings> SessionSettings;
    TSharedPtr<class FOnlineSessionSearch> SessionSearch;

    UNWGameInstance(const FObjectInitializer& ObjectInitializer);

    /**
    *	Function fired when a session create request has completed
    *
    *	@param SessionName the name of the session this callback is for
    *	@param bWasSuccessful true if the async action completed without error, false if there was an error
    */
    virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

    /**
    *	Function fired when a session start request has completed
    *
    *	@param SessionName the name of the session this callback is for
    *	@param bWasSuccessful true if the async action completed without error, false if there was an error
    */
    void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

    /**
    *	Find an online session
    *
    *	@param UserId user that initiated the request
    *	@param bIsLAN are we searching LAN matches
    *	@param bIsPresence are we searching presence sessions
    */
    void FindSessions(TSharedPtr<const FUniqueNetId> UserId, bool bIsLAN, bool bIsPresence);

    /**
    *	Delegate fired when a session search query has completed
    *
    *	@param bWasSuccessful true if the async action completed without error, false if there was an error
    */
    void OnFindSessionsComplete(bool bWasSuccessful);
};