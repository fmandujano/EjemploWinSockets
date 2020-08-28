/// Ejemplo de comunicacion con sockets de windows
/// Basado en el documento "Getting Started with Winsock" 
/// https://msdn.microsoft.com/en-us/library/windows/desktop/ms738545%28v=vs.85%29.aspx
/// Felipe Mandujano, 2015

/// Revisado al 28 de agosto de 2020


#include "ClientServer.h"

int main(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	puts("Opciones:");
	puts("E para ejemplo con servidor en juegodetalento.com:6666\n");
	puts("1 para servidor TCP"); 
	puts("2 para cliente TCP");
	puts("3 para servidor UDP");
	puts("4 para cliente UDP\n");

	int sel = _getch();

	if (sel == 49)
	{
		ServerThread();
	}
	else if (sel == 50)
	{
		ClientThread();
	}
	else if (sel == 51)
	{
		ServerUDPThread();
	}
	else if (sel == 52)
	{
		ClientUDPThread();
	}
	else if (sel == 'e')
	{
		ejemploTCP();
	}
	else

		std::cout << "opcion absurda. matando\n";

	//esperar a cerrar
	system("pause");
	
	return nRetCode;
}