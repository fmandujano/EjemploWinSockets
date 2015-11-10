#include "ClientServer.h"
using namespace std;

int  ServerThread()
{
	bool desconectar = false;

	cout << "Soy un servidor\r\n";

	//A SOCKET is simply a typedef for an unsigned int.
	//In Unix, socket handles were just about same as file 
	//handles which were again unsigned ints.
	//Since this cannot be entirely true under Windows
	//a new data type called SOCKET was defined.
	SOCKET server;

	//WSADATA is a struct that is filled up by the call 
	//to WSAStartup
	WSADATA wsaData;

	//The sockaddr_in specifies the address of the socket
	//for TCP/IP sockets. Other protocols use similar structures.
	sockaddr_in local;

	//WSAStartup initializes the program for calling WinSock.
	//The first parameter specifies the highest version of the 
	//WinSock specification, the program is allowed to use.
	int wsaret = WSAStartup(0x101, &wsaData);

	//WSAStartup returns zero on success.
	//If it fails we exit.
	if (wsaret != 0)
	{
		return 0;
	}

	//Now we populate the sockaddr_in structure
	local.sin_family = AF_INET; //Address family
	local.sin_addr.s_addr = INADDR_ANY; //Wild card IP address
	local.sin_port = htons((u_short)666); //port to use

	//the socket function creates our SOCKET
	server = socket(AF_INET, SOCK_STREAM, 0);

	//If the socket() function fails we exit
	if (server == INVALID_SOCKET)
	{
		return 0;
	}

	//bind links the socket we just created with the sockaddr_in 
	//structure. Basically it connects the socket with 
	//the local address and a specified port.
	//If it returns non-zero quit, as this indicates error
	if (bind(server, (sockaddr*)&local, sizeof(local)) != 0)
	{
		return 0;
	}

	puts("escuchando en puerto 666");

	//listen instructs the socket to listen for incoming 
	//connections from clients. The second arg is the backlog
	if (listen(server, 10) == SOCKET_ERROR)
	{
		printf("Listen error %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	puts(" detectoado");

	//we will need variables to hold the client socket.
	//thus we declare them here.
	SOCKET client;
	sockaddr_in from;
	int fromlen = sizeof(from);

	client = accept(server, (struct sockaddr*)&from, &fromlen);
	if (client == INVALID_SOCKET) {
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(server);
		WSACleanup();
		return 1;
	}

	puts("Un vliente se ha conectado");
	char recvbuf[128];  //un buffer de 128 bytes
	int iResult, iSendResult;
	//este es el tamanno del paquete a enviar y recibir
	int recvbuflen = 128;

	do 
	{
		//recibir mensaje
		iResult = recv(client, recvbuf, recvbuflen, 0);
		if (iResult > 0) 
		{
			printf("Bytes recibidos: %d\n", iResult);
			std::cout << "Cliente dice " << recvbuf << std::endl;
			char* msjRespuesta = "mensaje recibido";
			iSendResult = send(client, msjRespuesta, strlen(msjRespuesta), 0);
			//manejo de errores
			if (iSendResult == SOCKET_ERROR) 
			{
				printf("fallo al enviar: %d\n", WSAGetLastError());
				closesocket(client);
				WSACleanup();
				return 1;
			}
			printf("Bytes enviados: %d\n", strlen(msjRespuesta));
		}
		else if (iResult == 0) //significa	que el cliente se ha desconectad
			printf("Cerrando conexion...\n");
		else {
			printf("fallo al recibir: %d\n", WSAGetLastError());
			closesocket(client);
			WSACleanup();
			return 1;
		}
	}while (iResult > 0);
}
