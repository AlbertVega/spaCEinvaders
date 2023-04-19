#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "Globals.h"

#define NUM_SHOOTS 50
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

typedef struct Bullet
{
    int posBulletY;
    int posBulletX;
    Rectangle sourceRecBullet;
    Rectangle destRecBullet;
    bool active;
} Bullet;

int array[10] = {1,2,4,5,6,7,8,9,10};

void SetBullet(Bullet *bullets, int posPlayerX, int posPlayerY){
    for (int i = 0; i < NUM_SHOOTS; i++)
    {   
        if (bullets[i].active == false)
        {
            bullets[i].posBulletX = posPlayerX;
            bullets[i].posBulletY = posPlayerY-40;
            bullets[i].active = true;
            break;
        }
    }
}

void UpdateBullets(Bullet *bullets){
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        if (bullets[i].active)
        {
            bullets[i].sourceRecBullet = (Rectangle){0, 0, BULLET_WIDTH, BULLET_HEIGHT};
            bullets[i].destRecBullet = (Rectangle){bullets[i].posBulletX, bullets[i].posBulletY, bullets[i].sourceRecBullet.width * 5, bullets[i].sourceRecBullet.height * 5};
            DrawTexturePro(bullet, bullets[i].sourceRecBullet, bullets[i].destRecBullet, (Vector2){bullets[i].destRecBullet.width/2 +5,bullets[i].destRecBullet.height/2 +5}, 0, WHITE);
            bullets[i].posBulletY -= 15;
            if (bullets[i].posBulletY < 0)
            {
                bullets[i].active = false;
                bullets[i].posBulletY = GAME_SCREEN_HEIGHT - 100;
            }
        }
    }
}

void UpdateOvnis(char *Instruccion){
    if (strcmp(Instruccion, "dispara")) {   
        for (int i=0; i<2; i++){
            if (array[i] != 0){
                array[i] = 0;
            }
        }
        for (int i=0; i<2; i++){
            printf("%d", array[i]);
        }
    }    
}

int GameWindow()
{
    // initialize the window
    InitWindow(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, "Space Invaders");

    // set the framerate to 60 frames per second
    SetTargetFPS(60);

    // load the textures for all sprites
    Image logo = LoadImage("Graphics/src/assets/images/logo.png");
    player = LoadTexture("Graphics/src/assets/images/jugadorprov.png");
    ovni = LoadTexture("Graphics/src/assets/images/ovniprov.png");
    squid = LoadTexture("Graphics/src/assets/images/calamarprov.png");
    crab = LoadTexture("Graphics/src/assets/images/cangrejoprov.png");
    octopus = LoadTexture("Graphics/src/assets/images/pulpoprov.png");
    structure = LoadTexture("Graphics/src/assets/images/estructuraprov.png");
    bullet = LoadTexture("Graphics/src/assets/images/balaprov.png");

    // set the window icon
    SetWindowIcon(logo);

    // declare the source and destination rectangles for the player's ship
    Rectangle sourceRecPlayer;
    Rectangle destRecPlayer;
    // declare the variables for the player's ship position
    int posPlayerX = GAME_SCREEN_WIDTH/2;
    int posPlayerY = GAME_SCREEN_HEIGHT - 100;

    // declare the array of bullets and initialize them to false
    Bullet bullets[NUM_SHOOTS];
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        bullets[i].active = false;
    }

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
        // check if the player is shooting
        if (IsKeyPressed(KEY_SPACE)) SetBullet(bullets, posPlayerX, posPlayerY);

        // set the source rectangle for the player's ship
        sourceRecPlayer = (Rectangle){0, 0, PLAYER_WIDTH, PLAYER_HEIGHT};
        //set the destination rectangle for the player's ship, if the player is moving
        //the ship, the posPlayerX will be updated, so the ship will move
        destRecPlayer = (Rectangle){posPlayerX, posPlayerY, sourceRecPlayer.width * 5, sourceRecPlayer.height * 5};

        BeginDrawing();
            // paint the screen with a black background
            ClearBackground(BLACK);
            // show the structures of the game
            //SetEstructura();
            // show the player's ship
            DrawTexturePro(player, sourceRecPlayer, destRecPlayer, (Vector2){destRecPlayer.width/2,destRecPlayer.height/2}, 0, green);
            // update the bullets
            UpdateBullets(bullets);

        EndDrawing();
    }
    // unload the textures and close the window
    UnloadTexture(ovni);
    UnloadTexture(squid);
    UnloadTexture(crab);
    UnloadTexture(octopus);
    UnloadTexture(structure);
    UnloadTexture(bullet);
    UnloadTexture(player);
    UnloadImage(logo);
    CloseWindow();        

    return 0;
}
