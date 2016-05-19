#include "ClientServer.h"

int ClientThread()
{
	std::cout << "Soy un cliente \n";
	
	SOCKET localsocket;
	WSADATA wsaData;
	sockaddr_in server;
	
	int wsaret = WSAStartup(0x101, &wsaData);

	if (wsaret != 0)
	{
		return 0;
	}

	server.sin_family = AF_INET; //Address family
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons((u_short)666); //port to use

	//the socket function creates our SOCKET
	localsocket = socket(AF_INET, SOCK_STREAM, 0);

	//If the socket() function fails we exit
	if (localsocket == INVALID_SOCKET)
	{
		return 0;
	}




	if (connect(localsocket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Error al conectar: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	else
	{
		char buffer[256];
		int retval = send(localsocket, "HOLA", strlen("HOLA"), 0);
		if (retval == SOCKET_ERROR)
		{
			printf("Error al enviar: %d.\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		while (true)
		{

			std::cin.getline(buffer, 256);

			//std::cout << buffer<<"\n";
			
			int retval = send(localsocket, buffer, strlen(buffer), 0);
			if (retval == SOCKET_ERROR)
			{
				printf("Error al enviar: %d.\n", WSAGetLastError());
				WSACleanup();
				return 1;
			}
		}
		/*
		//ahora, recibir el mensaje
		char recvbuf[128]; //mismo tamanio que en el servidor
		int recvbuflen = 128;
		retval = recv(localsocket, recvbuf, recvbuflen, 0);
		//cuidado, aqui tampoco hay manejo de error!
		std::cout << "Servidor dice " << recvbuf << std::endl;


		buffer = " adios";
		retval = send(localsocket, buffer, strlen(buffer), 0);
		//aqui no hay manejo de errores!

		//terminar la conexion
		retval = shutdown(localsocket, SD_SEND);
		if (retval == SOCKET_ERROR) {
			printf("shutdown failed: %d\n", WSAGetLastError());
			closesocket(localsocket);
			WSACleanup();
			return 1;
		}

		*/
	}
	return 0;
}