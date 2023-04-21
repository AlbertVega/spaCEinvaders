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

int score = 0;
int lives = 3;

typedef struct Bullet
{
    int posBulletY;
    int posBulletX;
    Rectangle sourceRecBullet;
    Rectangle destRecBullet;
    bool active;
} Bullet;

typedef struct Structure
{
    Rectangle sourceRecStructure;
    Rectangle destRecStructure;
    int state;
} Structure;

typedef struct Alien
{
    int movementX;
    int posAlienY;
    Rectangle sourceRecAlien;
    Rectangle destRecAlien;
    bool active;
    char* type;
    int state;
} Alien;

/* 
    Method to set the initial values of bullets, receives the array of bullets, the positionX and positionY
    of the player, retuns nothing.
*/
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

/* 
    Method to upadate the bullets position, receives the array of bullets, retuns nothing.
*/
void UpdateBullets(Bullet *bullets){
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        if (bullets[i].active)
        {
            bullets[i].sourceRecBullet = (Rectangle){0, 0, BULLET_WIDTH, BULLET_HEIGHT};
            bullets[i].destRecBullet = (Rectangle){bullets[i].posBulletX, bullets[i].posBulletY, bullets[i].sourceRecBullet.width * 4, bullets[i].sourceRecBullet.height * 4};
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

/* 
    Method to set the initial values of bunkers, receives the array of bunkers, retuns nothing.
*/
void SetBunker(Structure *bunkers){
    for (int i = 0; i < NUM_BUNKERS; i++)
    {
        bunkers[i].sourceRecStructure = (Rectangle){0, 0, BUNKER_WIDTH, BUNKER_HEIGHT};
        bunkers[i].destRecStructure = (Rectangle){i*(GAME_SCREEN_WIDTH / 4) + 80, GAME_SCREEN_HEIGHT - 150, bunkers[i].sourceRecStructure.width * 5, bunkers[i].sourceRecStructure.height * 5};
        bunkers[i].state = 1;
    }
}

/* 
    Method to upadate the bunkers state, receives the array of bunkers, retuns nothing.
*/
void UpdateBunker(Structure *bunkers) {
    for (int i = 0; i < NUM_BUNKERS; i++)
    {
        if (bunkers[i].state > 5){
            bunkers[i].destRecStructure = (Rectangle){0, 0, 0, 0};
            bunkers[i].destRecStructure = (Rectangle){0, 0, 0, 0};
        }
        if (bunkers[i].state == 1)
        {
            DrawTexturePro(structure, bunkers[i].sourceRecStructure, bunkers[i].destRecStructure, (Vector2){0,0}, 0, GREEN);
        }
        else if (bunkers[i].state == 2)
        {
            bunkers[i].sourceRecStructure = (Rectangle){15, 0, BUNKER_WIDTH, BUNKER_HEIGHT};
            DrawTexturePro(structure, bunkers[i].sourceRecStructure, bunkers[i].destRecStructure, (Vector2){0,0}, 0, GREEN);
        }
        else if (bunkers[i].state == 3)
        {
            bunkers[i].sourceRecStructure = (Rectangle){30, 0, BUNKER_WIDTH, BUNKER_HEIGHT};
            DrawTexturePro(structure, bunkers[i].sourceRecStructure, bunkers[i].destRecStructure, (Vector2){0,0}, 0, GREEN);
        }
        else if (bunkers[i].state == 4)
        {
            bunkers[i].sourceRecStructure = (Rectangle){45, 0, BUNKER_WIDTH, BUNKER_HEIGHT};
            DrawTexturePro(structure, bunkers[i].sourceRecStructure, bunkers[i].destRecStructure, (Vector2){0,0}, 0, GREEN);
        }
        else if (bunkers[i].state == 5)
        {
            bunkers[i].sourceRecStructure = (Rectangle){60, 0, BUNKER_WIDTH, BUNKER_HEIGHT};
            DrawTexturePro(structure, bunkers[i].sourceRecStructure, bunkers[i].destRecStructure, (Vector2){0,0}, 0, GREEN);
        }
    }
}

/* 
    Method to check the collision between bullets and bunkers, receives the array of bullets and the array of bunkers, retuns nothing.
*/
void CheckBunker(Bullet *bullets, Structure *bunkers) {
    for (int i=0; i < NUM_BUNKERS; i++){
        for (int j=0; j<NUM_SHOOTS; j++) {
            if (bullets[j].active) {
                if (CheckCollisionRecs(bullets[j].destRecBullet, bunkers[i].destRecStructure))
                {
                    bunkers[i].state++;
                    bullets[j].active = false;
                }
            }
        }
    }
}

void SetAliens(Alien *aliens){
    for (int i = 0; i < NUM_ALIENS; i++)
    {
        if (i<11){
            aliens[i].state = 1;
            aliens[i].type = "squid";
            aliens[i].active = true;
            aliens[i].movementX = i*(GAME_SCREEN_WIDTH / 22) +  260;
            aliens[i].posAlienY = 100;
            aliens[i].sourceRecAlien = (Rectangle){0, 0, SQUID_WIDTH, SQUID_HEIGHT};
            aliens[i].destRecAlien = (Rectangle){aliens[i].movementX, aliens[i].posAlienY, aliens[i].sourceRecAlien.width * 4, aliens[i].sourceRecAlien.height * 4};
        }
        else if ((i>=11) & (i<22)){
            aliens[i].state = 1;
            aliens[i].type = "crab";
            aliens[i].active = true;
            aliens[i].movementX = (i-11)*(GAME_SCREEN_WIDTH / 22) +  260;
            aliens[i].posAlienY = 150;
            aliens[i].sourceRecAlien = (Rectangle){0, 0, CRAB_WIDTH, CRAB_HEIGHT};
            aliens[i].destRecAlien = (Rectangle){aliens[i].movementX, aliens[i].posAlienY, aliens[i].sourceRecAlien.width * 4, aliens[i].sourceRecAlien.height * 4};
        }
        else if ((i>=22) & (i<33)){
            aliens[i].state = 1;
            aliens[i].type = "crab";
            aliens[i].active = true;
            aliens[i].movementX = (i-22)*(GAME_SCREEN_WIDTH / 22) +  260;
            aliens[i].posAlienY = 200;
            aliens[i].sourceRecAlien = (Rectangle){0, 0, CRAB_WIDTH, CRAB_HEIGHT};
            aliens[i].destRecAlien = (Rectangle){aliens[i].movementX, aliens[i].posAlienY, aliens[i].sourceRecAlien.width * 4, aliens[i].sourceRecAlien.height * 4};
        }
        else if ((i>=33) & (i<44)){
            aliens[i].state = 1;
            aliens[i].type = "octopus";
            aliens[i].active = true;
            aliens[i].movementX = (i-33)*(GAME_SCREEN_WIDTH / 22) + 260;
            aliens[i].posAlienY = 250;
            aliens[i].sourceRecAlien = (Rectangle){0, 0, OCTOPUS_WIDTH, OCTOPUS_HEIGHT};
            aliens[i].destRecAlien = (Rectangle){aliens[i].movementX, aliens[i].posAlienY, aliens[i].sourceRecAlien.width * 4, aliens[i].sourceRecAlien.height * 4};
        }
        else if ((i>=44) & (i<55)){
            aliens[i].state = 1;
            aliens[i].type = "octopus";
            aliens[i].active = true;
            aliens[i].movementX = (i-44)*(GAME_SCREEN_WIDTH / 22) + 260;
            aliens[i].posAlienY = 300;
            aliens[i].sourceRecAlien = (Rectangle){0, 0, OCTOPUS_WIDTH, OCTOPUS_HEIGHT};
            aliens[i].destRecAlien = (Rectangle){aliens[i].movementX, aliens[i].posAlienY, aliens[i].sourceRecAlien.width * 4, aliens[i].sourceRecAlien.height * 4};
        }
    }
}

void UpdateAliens(Alien *aliens){
    for(int i = 0; i < NUM_ALIENS; i++)
    {
        if ((strcmp(aliens[i].type, "squid") == 0) && (aliens[i].active == true)){
            if (aliens[i].state == 1){
                aliens[i].sourceRecAlien = (Rectangle){0, 0, SQUID_WIDTH, SQUID_HEIGHT};
                DrawTexturePro(squid, aliens[i].sourceRecAlien, aliens[i].destRecAlien, (Vector2){SQUID_WIDTH,0}, 0, WHITE);
            }
            else if (aliens[i].state == 2){
                aliens[i].sourceRecAlien = (Rectangle){8, 0, SQUID_WIDTH, SQUID_HEIGHT};
                DrawTexturePro(squid, aliens[i].sourceRecAlien, aliens[i].destRecAlien, (Vector2){SQUID_WIDTH,0}, 0, WHITE);
            }
            else if (aliens[i].state == 3){
                aliens[i].sourceRecAlien = (Rectangle){16, 0, SQUID_WIDTH, SQUID_HEIGHT};
                DrawTexturePro(squid, aliens[i].sourceRecAlien, aliens[i].destRecAlien, (Vector2){SQUID_WIDTH,0}, 0, WHITE);
            }
        }
        if ((strcmp(aliens[i].type, "crab") == 0) && (aliens[i].active == true)){
            if (aliens[i].state == 1){
                aliens[i].sourceRecAlien = (Rectangle){0, 0, CRAB_WIDTH, CRAB_HEIGHT};
                DrawTexturePro(crab, aliens[i].sourceRecAlien, aliens[i].destRecAlien, (Vector2){CRAB_WIDTH,0}, 0, WHITE);
            }
            else if (aliens[i].state == 2){
                aliens[i].sourceRecAlien = (Rectangle){10, 0, CRAB_WIDTH, CRAB_HEIGHT};
                DrawTexturePro(crab, aliens[i].sourceRecAlien, aliens[i].destRecAlien, (Vector2){CRAB_WIDTH,0}, 0, WHITE);
            }
            else if (aliens[i].state == 3){
                aliens[i].sourceRecAlien = (Rectangle){20, 0, CRAB_WIDTH, CRAB_HEIGHT};
                DrawTexturePro(crab, aliens[i].sourceRecAlien, aliens[i].destRecAlien, (Vector2){CRAB_WIDTH,0}, 0, WHITE);
            }
        }
        if ((strcmp(aliens[i].type, "octopus") == 0) && (aliens[i].active == true)){
            if (aliens[i].state == 1){
                aliens[i].sourceRecAlien = (Rectangle){0, 0, OCTOPUS_WIDTH, OCTOPUS_HEIGHT};
                DrawTexturePro(octopus, aliens[i].sourceRecAlien, aliens[i].destRecAlien, (Vector2){OCTOPUS_WIDTH,0}, 0, WHITE);
            }
            else if (aliens[i].state == 2){
                aliens[i].sourceRecAlien = (Rectangle){11, 0, OCTOPUS_WIDTH, OCTOPUS_HEIGHT};
                DrawTexturePro(octopus, aliens[i].sourceRecAlien, aliens[i].destRecAlien, (Vector2){OCTOPUS_WIDTH,0}, 0, WHITE);
            }
            else if (aliens[i].state == 3){
                aliens[i].sourceRecAlien = (Rectangle){22, 0, OCTOPUS_WIDTH, OCTOPUS_HEIGHT};
                DrawTexturePro(octopus, aliens[i].sourceRecAlien, aliens[i].destRecAlien, (Vector2){OCTOPUS_WIDTH,0}, 0, WHITE);
            }
        }
    }
}

// method to check if the alien is hit by a bullet
void CheckAlien(Bullet *bullets, Alien *aliens){
    for(int i = 0; i < NUM_ALIENS; i++)
    {
        if (aliens[i].active == true){
            for(int j = 0; j < NUM_SHOOTS; j++)
            {
                if (bullets[j].active == true){
                    if (CheckCollisionRecs(aliens[i].destRecAlien, bullets[j].destRecBullet)){
                        if (strcmp(aliens[i].type, "squid") == 0){
                            score += 10;
                        }
                        else if (strcmp(aliens[i].type, "crab") == 0){
                            score += 20;
                        }
                        else if (strcmp(aliens[i].type, "octopus") == 0){
                            score += 40;
                        }
                        aliens[i].active = false;
                        bullets[j].active = false;
                    }
                }
            }
        }
    }
}

void showScore(){
    DrawText(TextFormat("Score: %i", score), 10, 10, 40, WHITE);
}

void showLives(){
    DrawText(TextFormat("Lives: %i", lives), GAME_SCREEN_WIDTH-150, 10, 40, WHITE);
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
    int posPlayerY = GAME_SCREEN_HEIGHT - 50;

    int movementX = 10;
    int movementY = 10;
    bool moveDown = false;
    // declare the array of bullets and initialize them to false
    Bullet bullets[NUM_SHOOTS];
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        bullets[i].active = false;
    }

    Structure bunkers[NUM_BUNKERS];
    SetBunker(bunkers);
    Alien aliens[NUM_ALIENS];
    SetAliens(aliens);

    double tiempo_anterior = GetTime();

    while (!WindowShouldClose())
    {   
        // Calcular el tiempo transcurrido desde el último frame
        double tiempo_actual = GetTime();
        double tiempo_transcurrido = tiempo_actual - tiempo_anterior;

        // Si ha pasado un segundo, aumentar el contador
        if (tiempo_transcurrido >= 0.50) {
            for (int i=0; i<NUM_ALIENS; i++) {
                aliens[i].destRecAlien.x += movementX;
            }

            for (int i=0; i<NUM_ALIENS; i++) {
                if (aliens[i].destRecAlien.x >= GAME_SCREEN_WIDTH - 50) {
                    movementX = -10;
                    moveDown = true;
                }
                else if (aliens[i].destRecAlien.x <= 50) {
                    movementX = 10;
                    moveDown = true;
                }
            }
            if (moveDown) {
                for (int i=0; i<NUM_ALIENS; i++) {
                    aliens[i].destRecAlien.y += movementY; 
                    moveDown = false;
                }
            }
            
            tiempo_anterior = tiempo_actual;
        }

        // check if the player is moving to the left and if it's not going out of the screen
        if (posPlayerX < 0 + PLAYER_WIDTH * 4) posPlayerX = 0 + PLAYER_WIDTH * 4;
        // check if the player is moving to the right and if it's not going out of the screen
        if (posPlayerX > GAME_SCREEN_WIDTH - PLAYER_WIDTH * 4) posPlayerX = GAME_SCREEN_WIDTH - PLAYER_WIDTH * 4;
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
        destRecPlayer = (Rectangle){posPlayerX, posPlayerY, sourceRecPlayer.width * 4, sourceRecPlayer.height * 4};

        BeginDrawing();
            // paint the screen with a black background
            ClearBackground(BLACK);
            // show the player's ship
            DrawTexturePro(player, sourceRecPlayer, destRecPlayer, (Vector2){destRecPlayer.width/2,destRecPlayer.height/2}, 0, green);
            // update the bullets
            UpdateBullets(bullets);
            // check if the bunkers are being hit by the bullets
            CheckBunker(bullets, bunkers);
            // check if the aliens are being hit by the bullets
            CheckAlien(bullets, aliens);
            // update the bunkers
            UpdateBunker(bunkers);
            // update the aliens
            UpdateAliens(aliens);
            // show the score
            showScore();
            // show the lives
            showLives();

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
