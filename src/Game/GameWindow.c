#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "Globals.h"
/*
    DECLARE THE TEXTURES FOR ALL SPRITES
*/
Texture2D ovni;
Texture2D squid;
Texture2D crab;
Texture2D octopus;
Texture2D structure;
Texture2D bullet;
Texture2D player;

int GameWindow()
{
    // initialize the window
    InitWindow(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, "Space Invaders");

    // set the window to fullscreen
    SetWindowState(FLAG_FULLSCREEN_MODE);

    // set the framerate to 60 frames per second
    SetTargetFPS(60);
    
    // load the textures for all sprites
    player = LoadTexture("../src/assets/images/jugadorprov.png");
    ovni = LoadTexture("../src/assets/images/ovniprov.png");
    squid = LoadTexture("../src/assets/images/calamarprov.png");
    crab = LoadTexture("../src/assets/images/cangrejoprov.png");
    octopus = LoadTexture("../src/assets/images/pulpoprov.png");
    structure = LoadTexture("../src/assets/images/estructuraprov.png");
    bullet = LoadTexture("../src/assets/images/balaprov.png");

    // declare the source and destination rectangles for the player's ship
    Rectangle sourceRecPlayer;
    Rectangle destRecPlayer;
    // declare the variables for the player's ship position
    int posPlayerX = GAME_SCREEN_WIDTH/2;
    int posPlayerY = GAME_SCREEN_HEIGHT - 100;

    while (!WindowShouldClose())
    {   
        // check if the player is moving to the left and if it's not going out of the screen
        if (posPlayerX < 0 + PLAYER_WIDTH * 5) posPlayerX = 0 + PLAYER_WIDTH * 5;
        // check if the player is moving to the right and if it's not going out of the screen
        if (posPlayerX > GAME_SCREEN_WIDTH - PLAYER_WIDTH * 5) posPlayerX = GAME_SCREEN_WIDTH - PLAYER_WIDTH * 5;
        // check if the player is moving to the right
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) posPlayerX += 5;
        // check if the player is moving to the left
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) posPlayerX -= 5;

        // set the source rectangle for the player's ship
        sourceRecPlayer = (Rectangle){0, 0, PLAYER_WIDTH, PLAYER_HEIGHT};
        //set the destination rectangle for the player's ship, if the player is moving
        //the ship, the posPlayerX will be updated, so the ship will move
        destRecPlayer = (Rectangle){posPlayerX, posPlayerY, sourceRecPlayer.width * 5, sourceRecPlayer.height * 5};

        BeginDrawing();
            // paint the screen with a black background
            ClearBackground(BLACK);
            // show the player's ship
            DrawTexturePro(player, sourceRecPlayer, destRecPlayer, (Vector2){destRecPlayer.width/2,destRecPlayer.height/2}, 0, green);
            
        EndDrawing();
    }
    // unload the textures and close the window
    UnloadTexture(ovni);
    UnloadTexture(squid);
    UnloadTexture(crab);
    UnloadTexture(octopus);
    UnloadTexture(structure);
    UnloadTexture(bullet);
    CloseWindow();        

    return 0;
}
