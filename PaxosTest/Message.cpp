#include "Message.h"
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>


void Message::start() {
    
}

int Message::sendMessage(Proposal *proposal, unsigned short port)
{
    
    WSADATA wsaData;
    SOCKET conn_socket;
    struct sockaddr_in server;
    struct hostent* hp;
    int resp;

    //Inicializamos la DLL de sockets
    resp = WSAStartup(MAKEWORD(1, 0), &wsaData);
    if (resp) {
        printf("Error al inicializar socket\n");
        return MSG_ERROR_INITIALIZATION_SOCKET;
    }

    //Obtenemos la IP del servidor... en este caso
    // localhost indica nuestra propia máquina...
    hp = (struct hostent*)gethostbyname("localhost");

    if (!hp) {
        printf("No se ha encontrado servidor...\n");
        WSACleanup(); return MSG_ERROR_UNKNOWN_SERVER;
    }

    // Creamos el socket...
    conn_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (conn_socket == INVALID_SOCKET) {
        printf("Error al crear socket\n");
        WSACleanup(); return MSG_ERROR_CREATE_SOCKET;
    }

    memset(&server, 0, sizeof(server));
    memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
    server.sin_family = hp->h_addrtype;
    server.sin_port = htons(port);

    // Nos conectamos con el servidor...
    if (connect(conn_socket, (struct sockaddr*) & server, sizeof(server)) == SOCKET_ERROR) {
        printf("Fallo al conectarse con el servidor\n");
        closesocket(conn_socket);
        WSACleanup(); return MSG_ERROR_FAILED_TO_CONNECT_SERVER;
    }
    
    memcpy(SendBuff, reinterpret_cast<const char *>(proposal), sizeof(Proposal));
    printf("[Sent]Proposal[%d.%d, %s]\n", proposal->get_proposal_number(), proposal->get_id(), proposal->get_value().c_str());
    send(conn_socket, SendBuff, sizeof(Proposal), 0);    

    // Cerramos el socket y liberamos la DLL de sockets
    closesocket(conn_socket);
    WSACleanup();
    return EXIT_SUCCESS;
}

int Message::receiveMessage(Proposal *proposal, unsigned short port)
{
    WSADATA wsaData;
    SOCKET conn_socket, comm_socket;
    //SOCKET comunicacion;
    struct sockaddr_in server;
    struct sockaddr_in client;
    struct hostent* hp;
    int resp, stsize;

    //Inicializamos la DLL de sockets
    resp = WSAStartup(MAKEWORD(1, 0), &wsaData);
    if (resp) {
        printf("Error al inicializar socket\n");
        return MSG_ERROR_INITIALIZATION_SOCKET;
    }

    //Obtenemos la IP que usará nuestro servidor... 
    // en este caso localhost indica nuestra propia máquina...
    hp = (struct hostent*)gethostbyname("localhost");

    if (!hp) {
        printf("No se ha encontrado servidor...\n");
        WSACleanup(); return MSG_ERROR_UNKNOWN_SERVER;
    }

    // Creamos el socket...
    conn_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (conn_socket == INVALID_SOCKET) {
        printf("Error al crear socket\n");
        WSACleanup(); return MSG_ERROR_CREATE_SOCKET;
    }

    memset(&server, 0, sizeof(server));
    memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
    server.sin_family = hp->h_addrtype;
    server.sin_port = htons(port);

    // Asociamos ip y puerto al socket
    resp = bind(conn_socket, (struct sockaddr*) & server, sizeof(server));
    if (resp == SOCKET_ERROR) {
        printf("Error al asociar puerto e ip al socket\n");
        closesocket(conn_socket); WSACleanup();
        return MSG_ERROR_TO_ASSOCIATE_PORT_AND_IP_SOCKET;
    }

    if (listen(conn_socket, 1) == SOCKET_ERROR) {
        printf("Error al habilitar conexiones entrantes\n");
        closesocket(conn_socket); WSACleanup();
        return MSG_ERROR_TO_ENABLE_INGOING_CONNECTIONS;
    }

    // Aceptamos conexiones entrantes
    //printf("Esperando conexiones entrantes... \n");
    stsize = sizeof(struct sockaddr);
    comm_socket = accept(conn_socket, (struct sockaddr*) & client, &stsize);
    if (comm_socket == INVALID_SOCKET) {
        printf("Error al aceptar conexión entrante\n");
        closesocket(conn_socket); WSACleanup();
        return MSG_ERROR_TO_ACCEPT_INGOING_CONNECTIONS;
    }
    
    // Como no vamos a aceptar más conexiones cerramos el socket escucha
    closesocket(conn_socket);
    

    //printf("Recibiendo Mensaje... \n");
    recv(comm_socket, RecvBuff, sizeof(RecvBuff), 0);
    proposal = reinterpret_cast<Proposal*>(RecvBuff);
    printf("[Received]Proposal[%d.%d, %s]\n", proposal->get_proposal_number(), proposal->get_id(), proposal->get_value().c_str());
    // Cerramos el socket de la comunicacion
    closesocket(comm_socket);

    // Cerramos liberia winsock
    WSACleanup();
    return (EXIT_SUCCESS);
}
