Our Unreal OnlineSubsystemNull implementation is all within the NWGameInstance class and handles all creating, finding, 
joining and destroying of sessions.

StartOnlineGame is a blueprint-callable wrapper for HostSession which handles the creation of a session as well as loading
the host themself into the level. This is also where all session settings are set up such as max players, session name, etc.

FindOnlineGames is a blueprint-callable wrapper for FindSessions which handles searching for existing sessions on the local
network (due to OnlineSubsystemNull). The OnFindSessionsCompleteDelegate is responsible for returning an array of session
search results which is handled (displayed) by our UI which is in blueprints.

JoinOnlineGame is a blueprint-callable wrapper for JoinSession which handles connecting the client to the given session, 
changing level, etc.

DestroySessionAndLeaveGame is a blueprint-callable wrapper for DestroySession which simply destroys an existing session and 
its delegate OnDestroySessionComplete handles moving the clients back to a safe map (the main menu).

The rest of our networking takes place in the individual classes (such as ArcticCharacter, our player) where we handle 
replicating variables and functions.