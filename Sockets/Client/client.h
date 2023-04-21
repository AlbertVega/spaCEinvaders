#ifndef client_h
#define client_h

#include <stdio.h>
#include <winsock2.h>
#include "cJSON.h"

 WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in server;
    char message[200];
    char server_reply[300];
    cJSON *json;
    cJSON *json2;
// funciones de inicializacion del cliente 
    int winsockInit();
    int socketInit();
    void serverDirection();
    int connectServer();
    void response(char* reply);

    int StartClient();
  


#endif // CLIENT_H 