#include "raylib.h"
#include <string.h>

int Prueba()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Ejemplo de mostrar texto letra por letra");

    SetTargetFPS(2); // Establece la tasa de actualización a medio segundo (2 fps)

    const char* texto = "Hola, mundo!";
    int longitudTexto = MeasureText(texto, 20);

    int letraActual = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (letraActual < strlen(texto))
        {
            char letra = texto[letraActual];

            DrawText(TextSubtext(texto, 0, letraActual), screenWidth/2 - longitudTexto/2, screenHeight/2 - 20, 20, BLACK); // Dibuja el texto hasta la letra actual

            letraActual++;

            if (letraActual < strlen(texto))
            {
                // Espera medio segundo antes de continuar
                for (int i = 0; i < 30; i++) // 2 fps * 30 frames = 1 segundo
                {
                    if (i == 0) DrawText(TextFormat("%c", letra), screenWidth/2 - longitudTexto/2 + MeasureText(TextSubtext(texto, 0, letraActual), 20), screenHeight/2 - 20, 20, BLACK); // Dibuja la letra actual
                    DrawText(TextSubtext(texto, 0, letraActual), screenWidth/2 - longitudTexto/2, screenHeight/2 - 20, 20, BLACK); // Dibuja el texto hasta la letra actual
                    DrawFPS(0, 0);
                    EndDrawing();
                }
            }
        }
        else
        {
            DrawText(texto, screenWidth/2 - longitudTexto/2, screenHeight/2 - 20, 20, BLACK); // Dibuja todo el texto si ya se ha mostrado completamente
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}