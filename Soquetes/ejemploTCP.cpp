#include "ClientServer.h"

#define PORT 6666

//Ejemplo de conexión TCP a servidor ubicado en juegodetalento.com:6666
int ejemploTCP()
{
	SOCKET localsocket;
	WSADATA wsaData;
	sockaddr_in server;

	//inicializar subsistema de winsock2 
	int wsaret = WSAStartup(0x101, &wsaData);

	if (wsaret != 0)
	{
		return 1;
	}

	//configurar direccion remota
	server.sin_family = AF_INET; //Address family
	server.sin_addr.s_addr = inet_addr("52.34.131.94");
	server.sin_port = htons((u_short)PORT); //port to use

	// configurar el socket
	localsocket = socket(AF_INET, SOCK_STREAM, 0);
	// comprobar si se pudo crear el socket
	if (localsocket == INVALID_SOCKET)
	{
		return 1;
	}

	std::cout << "Conectando a 52.34.131.94 en el puerto " << PORT << std::endl;
	//conectar a la direccion definida en server
	//si hay error imprimir un mensaje
	if (connect(localsocket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Error al conectar: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	else
	{
		//asignar un buffer de memoria de 256 bytes
		char buffer[256];
		//enviar mensaje con send
		char* mensaje = "hola desde programa en C++\n";
		int retval = send(localsocket, mensaje , strlen(mensaje), 0);
		//si hay error al enviar, mostrarlo
		if (retval == SOCKET_ERROR)
		{
			printf("Error al enviar: %d.\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}
		else
		{
			printf("Mensaje enviado con exito\n");
		}
	}

	return 0;
}