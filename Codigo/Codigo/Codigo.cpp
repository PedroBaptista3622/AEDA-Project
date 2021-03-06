// AEDA-Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Hotel.h"

using namespace std;


#define EXIT_TO_MAIN_MENU	0
#define	EXIT_AND_CLOSE		1
#define ERROR_CODE			2

/**
*	Limpa o ecrã da consola, para evitar confusão entre dados não relacionados.
*/
void clearScreen()
{
	cout << string(100, '\n');
}

/**
*	Verifica se a string passada como argumento é um número inteiro, ou não.
*	Se sim, retorna TRUE. Se não, retorna FALSE.
*/
bool isInt(string num)
{
	for (size_t i = 0; i < num.length(); i++)
		if (!isdigit(num.at(i)))
			return false;

	return true;
}

/**
*	Retorna uma cópia da string passada como argumento, mas apenas com letras minúsculas.
*/
string lowercase(string st)
{
	string ret = "";
	for (size_t i = 0; i < st.length(); i++)
	{
		ret += tolower(st.at(i));
	}
	return ret;
}

/**
*	Mostra na consola a informacão sobre um vector de pointers para objetos do tipo Espaco.
*/
void displayVectorEspacos(vector<Espaco *>& vec)
{
	for (size_t i = 0; i < vec.size(); i++) {
		cout << vec.at(i)->getOutputString() << '\n';
	}
}

/**
*	Adiciona um prato ao menu de um restaurante do hotel
*/
void auxAddPratoRestaurante(Hotel h)
{
	if (h.importInfoRestaurantes()) {

		cout << "Estes sao os restaurantes disponiveis na base de dados do hotel:" << endl;

		cout << endl;
		h.showInfoRestaurantes();
		cout << endl;

		string nome;
		cout << "Qual o nome do restaurante a que pretende adicionar um prato ao menu?";
		getline(cin, nome);
		while (!isalpha(nome.at(0)))
		{
			cout << "Nome invalido. Por favor insira devidamente o seu nome: ";
			getline(cin, nome);
		}
		cout << endl;

		h.addPratoRestaurante(nome);

	}
}

/**
*	Apresenta uma interface através da qual um gestor pode adicionar
*	um restaurante que estaja nas proximidades do hotel à estrutura de dados do representativo hotel.
*/
void auxAdicionaRestaurante(Hotel& h)
{
	string nome;
	cout << "Qual o nome do restaurante a ser adicionado aos dados do hotel " << h.getNomeHotel() << "? ";
	getline(cin, nome);
	while (!isalpha(nome.at(0)))
	{
		cout << "Nome invalido. Por favor insira devidamente o seu nome: ";
		getline(cin, nome);
	}
	cout << endl;


	string tipoCozinha;

	cout << "Qual o tipo de cozinha do restaurante " << nome << "? ";
	getline(cin, tipoCozinha);
	while (!isalpha(tipoCozinha.at(0)))
	{
		cout << "Isso nao e um tipo de cozinha!" << endl << "Por favor insira um tipo valido";
		getline(cin, tipoCozinha);
	}
	cout << endl;


	double distHotel;
	string distHotel_str;
	bool valid = false;

	cout << "Esta quase! So falta saber, a distancia do restaurante ao hotel (em metros): ";
	getline(cin, distHotel_str);

	while (!valid)
	{
		try
		{
			stod(distHotel_str);
			valid = true;
		}
		catch (invalid_argument iArg)
		{
			cout << "O numero que tentou inserir nao e valido, tente outra vez";
			getline(cin, distHotel_str);
		}
		catch (out_of_range oRange)
		{
			cout << "O numero que tentou inserir nao e valido, tente outra vez";
			getline(cin, distHotel_str);
		}
		
	}

	distHotel = stod(distHotel_str);
	
	Restaurante temp(nome, tipoCozinha, distHotel);
	h.addRestaurant(temp);
}

/**
*	Mostra no ecra todos os restautantes proximos do hotel a uma distancia pretendida (ou menos).
*/
void auxRestDist(Hotel h)
{
	double distHotel;
	string distHotel_str;
	bool valid = false;

	cout << "Qual a distancia maxima a que esta disposto a andar? ";
	getline(cin, distHotel_str);
	cout << endl;

	while (!valid)
	{
		try
		{
			stod(distHotel_str);
			valid = true;
		}
		catch (invalid_argument iArg)
		{
			cout << "O numero que tentou inserir nao e valido, tente outra vez";
			getline(cin, distHotel_str);
		}
		catch (out_of_range oRange)
		{
			cout << "O numero que tentou inserir nao e valido, tente outra vez";
			getline(cin, distHotel_str);
		}

	}

	distHotel = stod(distHotel_str);

	vector<Restaurante> todosResultados;

	todosResultados = h.getRestaurantesNMetros(distHotel);

	if (todosResultados.size() == 0)
	{
		cout << "Nao foi encontrado nenhum restaurante a " << distHotel << " metros ou menos do hotel" << endl;
	}
	else
	{
		for (size_t i = 0; i < todosResultados.size(); i++)
		{
			cout << todosResultados.at(i) << endl;
		}
	}

}

/**
*	Mostra no ecra todos os restaurantes proximos do hotel cujo o tipo de cozinha corresponda ao pretendido.
*/
void auxRestTipoComida(Hotel h)
{
	string tipoCozinha;

	cout << "Qual o tipo de cozinha do restaurante que pretende? ";
	getline(cin, tipoCozinha);
	while (!isalpha(tipoCozinha.at(0)))
	{
		cout << "Isso nao e um tipo de cozinha!" << endl << "Por favor insira um tipo valido";
		getline(cin, tipoCozinha);
	}
	cout << endl;

	vector<Restaurante> todosResultados;

	todosResultados = h.getRestaurantesDoTipo(tipoCozinha);

	if (todosResultados.size() == 0)
	{
		cout << "Nao foi encontrado nenhum restaurante com o tipo de cozinha pesquisado" << endl;
	}
	else
	{
		for (size_t i = 0; i < todosResultados.size(); i++)
		{
			cout << todosResultados.at(i) << endl;
		}
	}
}

/**
*	Funcao que complementa a funcao que atende o cliente e trata de dar todas as informacoes disponiveis sobre os restaurantes proximos do hotel.
*/
void auxConsultaRestaurantes(Hotel h)
{

	cout << "\td\t-\tVisualizar restaurantes a cerca de x metros ou menos;\n";
	cout << "\tc\t-\tVisualizar todos os restaurantes com um tipo de comida especifico;\n";
	cout << "\tt\t-\tVisualizar toda a informacao sobre os restaurantes proximos do hotel;\n";
	cout << "\ts\t-\tSair para menu;\n";
	cout << endl;

	string reply;
	cout << "Opcao: ";
	cin >> reply;
	cin.ignore();

	bool validInput = false;

	while (!validInput)
	{
		validInput = true;

		if (reply.length() == 1)
		{
			char rep = reply.at(0);
			switch (rep)
			{
			case 'd':
				cout << endl;
				auxRestDist(h);
				cout << endl;
				break;

			case 'c':

				cout << endl;
				auxRestTipoComida(h);
				cout << endl;
				break;

			case 't':
				cout << endl;
				h.showInfoRestaurantes();
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
			cin >> reply;
			cin.ignore();
		}
	
	}

	cout << '\n';
}

/**
*	Apresenta uma interface através da qual o cliente pode tentar colocar uma reserva.
*	@param h Hotel onde será colocada a reserva.
*	@param idCliente Número de identificacão do cliente que tenta colocar a reserva.
*/
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
			cout << ", em nome de " << h.encontraCliente(idCliente /*- 1*/).getNome(); 
			cout << ", entre " << data_ini.getDate();
			cout << " e " << data_fim.getDate();
			cout << ".\n";

			Reserva res(idCliente, data_ini, data_fim);
			Reservas temp = h.getReservas();
			h.efetuaReserva(&h.encontraCliente(idCliente), idEsp, data_ini, data_fim);
			double precoReserva = h.getPrecoReserva(idEsp, res);

			cout << "A reserva ficara por um total de " << precoReserva << " euros.\n";
			cout << "Pretende confirmar a reserva? (s/n): ";
			cin >> reply;
			cin.ignore();

			while (reply != "s" && reply != "n") 
			{
				cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
				cin >> reply;
				cin.ignore();
			}
			if (reply == "s") 
			{
				cout << "A sua reserva foi colocada.\n";	
			}
			else 
			{
				if (h.removeReserva(idEsp, res))
				{
					cout << "A sua reserva foi cancelada.\n";
				}
				else
				{
					cout << "Erro inesperado" << endl;
				}

			}
		}
	}
	else {
		cout << "As datas inseridas nao sao validas.\n";
	}

	cout << "Sera agora levado/a de volta para o menu de cliente.\n";
}

/**
*	Apresenta uma interface através da qual o cliente pode verificar a disponibilidade dos espacos do hotel:
*	Para isto, pode fornecer um intervalo de datas, e receberá todos os espacos disponíveis para esse período,
*	ou pode pedir a disponibilidade de um determinado espaco num dado mês, sendo que poderá vê-la num calendário.
*/
void auxVerificaDisponibilidade(Hotel& h)
{
	cout << "Como pretende verificar a disponibilidade dos espacos ? \n";
	cout << endl;
	cout << "\td\t-\tVerificar os espacos disponiveis entre duas datas;\n";
	cout << "\tc\t-\tVerificar, no calendario, a disponibilidade de um espaco para um dado mes.\n";
	cout << endl;

	string reply;
	cin >> reply;
	cin.ignore();
	
	while (reply != "d" && reply != "c")
	{
		cout << "Resposta invalida, por favor insira \"d\" ou \"c\" para responder: ";
		cin >> reply;
		cin.ignore();
	}
	if (reply == "d")
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

		cout << endl;
		cout << "Sera agora levado/a de volta para o menu de cliente.\n";
	}
	else
	{
		cout << "Estes sao os espacos que fazem parte do hotel" << h.getNomeHotel() << ":\n\n";
		vector<Espaco*> espacosHotel = h.getTodosEspacos();
		displayVectorEspacos(espacosHotel);
		cout << endl;
		cout << "Qual o id do espaco cuja disponibilidade quer verificar? ";
		string num_esp_str;
		cin >> num_esp_str;
		cin.ignore();
		while (!isInt(num_esp_str)) 
		{
			cout << "Valor inserido invalido. Insira de novo o id do espaco: ";
			cin >> num_esp_str;
			cin.ignore();
		}
		int num_esp = stoi(num_esp_str);
		bool idValid = false;
		for (size_t i = 0; i < h.getTodosEspacos().size(); i++) 
		{
			if (h.getTodosEspacos().at(i)->getNumID() == num_esp)
				idValid = true;
		}
		if (idValid) 
		{
			int mes = 0;
			string mes_str;
			cout << endl;
			cout << "Para quando pretende visualizar a disponibilidade?\n";
			while (mes < 1 || mes > 12) {
				cout << "Mes (1-12): ";
				cin >> mes_str;
				cin.ignore();
				while (!isInt(mes_str)) {
					cout << "Valor inserido invalido. Insira de novo o numero do mes: ";
					cin >> mes_str;
					cin.ignore();
				}
				mes = stoi(mes_str);
			}
			string ano_str;
			cout << "Ano: ";
			cin >> ano_str;
			cin.ignore();
			while (!isInt(ano_str)) {
				cout << "Valor inserido invalido. Insira de novo o ano: ";
				cin >> ano_str;
				cin.ignore();
			}
			int ano = stoi(ano_str);
			h.getReservas().showMonth(num_esp, mes, ano);
		}
		else
		{
			cout << "O espaco de id " << num_esp << " nao existe.\n";
		}

		cout << "Sera agora levado/a de volta para o menu de cliente.\n";
	}
}

/**
*	Apresenta uma tabela de precos relativamente ao hotel em questao.
*/
void auxConferePrecos() 
{
	cout << "Precario para os Quartos, por noite:\n";
	cout << "\tPreco Base: 50 euros\n";
	cout << "\t- Se for Duplo: Preco * 2\n";
	cout << "\t- Se for Single: Nao altera o preco\n";
	cout << "\t- Se for na Frente: Preco * 1.30\n";
	cout << "\t- Aos fins-de-semana: Preco * 1.05\n";
	cout << "\t- Em epoca alta (de Maio a Setembro): Preco * 1.20\n";
	cout << endl;
	cout << "Precario para as Salas de Reunioes, por dia:\n";
	cout << "\tPreco Base:\n";
	cout << "\t\tDe 0 a 29 pessoas: 30 euros\n";
	cout << "\t\tDe 30 a 49 pessoas: 35 euros\n";
	cout << "\t\tDe 50 a 79 pessoas: 50 euros\n";
	cout << "\t\tDe 80 a 119 pessoas: 85 euros\n";
	cout << "\t\tDe 120 a 199 pessoas: 140 euros\n";
	cout << "\t\tDe 200 a 499 pessoas: 250 euros\n";
	cout << "\t\t500 ou mais pessoas: 480 euros\n";
	cout << "\t- Se tiver equipamento de Video: Preco * 1.20\n";
	cout << "\t- Se nao: Nao altera o preco\n";
	cout << "\t- Se tiver equipamento de Audio: Preco * 1.05\n";
	cout << "\t- Se nao: Nao altera o preco\n";
	cout << endl;
}

/**
*	Apresenta uma interface com todas as possibilidades fornecidas a um cliente
*	que use o programa. Nomeadamente, as três funcões auxiliares, apresentadas acima.
*/
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
	cout << "Escreva o nome do hotel que pretende reservar: ";
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

	tabHClientes clientesTemp = h.getClientes();

	for (tabHClientes::const_iterator it = clientesTemp.begin(); it != clientesTemp.end(); it++)
	{
		if (it->getNome() == nomeCliente) 
		{
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

				if (idade == it->getIdade())
				{
					ja_e_cliente = true;
					idCliente = it->getIDCliente();
				}

			}
		}
	}


	if (!ja_e_cliente)
	{
		cout << "Ainda nao e cliente do hotel. Para se inscrever, precisamos apenas da sua idade: ";
		string idade_str;
		cin >> idade_str;
		cin.ignore();

		while (!isInt(idade_str))
		{
			cout << "Valor inserido invalido. Insira de novo a sua idade: ";
			cin >> idade_str;
			cin.ignore();
		}

		int idade = stoi(idade_str);
		h.adicionaCliente(nomeCliente, idade, 9001);

		tabHClientes temp = h.getClientes();
		auto it = temp.begin();

		for (size_t i = 0; i < temp.size() - 1; i++)
		{
			++it;
		}
		//Ultimo Cliente

		idCliente = it->getIDCliente();
	}

	cout << endl;
	cout << "Ola " << primNome << "! Bem-vindo/a! ";
	cout << "Como podemos ajuda-lo/a hoje ? \n";
	cout << endl;
	cout << "\tr\t-\tEfetuar uma reserva no hotel " << nomeHotel << ";\n";
	cout << "\tv\t-\tVerificar disponibilidade dos espacos do hotel " << nomeHotel << ";\n";
	cout << "\th\t-\tConsultar os restaurantes proximos do hotel " << nomeHotel << ";\n";
	cout << "\ta\t-\tReservar lugar num autocarro para visitar os pontos turisticos mais relevantes;\n";
	cout << "\tp\t-\tConferir a informacao dos precos do hotel " << nomeHotel << ";\n";
	cout << "\tm\t-\tConferir a informacao dos autocarros do hotel " << nomeHotel << ";\n";
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
				if (h.encontraCliente(nomeCliente)->getIdade() < 18)
				{
					cout << "E demasiado novo para efetuar uma reserva, apenas pode verificar os precos e a disponibilidade dos espacos." << endl;
					validInput = false;
				}
				else
				{
					auxFazReserva(h, idCliente);
				}
				
				cout << endl;
				break;

			case 'v':
				cout << endl;
				auxVerificaDisponibilidade(h);
				cout << endl;
				break;

			case 'h':
				cout << endl;
				auxConsultaRestaurantes(h);
				cout << endl;
				break;
			case 'a':
				cout << endl;
				h.reservaLugaresAutocarro();
				cout << endl;
				break;
			case 'p':
				cout << endl;
				auxConferePrecos();
				cout << endl;
				break;
			case 'm':
				cout << endl;
				h.showInfoAutocarrosCliente();
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
			cout << "\th\t-\tConsultar os restaurantes proximos do hotel " << nomeHotel << ";\n";
			cout << "\ta\t-\tReservar lugar num autocarro para visitar os pontos turisticos mais relevantes;\n";
			cout << "\tp\t-\tConferir a informacao dos precos do hotel " << nomeHotel << ";\n";
			cout << "\tm\t-\tConferir a informacao dos autocarros do hotel " << nomeHotel << ";\n";
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
		h.exportAllInfo();
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

/**
*	Apresenta uma interface através da qual um gestor pode adicionar
*	um espaco à estrutura de dados representativa do hotel. 
*/
void auxAdicionaEspaco(Hotel& h)
{
	string dado1, dado2, dado3, dado4;

	cout << "Pretende adicionar um Quarto, ou uma Sala de Reunioes? ";
	getline(cin, dado1);
	while (lowercase(dado1) != "quarto" && lowercase(dado1) != "sala de reunioes")
	{
		cout << "Tipo de Espaco invalido. Por favor, insira de novo: ";
		getline(cin, dado1);
	}
	if (lowercase(dado1) == "quarto")
	{
		cout << "Pretende que o Quarto seja duplo? (s/n): ";
		cin >> dado2;
		cin.ignore();
		while (dado2 != "s" && dado2 != "n")
		{
			cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
			cin >> dado2;
			cin.ignore();
		}
		cout << "Pretenda que o Quarto fique na frente? (s/n): ";
		cin >> dado3;
		cin.ignore();
		while (dado3 != "s" && dado3 != "n")
		{
			cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
			cin >> dado2;
			cin.ignore();
		}
		Espaco* esp = new Quarto((dado2 == "s"), (dado3 == "s"));
		h.adicionaEspaco(esp);
	}
	else
	{
		cout << "Pretende que a Sala de Reunioes tenha capacidade para quantas pessoas? ";
		cin >> dado2;
		cin.ignore();
		while (!isInt(dado2)) {
			cout << "Valor inserido invalido. Insira de novo: ";
			cin >> dado2;
			cin.ignore();
		}
		int cap = stoi(dado2);
		cout << "Pretende que a Sala de Reunioes tenha equipamento de Video? (s/n): ";
		cin >> dado3;
		cin.ignore();
		while (dado3 != "s" && dado3 != "n")
		{
			cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
			cin >> dado3;
			cin.ignore();
		}
		cout << "Pretende que a Sala de Reunioes tenha equipamento de Audio? (s/n): ";
		cin >> dado4;
		cin.ignore();
		while (dado4 != "s" && dado4 != "n")
		{
			cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
			cin >> dado2;
			cin.ignore();
		}
		Espaco* esp = new SalaDeReunioes(cap, (dado3 == "s"), (dado4 == "s"));
		h.adicionaEspaco(esp);
	}
}

/**
*	Apresenta uma interface através da qual um gestor pode adicionar
*	um funcionario à estrutura de dados representativa do hotel.
*/
void auxAdicionaFuncionario(Hotel& h)
{
	string nomeFunc;
	cout << "Qual o nome do funcionario a ser adicionado ao hotel " << h.getNomeHotel() << "? ";
	getline(cin, nomeFunc);
	while (!isalpha(nomeFunc.at(0)))
	{
		cout << "Nome invalido. Por favor insira devidamente o seu nome: ";
		getline(cin, nomeFunc);
	}
	string primNome = nomeFunc.substr(0, nomeFunc.find(' '));
	cout << endl;

	string superv;
	cout << primNome << " foi contratado para supervisor/a? (s/n): ";
	cin >> superv;
	cin.ignore();
	while (superv != "s" && superv != "n")
	{
		cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
		cin >> superv;
		cin.ignore();
	}
	if (superv == "s")
	{
		Funcionario* sup = new Supervisor(nomeFunc);
		h.adicionaFuncionario(sup);
	}
	else
	{
		Funcionario* func = new Funcionario(nomeFunc);
		h.adicionaFuncionario(func);
	}

}

/**
*	Apresenta uma interface através da qual um gestor pode adicionar
*	um cliente à estrutura de dados representativa do hotel.
*/
void auxAdicionaCliente(Hotel& h)
{
	string nomeCli;
	cout << "Qual o nome do cliente a ser adicionado aos dados do hotel " << h.getNomeHotel() << "? ";
	getline(cin, nomeCli);
	while (!isalpha(nomeCli.at(0)))
	{
		cout << "Nome invalido. Por favor insira devidamente o seu nome: ";
		getline(cin, nomeCli);
	}
	string primNome = nomeCli.substr(0, nomeCli.find(' '));
	cout << endl;

	string idade_str;
	cout << "Esta quase! So falta saber, quantos anos tem " << primNome << "? ";
	cin >> idade_str;
	while (!isInt(idade_str)) {
		cout << "Valor inserido invalido. Insira de novo a sua idade: ";
		cin >> idade_str;
		cin.ignore();
	}
	int idade = stoi(idade_str);

	h.adicionaCliente(nomeCli, idade, 9001);
}

/**
*	Apresenta uma interface através da qual um gestor pode consultar
*	a informação relativa aos funcionários do hotel.
*/
void auxConsultaInfoFuncionarios(Hotel& h)
{
	cout << "\ta\t-\tVisualizar informacao sobre os funcionarios por ordem alfabetica;\n";
	cout << "\ti\t-\tVisualizar informacao sobre os funcionarios por ordem alfabetica-invertida;\n";
	cout << "\tc\t-\tVisualizar informacao sobre os funcionarios por ordem de codigo id;\n";
	cout << "\ts\t-\tSair, cancelando a operacao de consulta de funcionarios.\n";
	cout << endl;

	string reply;
	cout << "Opcao: ";
	cin >> reply;
	cin.ignore();
	bool validInput = false;
	while (!validInput) {
		validInput = true;
		if (reply.length() == 1)
		{
			char rep = reply.at(0);
			switch (rep)
			{
			case 'a':
				h.sortFuncionariosA();
				cout << endl;
				h.showInfoFuncionarios();
				cout << endl;
				break;
			case 'i':
				h.sortFuncionariosAA();
				cout << endl;
				h.showInfoFuncionarios();
				cout << endl;
				break;
			case 'c':
				h.sortFuncionariosID();
				cout << endl;
				h.showInfoFuncionarios();
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
			cin >> reply;
			cin.ignore();
		}

	}
}

/**
*	Apresenta uma interface através da qual um gestor pode verificar, ou
*	consultar, toda a informacão na estrutura de dados representativa do hotel.
*/
void auxConsultaInfoHotel(Hotel& h)
{
	cout << "Quais os dados acerca dos quais pretende visualizar as informacoes do hotel " << h.getNomeHotel() << "?\n";
	cout << endl;
	cout << "\tc\t-\tVisualizar informacao sobre os clientes;\n";
	cout << "\te\t-\tVisualizar informacao sobre os espacos;\n";
	cout << "\tr\t-\tVisualizar informacao sobre as reservas;\n";
	cout << "\tf\t-\tVisualizar informacao sobre os funcionarios;\n";
	cout << "\th\t-\tVisualizar informacao sobre os restaurantes proximos do hotel;\n";
	cout << "\tm\t-\tConferir a informacao dos autocarros do hotel;\n";
	cout << "\tt\t-\tVisualizar todas as informacoes do hotel;\n";
	cout << "\ts\t-\tSair, cancelando a operacao de consulta.\n";
	cout << endl;

	string reply;
	cout << "Opcao: ";
	cin >> reply;
	cin.ignore();
	bool validInput = false;
	while (!validInput) {
		validInput = true;
		if (reply.length() == 1)
		{
			char rep = reply.at(0);
			switch (rep)
			{
			case 'c':
				cout << endl;
				h.showInfoClientes();
				cout << endl;
				break;
			case 'e':
				cout << endl;
				h.showInfoEspacos();
				cout << endl;
				break;
			case 'r':
				cout << endl;
				h.showInfoReservas();
				cout << endl;
				break;
			case 'f':
				cout << endl;
				auxConsultaInfoFuncionarios(h);
				cout << endl;
				break;
			case 'h':
				cout << endl;
				h.showInfoRestaurantes();
				cout << endl;
				break;
			case 'm':
				cout << endl;
				h.showInfoAutocarrosGestor();
				cout << endl;
				break;

			case 't':	
				cout << endl;
				h.showAllInfo();
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
			cin >> reply;
			cin.ignore();
		}

	}


}

/**
*	Apresenta uma interface com todas as possibilidades fornecidas a um gestor que
*	use o programa. Nomeadamente, as quatro funcões auxiliares, apresentadas acima.
*/
int atendeGestor()
{

	clearScreen();
	cout << endl;
	cout << "/////////////////////////////////////\n";
	cout << "////      GestHotel - Gestor     ////\n";
	cout << "/////////////////////////////////////\n";
	cout << endl;

	string nomeHotel;
	cout << "Escreva o nome do seu hotel: ";
	getline(cin, nomeHotel);

	Hotel h(nomeHotel);
	if (!h.importAllInfo()) 
	{
		cout << "Nao foi encontrada a informacao necessaria para importar nenhum hotel com o nome " << nomeHotel << ".\n";
		cout << "Foi criado o hotel " << nomeHotel << "!\n";
		cout << endl;
	}

	cout << "Como pretende alterar o hotel " << h.getNomeHotel() << "?\n";
	cout << endl;
	cout << "\te\t-\tAdicionar um novo espaco;\n";
	cout << "\tf\t-\tAdicionar um novo funcionario;\n";
	cout << "\tc\t-\tAdicionar um novo cliente;\n";
	cout << "\tr\t-\tAdicionar um novo restaurante nas redondezas do hotel;\n";
	cout << "\tp\t-\tAdicionar um novo prato ao menu de um restaurante nas redondezas do hotel;\n";
	cout << "\ta\t-\tAdicionar um novo autocarro a lista de autocarros do hotel;\n";
	cout << "\ti\t-\tConsultar a informacao armazenada sobre o hotel " << h.getNomeHotel() << ";\n";
	cout << "\ts\t-\tSair da plataforma de gestao.\n";
	cout << endl;

	string reply;
	cout << "Opcao: ";
	cin >> reply;
	cin.ignore();
	bool validInput;
	while (reply != "s") {
		validInput = true;
		if (reply.length() == 1)
		{
			char rep = reply.at(0);
			switch (rep)
			{
			case 'e':
				cout << endl;
				auxAdicionaEspaco(h);
				cout << endl;
				break;
			case 'f':
				cout << endl;
				auxAdicionaFuncionario(h);
				cout << endl;
				break;
			case 'c':
				cout << endl;
				auxAdicionaCliente(h);
				cout << endl;
				break;
			case 'r':
				cout << endl;
				auxAdicionaRestaurante(h);
				cout << endl;
				break;
			case 'p':
				cout << endl;
				auxAddPratoRestaurante(h);
				cout << endl;
				break;
			case 'a':
				cout << endl;
				h.addAutocarro();
				cout << endl;
				break;
			case 'i':
				cout << endl;
				auxConsultaInfoHotel(h);
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
			cout << "Como pretende alterar o hotel " << h.getNomeHotel() << "?\n";
			cout << endl;
			cout << "\te\t-\tAdicionar um novo espaco;\n";
			cout << "\tf\t-\tAdicionar um novo funcionario;\n";
			cout << "\tc\t-\tAdicionar um novo cliente;\n";
			cout << "\tr\t-\tAdicionar um novo restaurante nas redondezas do hotel;\n";
			cout << "\tp\t-\tAdicionar um novo prato ao menu de um restaurante nas redondezas do hotel;\n";
			cout << "\ta\t-\tAdicionar um novo autocarro a lista de autocarros do hotel;\n";
			cout << "\ti\t-\tConsultar a informacao armazenada sobre o hotel " << h.getNomeHotel() << ";\n";
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
		h.exportAllInfo();
		cout << "Saindo para o menu principal.\n";
		cout << "Prima ENTER para encerrar a plataforma de gestao . . .\n";
		cin.ignore();
		clearScreen();
		return EXIT_TO_MAIN_MENU;
	}

	h.exportAllInfo();
	cout << "Prima ENTER para encerrar a plataforma de gestao . . .\n";
	cin.ignore();
	clearScreen();
	return EXIT_AND_CLOSE;
}

/**
*	Mostra na consola todas as possibilidades fornecidas em cada um dos modos do programa.
*/
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

/**
*	Funcão principal da interface. Trata toda a interacão entre o utilizador e
*	as estruturas de dados. Todas as funcões neste ficheiro servem de auxiliares
*	a esta.
*/
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
