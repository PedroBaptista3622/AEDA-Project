// AEDA-Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Hotel.h"


int main()
{
	Hotel h;

	Cliente cliente1("Pedro", 19);
	Cliente cliente2("Diogo Machado", 19);
	Cliente cliente3("Margarida", 19);

	h.adicionaCliente(&cliente1);
	h.adicionaCliente(&cliente2);
	h.adicionaCliente(&cliente3);

	std::cout << "N Clientes: "<< h.nClientes() << endl;

	h.exportInfo();

    std::cout << "Hello World!\n"; 
}
