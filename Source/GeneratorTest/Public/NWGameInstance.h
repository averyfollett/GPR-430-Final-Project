// Fill out your copyright notice in the Description page of Project Settings.


//The code here and in the corresponding cpp file is following the tutorial at https://unreal.gg-labs.com/v/4.25/wiki-archives/networking/how-to-use-sessions-in-c++

#pragma once
#include "CoreMinimal.h"

#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "FindSessionsCallbackProxy.h"
#include "ChatUIWidget.h"
#include "NWGameInstance.generated.h"

// Custom delegate for us to handle displaying sessions in UMG with blueprints
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSessionsFound, const TArray<FBlueprintSessionResult>&, SearchResults);

UCLASS()
class GENERATORTEST_API UNWGameInstance : public UGameInstance
{
    GENERATED_BODY()

        /**
        *	Function to host a game!
        */
        bool HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, int32 MaxNumPlayers);

    // Delegate called when session created
    FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
    // Delegate called when session started
    FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
    // Delegate for searching for sessions
    FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
    // Delegate for joining a session
    FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
    // Delegate for destroying a session
    FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;

    // Handles to registered delegates for creating/starting a session
    FDelegateHandle OnCreateSessionCompleteDelegateHandle;
    FDelegateHandle OnStartSessionCompleteDelegateHandle;
    // Handle to registered delegate for searching a session
    FDelegateHandle OnFindSessionsCompleteDelegateHandle;
    // Handle to registered delegate for joining a session
    FDelegateHandle OnJoinSessionCompleteDelegateHandle;
    // Handle to registered delegate for destroying a session
    FDelegateHandle OnDestroySessionCompleteDelegateHandle;

    
    TSharedPtr<class FOnlineSessionSettings> SessionSettings;
    TSharedPtr<class FOnlineSessionSearch> SessionSearch;

    UPROPERTY(BlueprintAssignable)
    FSessionsFound SessionsFound;

    UNWGameInstance(const FObjectInitializer& ObjectInitializer);

    /**
    *	Function fired when a session create request has completed
    */
    virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

    /**
    *	Function fired when a session start request has completed
    */
    void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

    /**
    *	Find an online session
    */
    void FindSessions(TSharedPtr<const FUniqueNetId> UserId, bool bIsLAN, bool bIsPresence);

    /**
    *	Delegate fired when a session search query has completed
    */
    void OnFindSessionsComplete(bool bWasSuccessful);

    /**
    *	Joins a session via a search result
    */
    bool JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);

    /**
    *	Delegate fired when a session join request has completed
    */
    void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

    /**
    *	Delegate fired when a destroying an online session has completed
    */
    virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

    virtual void BeginDestroy() override;

    
protected:

    
public:
    UFUNCTION(BlueprintCallable, Category = "Network|Test")
    void StartOnlineGame();
    
    UFUNCTION(BlueprintCallable, Category = "Network|Test")
    void FindOnlineGames();
    
    UFUNCTION(BlueprintCallable, Category = "Network|Test")
    void JoinOnlineGame(FBlueprintSessionResult SessionResult);

    UFUNCTION(BlueprintCallable, Category = "Network|Test")
    void DestroySessionAndLeaveGame();
};