// AEDA-Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Hotel.h"

int main()
{
	Hotel h;

	h.adicionaCliente("Pedro", 19);
	h.adicionaCliente("Diogo Machado", 19);
	h.adicionaCliente("Margarida", 19);

	std::cout << "N Clientes: "<< h.nClientes() << endl;

	// h.exportInfo();

    std::cout << "Buildou sem problemas\n"; 
}
