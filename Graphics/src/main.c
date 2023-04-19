#include "Game/StartWindow.h"
#include "../../Sockets/Client/client.h"

#include <windows.h>
#include <stdio.h>

DWORD WINAPI ThreadFunc1(LPVOID lpParam) {
    // Código del primer hilo aquí
    StartWindow();
    return 0;
}

DWORD WINAPI ThreadFunc2(LPVOID lpParam) {
    // Código del segundo hilo aquí
    StartClient();
    return 0;
}

int main() {

    printf("Bienvenido a SpaCEInvaders, ¿Desea ser observador o jugador? (O/J): ");
    fgets(message, 1024, stdin);

    if ((strcmp(message, "J\n") == 0) || (strcmp(message, "j\n") == 0))
    {
        HANDLE hThread1, hThread2;

        // Crea el primer hilo
        hThread1 = CreateThread(NULL, 0, ThreadFunc1, NULL, 0, NULL);
        if (hThread1 == NULL) {
            printf("Error al crear el primer hilo\n");
            return 1;
        }

        // Crea el segundo hilo
        hThread2 = CreateThread(NULL, 0, ThreadFunc2, NULL, 0, NULL);
        if (hThread2 == NULL) {
            printf("Error al crear el segundo hilo\n");
            return 1;
        }

        // Espera a que los hilos terminen
        WaitForSingleObject(hThread1, INFINITE);
        WaitForSingleObject(hThread2, INFINITE);

        // Cierra los handles de los hilos
        CloseHandle(hThread1);
        CloseHandle(hThread2);
    }
    else if ((strcmp(message, "O\n") == 0) || (strcmp(message, "o\n") == 0)) == 0)
    {
        printf("aun no implementado");
    }
    else
    {
        printf("Opción no válida");
    }

    return 0;
}
