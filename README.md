# UnstructuredCom
Sample code to demonstrate unstructured behavior when running a local COM server

## Issue summary
While a local single threaded COM server is doing an outgoing calls to a single threaded client, it appears to be able to process it's own message queue. The server state may therefore have changed when the outgoing call returns. 

## Description
This sample code implements a client application, and a local COM server called 'Player'. The client creates a Player object, and provides the player with a frame data source. The player displays the frame numbers it got from the client. 

The player is driven by a timer that triggers fetching of frame data from the client. Once a frame is received, it schedules a redraw by invalidating it's own window. On the resulting paint messages, the player then prints the frame number it got from the client. If, however, the client spends some time processing the frame request, the player appears to be able to process it's own message queue (including painting to sreen while it is fetching the frame from the client). In this case, the player prints a message telling that it did not receive a frame.

Since the player is single threaded, it is surprising that it is able to process it's own message queue while it is, at the same time, calling a function on the client. As a result, the player appears to run two threads, but since it is single threaded, regular synchronization primitives (mutexes) can not be used to protect data.

## Interesting code snippets:
See Player/Player.cpp, functions Player::OnPaint and Player::OnTimer, that are annotated with this interesting behavior. 

## Bonus chatter: Server destruction
Server destruction is a special case, that cause particularly visible effects (not illustrated in this sample)

1. The server calls a function on the client
2. The client is busy, and can not immediately handle the request, so the server has to wait.
3. Now the client starts processing it's own messages
4. The client releases the server
5. The server destructors run
6. The client services the call from the client (step 1.)
7. The function call in 1. returns, but the server is now destroyed, and the stack is gone. 

## Build/run instructions

* Build projects Client and Player. Player.exe is registered automatically in a post build event.
* Run Client.exe
* Two windows should appear, Player and Client. The Player window should show some continuously updating text. 