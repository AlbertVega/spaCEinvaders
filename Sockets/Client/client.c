#include "client.h"
#include <windows.h>

int winsockInit(){
  if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        printf("Error: no se pudo inicializar Winsock\n");
        return 1;
    } else {
        return 0;
    }
}
int socketInit(){
  sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Error: no se pudo crear el socket\n");
        return 1;
    } else {
        return 0;
    }
}
void serverDirection(){
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Dirección IP del servidor
    server.sin_family = AF_INET; // Familia de direcciones (IPv4)
    server.sin_port = htons(8080); // Puerto del servidor
}

int connectServer(){
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Error: no se pudo conectar con el servidor\n");
        return 1;
    } else {
        printf("Conexión establecida\n");
        return 0;
    }
}

DWORD WINAPI listener(LPVOID lpParam){
    while(TRUE){
        if (recv(sock, server_reply, 300, 0) < 0) {
            printf("Error: no se pudo recibir la respuesta del servidor\n");
            return 1;
        }
    //ACA EL STRING QUE LLEGA LO VUELVE A CREAR .JSON
        
        json2 = cJSON_Parse(server_reply);
        printf("Respuesta del servidor: %s\n", server_reply);
        char* json_string2 = cJSON_Print(json2);
        printf("Respuesta del servidor with parser %s\n", json_string2);        
        if(strcmp(json_string2, "exit") == 0){
            break;
        }
    }
    return 0;
}

int response(char* reply){
    printf("Respuesta del servidor: %s\n", reply);
    json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "mensaje", reply);
    char* json_string = cJSON_Print(json);
    strcat(json_string, "\n");
    printf("Mensaje JSON xd: %s \n" , json_string);
        if (send(sock, json_string, strlen(json_string), 0) < 0) {
            printf("Error: no se pudo enviar el mensaje\n");
            return 1;
        }
        else{
            printf("Mensaje enviado\n");
            return 0;
        }

}

int StartClient() {

    winsockInit();
    socketInit();
    serverDirection();
    connectServer();
    HANDLE Thread1;
    Thread1 = CreateThread(NULL, 0, listener, NULL, 0, NULL);
    //Thread2 = CreateThread(NULL, 0, sender, NULL, 0, NULL);
    if (Thread1 == NULL) {
        printf("Error al crear el primer hilo\n");
        return 1;
    }

    while (TRUE)
    {
        // Crear un objeto cJSON con el campo "mensaje" y su valor ingresado por el usuario
        printf("Ingrese el mensaje: ");
        fgets(message, 1024, stdin);
        message[strcspn(message, "\n")] = 0; // Eliminar el salto de línea al final del mensaje
       /* json = cJSON_CreateObject();
         //ACA SE AGREGAN LOS CAMPOS JSON
        cJSON_AddStringToObject(json, "mensaje", message);
        char* json_string = cJSON_Print(json);
        strcat(json_string, "\n");
        printf("Mensaje JSON: %s \n" , json_string);

        if (send(sock, json_string, strlen(json_string), 0) < 0) {
            printf("Error: no se pudo enviar el mensaje\n");
            return 1;
        }
        if (strcmp(message, "exit") == 0)
        {
            WaitForSingleObject(Thread1, INFINITE);            
            CloseHandle(Thread1);
            break;
        }*/
        response(message);
        printf("Mensaje enviado\n");
        // Recibir datos del servidor
        /*if (recv(sock, server_reply, 300, 0) < 0) {
            printf("Error: no se pudo recibir la respuesta del servidor\n");
            return 1;
        }
        //ACA EL STRING QUE LLEGA LO VUELVE A CREAR .JSON
        
        json2 = cJSON_Parse(server_reply);
        printf("Respuesta del servidor: %s\n", server_reply);
        char* json_string2 = cJSON_Print(json2);
        printf("Respuesta del servidor with parser %s\n", json_string2);*/
    }
    // Cerrar el socket
    closesocket(sock);
    WSACleanup();

    return 0;
}