/// Ejemplo de comunicacion con sockets de windows
/// Basado en el documento "Getting Started with Winsock" 
/// https://msdn.microsoft.com/en-us/library/windows/desktop/ms738545%28v=vs.85%29.aspx
/// Felipe Mandujano, 2015


#include "ClientServer.h"

int main(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	std::cout << "Escribe 1 para servidor, 2 para cliente \n";

	int sel = _getch();

	if (sel == 49)
	{
		ServerThread();
	}
	else if (sel == 50)
	{
		ClientThread();
	}
	else
		std::cout << "opcion absurda. matando\n";

	//esperar a cerrar
	system("pause");
	
	return nRetCode;
}