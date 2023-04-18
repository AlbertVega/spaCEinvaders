#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "raylib.h"
#include "Globals.h"
#include "GameWindow.h"

/*
    DECLARE THE TEXTURES FOR ALL SPRITES
*/
Texture2D ovni;
Texture2D squid;
Texture2D crab;
Texture2D octopus; 
Texture2D title;
Font font;

int StartWindow()
{
    InitWindow(START_SCREEN_WIDTH, START_SCREEN_HEIGHT, "Space Invaders");

    Image logo = LoadImage("src/assets/images/logo.png");
    SetWindowIcon(logo);

    SetTargetFPS(60);

    int framesCounter = 0;
    
    ovni = LoadTexture("src/assets/images/ovni.png");
    squid = LoadTexture("src/assets/images/calamar.png");
    crab = LoadTexture("src/assets/images/cangrejo.png");
    octopus = LoadTexture("src/assets/images/pulpo.png");
    title = LoadTexture("src/assets/images/titulo.png");
    font = LoadFont("src/assets/fonts/space_invaders.ttf");

    char *text = (char *) malloc(sizeof(char));

    while (!WindowShouldClose())
    {   
        // verify if the space key is pressed, so the text will be shown again
        if (IsKeyPressed(KEY_SPACE)){
            framesCounter = 0;
        // else the text will be shown normally
        }else{
            framesCounter++;
        }

        Vector2 mousePos = GetMousePosition();

        bool mouseOverText;

        BeginDrawing();
            // paint the screen with a black background
            ClearBackground(BLACK);

            // show the title image "Space Invaders"
            Rectangle sourceRecTitle = (Rectangle){0, 0, TITLE_WIDTH, TITLE_HEIGHT};
            Rectangle destRecTitle = (Rectangle){START_SCREEN_WIDTH/2, START_SCREEN_HEIGHT/6, sourceRecTitle.width * 3, sourceRecTitle.height * 3};
            DrawTexturePro(title, sourceRecTitle, destRecTitle, (Vector2){destRecTitle.width/2,destRecTitle.height/2}, 0, WHITE);

            // show the text "CLICK HERE TO PLAY!"
            text = "CLICK HERE TO PLAY!";
            //check if the mouse is over the text
            mouseOverText = CheckCollisionPointRec(mousePos, (Rectangle) {START_SCREEN_WIDTH/2 - MeasureText(text, 40)/2, START_SCREEN_HEIGHT/3, MeasureText(text, 40), 40 });
            //if the mouse is over the text, show it in green, else show it in white
            if (mouseOverText) {
                
                DrawText(text, START_SCREEN_WIDTH/2 - MeasureText(text, 40)/2, START_SCREEN_HEIGHT/3, 40, green);
                
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    CloseWindow();
                    GameWindow();
                }
            } else {
                DrawText(text, START_SCREEN_WIDTH/2 - MeasureText(text, 40)/2, START_SCREEN_HEIGHT/3, 40, WHITE);
            }

            // show the text "SCORE ADVANCE TABLE"
            text = "*SCORE ADVANCE TABLE*";
            DrawText(text, START_SCREEN_WIDTH/2 - MeasureText(text, 40)/2, START_SCREEN_HEIGHT/2, 40, WHITE);

            //show the ovni
            Rectangle sourceRecOvni = (Rectangle){0, 0, OVNI_WIDTH, OVNI_HEIGHT};
            Rectangle destRecOvni = (Rectangle){START_SCREEN_WIDTH/2 - 150, START_SCREEN_HEIGHT/2 + 80, sourceRecOvni.width * 5, sourceRecOvni.height * 5};
            DrawTexturePro(ovni, sourceRecOvni, destRecOvni, (Vector2){destRecOvni.width/2,destRecOvni.height/2}, 0, RED);
            
            //show the text "MYSTERY"
            DrawText(TextSubtext("= ? MYSTERY", 0, framesCounter/10), START_SCREEN_WIDTH/2 - 80, START_SCREEN_HEIGHT/2 + 60, 40, WHITE);

            //show the squid
            Rectangle sourceRecSquid = (Rectangle){0, 0, SQUID_WIDTH, SQUID_HEIGHT};
            Rectangle destRecSquid = (Rectangle){START_SCREEN_WIDTH/2 - 150, START_SCREEN_HEIGHT/2 + 160, sourceRecSquid.width * 5, sourceRecSquid.height * 5};
            DrawTexturePro(squid, sourceRecSquid, destRecSquid, (Vector2){destRecSquid.width/2,destRecSquid.height/2}, 0, green);

            //show the text "30 POINTS"
            DrawText(TextSubtext("= 30 POINTS", 0, framesCounter/10), START_SCREEN_WIDTH/2 - 80, START_SCREEN_HEIGHT/2 + 140, 40, WHITE);

            //show the crab
            Rectangle sourceRecCrab = (Rectangle){0, 0, CRAB_WIDTH, CRAB_HEIGHT};
            Rectangle destRecCrab = (Rectangle){START_SCREEN_WIDTH/2 - 150, START_SCREEN_HEIGHT/2 + 240, sourceRecCrab.width * 5, sourceRecCrab.height * 5};
            DrawTexturePro(crab, sourceRecCrab, destRecCrab, (Vector2){destRecCrab.width/2,destRecCrab.height/2}, 0, blue);

            //show the text "20 POINTS"
            DrawText(TextSubtext("= 20 POINTS", 0, framesCounter/10), START_SCREEN_WIDTH/2 - 80, START_SCREEN_HEIGHT/2 + 220, 40, WHITE);

            //show the octopus
            Rectangle sourceRecOctopus = (Rectangle){0, 0, OCTOPUS_WIDTH, OCTOPUS_HEIGHT};
            Rectangle destRecOctopus = (Rectangle){START_SCREEN_WIDTH/2 - 150, START_SCREEN_HEIGHT/2 + 320, sourceRecOctopus.width * 5, sourceRecOctopus.height * 5};
            DrawTexturePro(octopus, sourceRecOctopus, destRecOctopus, (Vector2){destRecOctopus.width/2,destRecOctopus.height/2}, 0, pink);

            //show the text "10 POINTS"
            DrawText(TextSubtext("= 10 POINTS", 0, framesCounter/10), START_SCREEN_WIDTH/2 - 80, START_SCREEN_HEIGHT/2 + 300, 40, WHITE);

        EndDrawing();
    }

    free(text);
    UnloadTexture(ovni);
    UnloadTexture(squid);
    UnloadTexture(crab);
    UnloadTexture(octopus);
    UnloadTexture(title);
    UnloadFont(font);
    UnloadImage(logo);

    CloseWindow();        

    return 0;
}