// AEDA-Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Hotel.h"

int main()
{
	ifstream ficheiro;
	string nomeFicheiro;

	cout << "Escreva o nome do ficheiro de onde pretende importar os dados" << endl;
	do {
		cin >> nomeFicheiro;

		if (nomeFicheiro.length() < 4 || nomeFicheiro.substr(nomeFicheiro.length() - 4, 4) != ".txt") {
			nomeFicheiro += ".txt";
		}

		ficheiro.open(nomeFicheiro);

		if (!ficheiro.is_open())
		{
			cerr << "Erro ao abrir o ficheiro, escreva novamente o nome do mesmo" << endl;
			cin.ignore(9999999, '\n');
			cin.clear();
		}

	} while (!ficheiro.is_open());
	
	Hotel h(ficheiro);

	ficheiro.close();

	h.adicionaCliente("Pedro", 19);
	h.adicionaCliente("Diogo Machado", 19);
	h.adicionaCliente("Margarida", 19);

	std::cout << "N Clientes: " << h.nClientes() << endl;
	std::cout << "N Espacos: " << h.nEspacos() << "\n\n";

	// h.exportInfo();

    std::cout << "Buildou sem problemas\n\n"; 

	return 0;
}
