// AEDA-Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Hotel.h"

using namespace std;


#define EXIT_TO_MAIN_MENU	0
#define	EXIT_AND_CLOSE		1
#define ERROR_CODE			2

void clearScreen()
{
	cout << string(100, '\n');
}

bool isInt(string num)
{
	for (size_t i = 0; i < num.length(); i++)
		if (!isdigit(num.at(i)))
			return false;

	return true;
}

void displayVectorEspacos(vector<Espaco *>& vec)
{
	for (size_t i = 0; i < vec.size(); i++) {
		cout << vec.at(i)->getOutputString() << '\n';
	}
}

void auxFazReserva(Hotel& h, int idCliente)
{

	string d_ini_str, m_ini_str, y_ini_str;
	string d_fim_str, m_fim_str, y_fim_str;
	int d_ini, m_ini, y_ini;
	int d_fim, m_fim, y_fim;
	cout << "Para quando pretende efetuar a sua reserva?\n";
	cout << "Data de inicio: dia -> "; cin >> d_ini_str;
	while (!isInt(d_ini_str)) {
		cout << "Valor inserido invalido. Insira de novo: ";
		cin >> d_ini_str;
		cin.ignore();
	}
	d_ini = stoi(d_ini_str);
	cout << "Data de inicio: mes -> "; cin >> m_ini_str;
	while (!isInt(m_ini_str)) {
		cout << "Valor inserido invalido. Insira de novo: ";
		cin >> m_ini_str;
		cin.ignore();
	}
	m_ini = stoi(m_ini_str);
	cout << "Data de inicio: ano -> "; cin >> y_ini_str;
	while (!isInt(y_ini_str)) {
		cout << "Valor inserido invalido. Insira de novo: ";
		cin >> y_ini_str;
		cin.ignore();
	}
	y_ini = stoi(y_ini_str);
	cout << "Data de fim: dia -> "; cin >> d_fim_str;
	while (!isInt(d_fim_str)) {
		cout << "Valor inserido invalido. Insira de novo: ";
		cin >> d_fim_str;
		cin.ignore();
	}
	d_fim = stoi(d_fim_str);
	cout << "Data de fim: mes -> "; cin >> m_fim_str;
	while (!isInt(m_fim_str)) {
		cout << "Valor inserido invalido. Insira de novo: ";
		cin >> m_fim_str;
		cin.ignore();
	}
	m_fim = stoi(m_fim_str);
	cout << "Data de fim: ano -> "; cin >> y_fim_str;
	while (!isInt(y_fim_str)) {
		cout << "Valor inserido invalido. Insira de novo: ";
		cin >> y_fim_str;
		cin.ignore();
	}
	y_fim = stoi(y_fim_str);

	Date data_ini;
	Date data_fim;
	bool datasValidas = false;
	try {
		Date di(d_ini, m_ini, y_ini);
		Date df(d_fim, m_fim, y_fim);
		data_ini = di;
		data_fim = df;
		datasValidas = true;
	}
	catch (CriaDataInvalida e) {
		cerr << "Nao existe a data " << e.getDados() << "!\n";
	}

	if (datasValidas) {
		vector<Espaco*> disp = h.getEspacosDisponiveis(data_ini, data_fim);
		cout << "Estes sao os espacos disponivels para as datas especificadas:\n\n";
		displayVectorEspacos(disp);
		cout << endl;
		cout << "Qual destes espacos pretende escolher? ";
		string reply;
		cin >> reply;
		cin.ignore();
		while (!isInt(reply))
		{
			cout << "Nao inseriu um numero valido. Insira de novo: ";
			cin >> reply;
			cin.ignore();
		}
		int idEsp = stoi(reply);
		bool numValido = false;
		for (size_t i = 0; i < disp.size(); i++) {
			if (disp.at(i)->getNumID() == idEsp) {
				numValido = true;
			}
		}
		if (numValido) {
			cout << "Sera reservado o espaco " << idEsp;
			cout << ", em nome de " << h.getClientes().at(idCliente - 1)->getNome();
			cout << ", entre " << data_ini.getDate();
			cout << " e " << data_fim.getDate();
			cout << ". Pretende confirmar a reserva? (s/n): ";
			cin >> reply;
			cin.ignore();
			while (reply != "s" && reply != "n") {
				cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
				cin >> reply;
				cin.ignore();
			}
			if (reply == "s") {
				if (h.efetuaReserva(h.getClientes().at(idCliente), idEsp, data_ini, data_fim))
					cout << "A sua reserva foi colocada.\n";
				else {
					cout << "Ocorreu um erro na colocacao da sua reserva. Sera agora levado para o menu de cliente.\n";
				}
			}
			else {
				cout << "A sua reserva foi cancelada.\n";
			}
		}
	}
	else {
		cout << "As datas inseridas nao sao validas.\n";
	}

	cout << "Sera agora levado/a de volta para o menu de cliente.\n";
}

void auxVerificaDisponibilidade(Hotel& h)
{
	string d_ini_str, m_ini_str, y_ini_str;
	string d_fim_str, m_fim_str, y_fim_str;
	int d_ini, m_ini, y_ini;
	int d_fim, m_fim, y_fim;
	cout << "Para quando pretende efetuar a sua reserva?\n";
	cout << "Data de inicio: dia -> "; cin >> d_ini_str;
	while (!isInt(d_ini_str)) {
		cout << "Valor inserido invalido. Insira de novo: ";
		cin >> d_ini_str;
		cin.ignore();
	}
	d_ini = stoi(d_ini_str);
	cout << "Data de inicio: mes -> "; cin >> m_ini_str;
	while (!isInt(m_ini_str)) {
		cout << "Valor inserido invalido. Insira de novo: ";
		cin >> m_ini_str;
		cin.ignore();
	}
	m_ini = stoi(m_ini_str);
	cout << "Data de inicio: ano -> "; cin >> y_ini_str;
	while (!isInt(y_ini_str)) {
		cout << "Valor inserido invalido. Insira de novo: ";
		cin >> y_ini_str;
		cin.ignore();
	}
	y_ini = stoi(y_ini_str);
	cout << "Data de fim: dia -> "; cin >> d_fim_str;
	while (!isInt(d_fim_str)) {
		cout << "Valor inserido invalido. Insira de novo: ";
		cin >> d_fim_str;
		cin.ignore();
	}
	d_fim = stoi(d_fim_str);
	cout << "Data de fim: mes -> "; cin >> m_fim_str;
	while (!isInt(m_fim_str)) {
		cout << "Valor inserido invalido. Insira de novo: ";
		cin >> m_fim_str;
		cin.ignore();
	}
	m_fim = stoi(m_fim_str);
	cout << "Data de fim: ano -> "; cin >> y_fim_str;
	while (!isInt(y_fim_str)) {
		cout << "Valor inserido invalido. Insira de novo: ";
		cin >> y_fim_str;
		cin.ignore();
	}
	y_fim = stoi(y_fim_str);

	Date data_ini;
	Date data_fim;
	bool datasValidas = false;
	try {
		Date di(d_ini, m_ini, y_ini);
		Date df(d_fim, m_fim, y_fim);
		data_ini = di;
		data_fim = df;
		datasValidas = true;
	}
	catch (CriaDataInvalida e) {
		cerr << "Nao existe a data " << e.getDados() << "!\n";
	}

	if (datasValidas)
	{
		vector<Espaco*> disp = h.getEspacosDisponiveis(data_ini, data_fim);
		cout << "Estes sao os espacos disponivels para as datas especificadas:\n\n";
		displayVectorEspacos(disp);
	}
	else
	{
		cout << "As datas inseridas nao sao validas.\n";
	}

	cout << "Sera agora levado/a de volta para o menu de cliente.\n";
}

void auxConferePrecos(Hotel& h) {}

void auxCriaHotel() {}

void auxMudaHotel() {}

int atendeCliente()
{
	clearScreen();
	cout << endl;
	cout << "//////////////////////////////////////\n";
	cout << "////      GestHotel - Cliente     ////\n";
	cout << "//////////////////////////////////////\n";
	cout << endl;

	string nomeCliente;
	cout << "Como se chama? ";
	getline(cin, nomeCliente);
	while (!isalpha(nomeCliente.at(0)))
	{
		cout << "Nome invalido. Por favor insira devidamente o seu nome: ";
		getline(cin, nomeCliente);
	}
	string primNome = nomeCliente.substr(0, nomeCliente.find(' '));
	cout << endl;

	string nomeHotel;
	cout << "Escreva o nome do hotel que pretende reservar:" << endl;
	getline(cin, nomeHotel);

	Hotel h(nomeHotel);
	if (h.importAllInfo() != true)
	{
		cout << "A informacao relativa ao hotel " << nomeHotel << " e invalida.\n";
		cout << "A plataforma de cliente sera encerrada.\n";
		return ERROR_CODE;
	}
	cout << endl;

	bool ja_e_cliente = false;
	int idCliente;
	for (size_t i = 0; i < h.getClientes().size(); i++) {
		if (h.getClientes().at(i)->getNome() == nomeCliente) {
			cout << "O seu nome foi encontrado entre os clientes do Hotel.\n";
			cout << "Ja e cliente do hotel " << h.getNomeHotel() << "? (s/n): ";

			string confirm;
			cin >> confirm;
			cin.ignore();
			while (confirm != "s" && confirm != "n")
			{
				cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
				cin >> confirm;
				cin.ignore();
			}

			if (confirm == "s")
			{
				cout << "Para conferir, diga-nos quantos anos tem: ";
				string idade_str;
				cin >> idade_str;
				cin.ignore();
				while (!isInt(idade_str)) {
					cout << "Valor inserido invalido. Insira de novo a sua idade: ";
					cin >> idade_str;
					cin.ignore();
				}
				int idade = stoi(idade_str);
				if (idade == h.getClientes().at(i)->getIdade())
				{
					ja_e_cliente = true;
					idCliente = h.getClientes().at(i)->getIDCliente();
				}

			}
		}
	}
	if (!ja_e_cliente) {
		cout << "Ainda nao e cliente do hotel. Para se inscrever, precisamos apenas da sua idade: ";
		string idade_str;
		cin >> idade_str;
		cin.ignore();
		while (!isInt(idade_str)) {
			cout << "Valor inserido invalido. Insira de novo a sua idade: ";
			cin >> idade_str;
			cin.ignore();
		}
		int idade = stoi(idade_str);
		h.adicionaCliente(nomeCliente, idade);
		idCliente = h.getClientes().at(h.getClientes().size() - 1)->getIDCliente();
	}

	cout << endl;
	cout << "Ola " << primNome << "! Bem-vindo! ";
	cout << "Como podemos ajuda-lo hoje ? \n";
	cout << endl;
	cout << "\tr\t-\tEfetuar uma reserva no hotel " << nomeHotel << ";\n";
	cout << "\tv\t-\tVerificar disponibilidade dos espacos do hotel " << nomeHotel << ";\n";
	cout << "\tp\t-\tConferir a informacao dos precos do hotel " << nomeHotel << ";\n";
	cout << "\ts\t-\tSair da plataforma de cliente.\n";
	cout << endl;

	string reply;
	cout << "Opcao: ";
	cin >> reply;
	cin.ignore();
	bool validInput;
	while (reply != "s") {
		validInput = true;
		if (reply.length() == 1) {
			char rep = reply.at(0);
			switch (rep)
			{
			case 'r':
				cout << endl;
				auxFazReserva(h, idCliente);
				cout << endl;
				break;

			case 'v':
				cout << endl;
				auxVerificaDisponibilidade(h);
				cout << endl;
				break;

			case 'p':
				cout << endl;
				cout << "placeholder: conferir precos;\n";
				cout << endl;
				break;

			case 's':
				break;

			default:
				validInput = false;
				break;
			}
		}
		else
		{
			validInput = false;
		}

		if (!validInput)
		{
			cout << "Por favor insira uma opcao valida!\n\n";
		}

		if (reply != "s") {
			cout << "Como podemos ajuda-lo hoje ? \n";
			cout << endl;
			cout << "\tr\t-\tEfetuar uma reserva no hotel " << nomeHotel << ";\n";
			cout << "\tv\t-\tVerificar disponibilidade dos espacos do hotel " << nomeHotel << ";\n";
			cout << "\tp\t-\tConferir a informacao dos precos do hotel " << nomeHotel << ";\n";
			cout << "\ts\t-\tSair da plataforma de cliente.\n";
			cout << endl;

			cout << "Opcao: ";
			cin >> reply;
			cin.ignore();
		}
	}

	cout << "Obrigado por reservar connosco. Esperamos ve-lo em breve!\n";
	cout << endl;
	cout << "\tm\t-\tSair para o menu principal;\n";
	cout << "\tf\t-\tFechar a plataforma.\n";
	cout << endl;

	string confirm;
	cin >> confirm;
	cin.ignore();
	while (confirm != "m" && confirm != "f")
	{
		cout << "Resposta invalida, por favor insira \"m\" ou \"f\" para responder: ";
		cin >> confirm;
		cin.ignore();
	}
	if (confirm == "m")
	{
		cout << "Saindo para o menu principal.\n";
		cout << "Prima ENTER para encerrar a plataforma de cliente . . .\n";
		cin.ignore();
		clearScreen();
		return EXIT_TO_MAIN_MENU;
	}

	h.exportAllInfo();

	cout << "Prima ENTER para encerrar a plataforma de cliente . . .\n";
	cin.ignore();
	clearScreen();
	return EXIT_AND_CLOSE;
}

int atendeGestor()
{
	clearScreen();
	cout << endl;
	cout << "/////////////////////////////////////\n";
	cout << "////      GestHotel - Gestor     ////\n";
	cout << "/////////////////////////////////////\n";
	cout << endl;

	cout << "Pretende criar um novo hotel, ou modificar um ja existente na plataforma?\n";
	cout << endl;
	cout << "\tc\t-\tCriar um novo hotel;\n";
	cout << "\tm\t-\tModificar um hotel existente;\n";
	cout << "\ts\t-\tSair da plataforma de gestao.\n";
	cout << endl;

	string reply;
	cout << "Opcao: ";
	cin >> reply;
	cin.ignore();
	bool validInput;
	while (reply != "s") {
		validInput = true;
		if (reply.length() == 1) {
			char rep = reply.at(0);
			switch (rep)
			{
			case 'c':
				cout << endl;
				cout << "placeholder: criar hotel;\n";
				cout << endl;
				break;

			case 'm':
				cout << endl;
				cout << "placeholder: modificar hotel;\n";
				cout << endl;
				break;

			case 's':
				break;

			default:
				validInput = false;
				break;
			}
		}
		else
		{
			validInput = false;
		}

		if (!validInput)
		{
			cout << "Por favor insira uma opcao valida!\n\n";
		}

		if (reply != "s") {
			cout << "Pretende criar um novo hotel, ou modificar um ja existente na plataforma?\n";
			cout << endl;
			cout << "\tc\t-\tCriar um novo hotel;\n";
			cout << "\tm\t-\tModificar um hotel existente;\n";
			cout << "\ts\t-\tSair da plataforma de gestao.\n";
			cout << endl;

			cout << "Opcao: ";
			cin >> reply;
			cin.ignore();
		}
	}

	cout << "Obrigado por trabalhar connosco. Esperamos ve-lo em breve!\n";
	cout << endl;
	cout << "\tm\t-\tSair para o menu principal;\n";
	cout << "\tf\t-\tFechar a plataforma.\n";
	cout << endl;

	string confirm;
	cin >> confirm;
	cin.ignore();
	while (confirm != "m" && confirm != "f")
	{
		cout << "Resposta invalida, por favor insira \"m\" ou \"f\" para responder: ";
		cin >> confirm;
		cin.ignore();
	}
	if (confirm == "m")
	{
		cout << "Saindo para o menu principal.\n";
		cout << "Prima ENTER para encerrar a plataforma de cliente . . .\n";
		cin.ignore();
		clearScreen();
		return EXIT_TO_MAIN_MENU;
	}


	cout << "Prima ENTER para encerrar a plataforma de cliente . . .\n";
	cin.ignore();
	clearScreen();
	return EXIT_AND_CLOSE;
}

int mostrarAjuda()
{
	cout << endl;
	cout << "Na plataforma de cliente, e possivel, relativamente a um dos nossos hoteis:\n";
	cout << "\t\t- Efetuar uma reserva;\n";
	cout << "\t\t- Verificar a disponibilidade dos espacos;\n";
	cout << "\t\t- Conferir a informacao de precos.\n";
	cout << endl;
	cout << "Na plataforma de gestao, e possivel:\n";
	cout << "\t\t- Criar um novo hotel, para ser gerido atraves da plataforma;\n";
	cout << "\t\t- Verificar a informacao de um dos hoteis ja existentes na plataforma;\n";
	cout << "\t\t- Modificar a informacao de um dos hoteis previamente adicionados.\n";
	cout << endl;

	return EXIT_TO_MAIN_MENU;
}

bool atendimento()
{
	cout << "/////////////////////////////\n";
	cout << "////      GestHotel      ////\n";
	cout << "/////////////////////////////\n";
	cout << endl;
	cout << "Pretende utilizar a nossa plataforma enquanto cliente, ou enquanto gestor de um dos nossos hoteis?\n";
	cout << endl;
	cout << " [o seu input]\t-\t[acao a realizar]\n";
	cout << "\tc\t-\tutilizar a plataforma de cliente\n";
	cout << "\tg\t-\tutilizar a plataforma de gestao\n";
	cout << "\ta\t-\tobter ajuda\n";
	cout << "\ts\t-\tsair do programa\n\n";

	string reply;
	cout << "Opcao: ";
	cin >> reply;
	cin.ignore();
	bool validInput;
	while (reply != "s") {
		validInput = true;
		if (reply.length() == 1) {
			char rep = reply.at(0);
			int atendeuCliente;
			int atendeuGestor;
			switch (rep)
			{
			case 'c':
				atendeuCliente = atendeCliente();
				if (atendeuCliente == ERROR_CODE)
				{
					cout << "A plataforma de cliente obteve um erro inesperado!\n";
					cout << "Pretende encerrar a plataforma? (s/n): ";
					string confirm;
					cin >> confirm;
					cin.ignore();
					while (confirm != "s" && confirm != "n")
					{
						cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
						cin >> confirm;
						cin.ignore();
					}
					if (confirm == "s")
					{
						cout << "A plataforma sera agora encerrada.\n";
						return false;
					}
				}
				else if (atendeuCliente == EXIT_TO_MAIN_MENU)
				{
					cout << "A plataforma de cliente foi encerrada com sucesso!\n\n";
				}
				else
				{
					cout << "A plataforma de cliente foi encerrada com sucesso!\n";
					reply = "s";
				}
				break;

			case 'g':
				atendeuGestor = atendeGestor();
				if (atendeuGestor == ERROR_CODE)
				{
					cout << "A plataforma de cliente obteve um erro inesperado!\n";
					cout << "Pretende encerrar a plataforma? (s/n): ";
					string confirm;
					cin >> confirm;
					cin.ignore();
					while (confirm != "s" && confirm != "n")
					{
						cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
						cin >> confirm;
						cin.ignore();
					}
					if (confirm == "s")
					{
						cout << "A plataforma sera agora encerrada.\n";
						return false;
					}
				}
				else if (atendeuGestor == EXIT_TO_MAIN_MENU)
				{
					cout << "A plataforma de gestao foi encerrada com sucesso!\n\n";
				}
				else
				{
					cout << "A plataforma de gestao foi encerrada com sucesso!\n";
					reply = "s";
				}
				break;

			case 'a':
				if (mostrarAjuda() != EXIT_TO_MAIN_MENU)
				{
					cout << "Ocorreu um erro ao exibir o painel de ajuda!\n\n";
				}
				break;

			case 's':
				break;

			default:
				validInput = false;
				break;
			}
		}
		else {
			validInput = false;
		}

		if (!validInput)
		{
			cout << "Por favor insira uma opcao valida!\n\n";
		}

		if (reply != "s") {
			cout << "Pretende utilizar a nossa plataforma enquanto cliente, ou enquanto gestor de um dos nossos hoteis?\n";
			cout << endl;
			cout << " [o seu input]\t-\t[acao a realizar]\n";
			cout << "\tc\t-\tUtilizar a plataforma de cliente;\n";
			cout << "\tg\t-\tUtilizar a plataforma de gestao;\n";
			cout << "\ta\t-\tObter ajuda;\n";
			cout << "\ts\t-\tSair do programa.\n\n";

			cout << "Opcao: ";
			cin >> reply;
			cin.ignore();
		}

	}
	cout << "Obrigado por utilizar a nossa plataforma. Esperamos que tenha tido uma boa experiencia!\n";
	cout << "Prima ENTER para encerrar a plataforma . . .\n";
	cin.get();

	return true;
}

int main()
{
	if (atendimento() == false) {
		cout << "Pedimos desculpa pelo incomodo, estamos a trabalhar para reparar a plataforma! :)\n";
		cout << "Prima ENTER para encerrar a plataforma . . .\n";
		cin.ignore();
		cin.get();
	}

	return 0;
}
