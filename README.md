# UnstructuredCom
Sample code to demonstrates how to avoid reentrancy when running a local COM server using the IMessageFilter interface

## Issue summary
This sample code shows a workaround to avoid reentrancy in the communication between a COM client and a COM client. The problem is that a callback from the server to the client will pump the server message queue while the callback is being marshalled.  

## Description
This sample code implements a client application, and a local COM server called 'Player'. The client creates a Player object, and provides the player with a frame data source through an Initialize call. The initialization is performed asynchronously using a PostMessage, and the message handler calls back into the client to complete initialization. Then, the client starts the player by calling the interface function Play.

Without using a message filter, the Initialize function will process the Play call while calling back into the client, leading to reentrancy problems.

This sample code shows how to use an IMessageFilter implementation to avoid this reentrancy problem, by delaying the Play call until the initialization is complete.

## Build/run instructions

* Build projects Client and Player. Player.exe is registered automatically in a post build event.
* Run Client.exe
* Two windows should appear, Player and Client. The Player window should show that the player is playing. 