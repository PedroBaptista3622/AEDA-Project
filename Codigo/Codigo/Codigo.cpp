// AEDA-Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Hotel.h"

using namespace std;

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

	cin.ignore(1000, '\n');
	string nomeHotel;
	cout << "\nEscreva o nome do hotel que pretende reservar:" << endl;
	getline(cin, nomeHotel);

	Hotel h(nomeHotel, ficheiro);

	ficheiro.close();

	h.adicionaCliente("Pedro", 19);
	h.adicionaCliente("Diogo Machado", 19);
	h.adicionaCliente("Margarida", 19);

	cout << "N Clientes: " << h.nClientes() << endl;
	cout << "N Espacos: " << h.nEspacos() << "\n\n";

	Date d1(23, 11, 2018);
	Date d2(26, 11, 2018);
	Date d3(28, 11, 2018);
	Date d4(29, 11, 2018);
	h.efetuaReserva(h.getClientes().at(1), 4, d1, d2);
	h.efetuaReserva(h.getClientes().at(1), 4, d3, d4);

	Funcionario* f1 = new Funcionario("Omar Salgado");
	Funcionario* f2 = new Supervisor("Jacinto Leite");
	Funcionario* f3 = new Supervisor("Adolfo Dias");
	h.adicionaFuncionario(f1);
	h.adicionaFuncionario(f2);
	h.adicionaFuncionario(f3);
	h.alocaSupervisores();

	h.exportInfoClientes();
	h.exportInfoEspacos();
	h.exportInfoReservas();
	h.exportInfoFuncionarios();

    cout << "\nBuildou sem problemas\n"; 

	cout << "\nPrima ENTER para sair do programa . . .";
	cin.ignore(9999999, '\n');
	cin.clear();

	return 0;
}
