#include "ClientServer.h"
using namespace std;

#define PUERTO 666
#define MSG_SIZE 128

int  ServerUDPThread()
{
	bool desconectar = false;

	cout << "Soy un servidor\r\n";

	//A SOCKET is simply a typedef for an unsigned int.
	//In Unix, socket handles were just about same as file 
	//handles which were again unsigned ints.
	//Since this cannot be entirely true under Windows
	//a new data type called SOCKET was defined.
	SOCKET s;

	//WSADATA is a struct that is filled up by the call 
	//to WSAStartup
	WSADATA wsaData;

	//The sockaddr_in specifies the address of the socket
	//for TCP/IP sockets. Other protocols use similar structures.
	sockaddr_in local, other;

	int slen = sizeof(other);


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

	//the socket function creates our SOCKET
	s = socket(AF_INET, SOCK_DGRAM, 0);
	//If the socket() function fails we exit
	if (s == INVALID_SOCKET)
	{
		puts("Error al crear el socket");
		return 0;
	}

	//Now we populate the sockaddr_in structure
	local.sin_family = AF_INET; //Address family
	local.sin_addr.s_addr =  INADDR_ANY; //Wild card IP address
	local.sin_port = htons((u_short)PUERTO); //port to use
	

	//bind links the socket we just created with the sockaddr_in 
	//structure. Basically it connects the socket with 
	//the local address and a specified port.
	//If it returns non-zero quit, as this indicates error
	if (bind(s, (sockaddr*)&local, sizeof(local)) == SOCKET_ERROR)
	{
		puts("error al hacer bind");
		return 0;
	}

	printf("escuchando en puerto %i\n", PUERTO);

	char buf[MSG_SIZE];
	int recv_len;
	while (1)
	{
		//printf("Esperando datos");
		fflush(stdout);

		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', MSG_SIZE);

		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf, MSG_SIZE, 0, (sockaddr *) &other, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			//exit(EXIT_FAILURE);
		}

		if (buf[0] != 0)
		{
			//print details of the client/peer and the data received
			printf("Recibido de %s: %s\n", inet_ntoa(other.sin_addr), buf);
		}
		//printf("Datos: %s\n", buf);

	}
	closesocket(s);
	WSACleanup();
	return 1;
}
