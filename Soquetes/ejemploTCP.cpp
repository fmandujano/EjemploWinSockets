#include "ClientServer.h"

#define PORT 6666

//Ejemplo de conexión TCP a servidor ubicado en monsterballgo.com:6666
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

	std::cout << "Cliente Conectando a 52.34.131.94 en el puerto " << PORT << std::endl; 
	//conectar a la direccion definida en server
	//si hay error imprimir un mensaje
	if (connect(localsocket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		//traducir codigo de error a algo legible
		wchar_t* strerror = NULL;
		int errorcode = WSAGetLastError();
		FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorcode,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			strerror,
			0, NULL);

		std::cout << "Error al conectar: " << strerror << std::endl;
		WSACleanup();
		return 1;
	}
	else
	{
		//asignar un buffer de memoria de 256 bytes
		char buffer[256];
		//enviar mensaje con send
		char* mensaje = "PLAYERPOS(x=123.234234,y=23423.23,z=56546)\n";
		int retval = send(localsocket, mensaje , strlen(mensaje), 0);
		//si hay error al enviar, mostrarlo
		if (retval == SOCKET_ERROR)
		{
			//traducir numero de error a string humanamente legible
			wchar_t* strerror = NULL;
			int errorcode = WSAGetLastError();
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, errorcode,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				strerror, 
				0, NULL);

			std::cout << "2Error al conectar: " << strerror << std::endl;

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