#pragma once

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include "EspacosReserva.h"
#include "Cliente.h"

using namespace std;


class Reserva {

private:

	/**
	*	Cont�m a data de in�cio da reserva
	*/
	Date inicio;

	/**
	*	Cont�m a data de fim da reserva
	*/
	Date fim;

	/**
	*	Cont�m o id do cliente que efetuou a reserva
	*/
	int idCliente;

public:

	/**
	*	Contrutor da class Reserva
	*/
	Reserva(int idCliente, Date &inicio, Date &fim);

	/**
	*	Retorna a data de in�cio da reserva
	*/
	Date returnInicio() const;

	/**
	*	Retorna a data de fim da reserva
	*/
	Date returnFim() const;

	/**
	*	Retorna o id do cliente que efetuou a reserva
	*/
	int returnidCliente() const;

	/**
	*	Retorna true se as reservas forem incompativeis, isto �, se n�o puderem existir em simult�neo;
	*/
	bool operator - (Reserva& reserva2);

	/**
	*	Retorna true se as reservas forem iguais, isto �, se as datas de inicio e fim e o id do cliente em ambas forem iguais
	*/
	bool operator == (Reserva& reserva2);

	/**
	*	Usado para exportar toda a informa��o dos objetos desta class para ficheiros de texto
	*/
	friend ostream & operator << (ostream & out, const Reserva & r1);
};

class Reservas {

	/**
	*	Estrutura map que cont�m como primeiro elemento o id de um espa�o e como segundo elemento um vetor de objetos da classe Reserva
	*/
	map <size_t, vector<Reserva>> reservasHotel;

public:

	/**
	*	Construtor da class Reservas (sem par�metros)
	*/
	Reservas();

	/**
	*	Construtor da class Reservas
	*/
	Reservas(vector<Espaco *> espacos);

	/**
	*	Adiciona mais um espa�o e respetivo vetor Reserva � estrutura map
	*/
	void updateReservas(Espaco * espaco);

	/**
	*	Remove um espa�o e respetivo vetor Reserva da estrutura map
	*/
	void removeEspaco(size_t numID);

	/**
	*	Retorna a estrutura map que cont�m todas as reservas efetuadas
	*/
	map <size_t, vector<Reserva>> returnReservas();

	/**
	*	Adiciona uma reserva ao espa�o com id numID
	*/
	bool adicionaReserva(size_t numID, Reserva r1);

	/**
	*	Remove a reserva passada como par�metro do espa�o com id numID
	*/
	bool removeReserva(size_t numID, Reserva r1);

	/**
	*	Altera a reserva rAntiga do espa�o numID para a reserva rNova
	*/
	bool alteraReserva(size_t numID, Reserva rAntiga, Reserva rNova);

	/**
	*	Verifica se existe uma reserva igual a r1 no espa�o de id numID.
	*	Caso exista retorna true, caso contr�rio retorna false
	*/
	bool reservaExiste(size_t numID, Reserva r1);

	/**
	*	Verifica se o espa�o de id numID tem alguma reserva.
	*	Retorna true se estiver, caso contr�rio, retorna false.
	*/
	bool temReservas(size_t numID);

	/**
	*	Verifica se o espa�o de id numID est� ocupado na data d1.
	*	Retorna true se estiver, caso contr�rio, retorna false.
	*/
	bool verificaEspaco(size_t numID, Date d1) const;

	/**
	*	Mostra um calend�rio com a disponibilidade do espa�o de id numID nesse m�s
	*/
	void showMonth(size_t numId, size_t month, size_t year);

};

// -----------------------------------------------------------Exceptions--------------------------------------------------------// 

class EspacoNaoPertenceHotel
{
	/**
	*	Cont�m o numID do espa�o inserido e que n�o pertence ao hotel
	*/
	size_t num_ID;

public:

	/**
	*	Contrutor da exce��o
	*/
	EspacoNaoPertenceHotel(size_t id) {
		num_ID = id;
		cerr << "Espaco de ID:" << num_ID << " nao pertence ao hotel!" << endl;
	}

	/**
	*	Retorna o numID do espa�o inserido e que n�o pertence ao hotel
	*/
	size_t getNumID() const { return num_ID; }
};

class FuncionarioNaoTrabalhaHotel
{
	/**
	*	Cont�m o id do funcion�rio inserido e que n�o pertence ao hotel
	*/
	size_t ID_Code;

public:

	/**
	*	Construtor da exce��o
	*/
	FuncionarioNaoTrabalhaHotel(size_t id) {
		ID_Code = id;
		cerr << "O Funcionario de id:" << ID_Code << " nao trabalha no hotel!" << endl;
	}

	/**
	*	Retorna o id do funcion�rio inserido e que n�o pertence ao hotel
	*/
	size_t getID_Code() const { return ID_Code; }
};

class ClienteNaoEncontrado
{
	/**
	*	Cont�m o nome do Cliente inserido e que n�o foi encontrado
	*/
	string nome;

public:

	/**
	*	Contrutor da exce��o
	*/
	ClienteNaoEncontrado(string nom) {
		nome = nom;
		cerr << "O cliente de nome " << this->nome << " nao consta da nossa lista de clientes!" << endl;
	}

	/**
	*	Retorna o nome do Cliente inserido e que n�o foi encontrado
	*/
	string getNome() const { return nome; }
};

class ClienteDemasiadoNovoReserva
{
	/**
	*	Nome do cliente que � demasiado novo para efetuar uma reserva
	*/
	string nome;

public:

	/**
	*	Contrutor da exce��o
	*/
	ClienteDemasiadoNovoReserva(string nom) {
		nome = nom;
	}

	/**
	*	Retorna o nome do cliente que � demasiado novo para efetuar a reserva
	*/
	string getNome() const { return nome; }
};

class EspacoNaoDisponivel
{
	/**
	*	Cont�m o numID do espa�o que n�o se encontra dispon�vel
	*/
	size_t numID;

public:

	/**
	*	Construtor da exce��o
	*/
	EspacoNaoDisponivel(size_t id) {
		numID = id;
	}
	/**
	*	Retorna o numID do espa�o que n�o se encontra dispon�vel
	*/
	size_t getNumID() const { return numID; }
};

class ReservasCoincidem
{
	/**
	*	Cont�m o numID do espa�o que j� tem uma reserva na data inserida
	*/
	size_t numID;

public:

	/**
	*	Construtor da exce��o
	*/
	ReservasCoincidem(size_t id) {
		numID = id;
		cerr << "O espaco de id = " << this->numID << " ja tem uma reserva nesta data" << endl;
	}
	
	/**
	*	Retorna o numID do espa�o que j� tem uma reserva na data inserida
	*/
	size_t getNum_ID() const { return numID; }
};

class ReservaNaoExiste
{
	/**
	*	Cont�m o numID do espa�o que n�o cont�m nenhuma reserva na data inserida
	*/
	size_t numID;

public:

	/**
	*	Construtor da exce��o
	*/
	ReservaNaoExiste(size_t id) {
		numID = id;
		cerr << "O espaco de id = " << this->numID << " nao tem uma reserva nesta data" << endl;
	}

	/**
	*	Retorna o numID do espa�o que n�o cont�m nenhuma reserva na data inserida
	*/
	size_t getNum_ID() const { return numID; }
};

class NaoHaSupervisores
{
	/**
	*	Cont�m o nome do Hotel onde n�o existe qualquer Supervisor.
	*/
	string nomeHotel;

public:

	/**
	*	Construtor da exce��o
	*/
	NaoHaSupervisores(string nome) { nomeHotel = nome; }

	/**
	*	Retorna o nome do Hotel onde n�o existem Supervisores.
	*/
	string getNomeHotel() const { return nomeHotel; }
};

class DatasInvalidas
{
	/**
	*	Cont�m o id do Cliente que tentou fazer uma reserva com datas inv�lidas.
	*/
	int idCliente;

public:

	/**
	*	Construtor da exce��o
	*/
	DatasInvalidas(int id_cli) { idCliente = id_cli; }

	/**
	*	Retorna o id do Cliente que tentou fazer a reserva inv�lida.
	*/
	int getIdCliente() const { return idCliente; }
};
