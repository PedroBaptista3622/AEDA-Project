#pragma once

#include <string>
#include <vector>

#include "EspacosReserva.h"

using namespace std;

class Funcionario 
{
	
    string nome;
    size_t ID_Code;
	bool supervisor_status;

public:

	/**
	*	Construtor Funcionarios
	*/
    Funcionario(string nome);

	/**
	*	Destrutor Funcionarios
	*/
	virtual ~Funcionario() {}

	/**
	*	Retorna nome funcionario
	*/
    string getNome() const;

	/**
	*	Retorna id funcionario
	*/
    size_t getID_Code() const;

	/**
	*	Torna funcionario um supervisor
	*/
	void makeSupervisor();

	/**
	*	Retorna se o funcionario � ou n�o supervisor
	*/
	bool isSupervisor() const;

	/**
	*	Usado para verificar se um funcionario � inferior a outro alfabeticamente
	*/
	bool operator<(const Funcionario &f2) const;

	/**
	*	Usado para verificar se um funcionario � superior a outro alfabeticamente
	*/
	//friend bool compA(const Funcionario &f2) const;

	/**
	*	Usado para verificar se o numero de id de umfuncionario � inferior ao de outro
	*/
	//friend bool compId(const Funcionario &f2) const;

	/**
	*	Tentativa de remover os espa�os de um funcion�rio.
	*	Falha se aplicada a um funcion�rio que n�o seja supervisor.
	*/
	virtual void RemoveEspacos();

	/**
	*	Tentativa de adicionar um espa�o a um funcion�rio.
	*	Falha se aplicada a um funcion�rio que n�o seja supervisor.
	*/
	virtual void AcrescentaEspaco(Espaco* espaco);

	/**
	*	Obtem a string a ser exportada para um dado funcionario
	*/
	virtual string getOutputString();

	/**
	*	Usado para exportar informa��o relativa ao objeto para ficheiros
	*/
	friend ostream& operator << (ostream& ofs, Funcionario* func);

	/**
	*	Faz nextWorkerId = 1;
	*/
	static void resetWorkerID();


private:
	static size_t nextWorkerID;

};

class Supervisor : public Funcionario 
{

    vector<Espaco *> Espacos;

public:

	/**
	*	Construtor Funcionarios
	*/
    Supervisor(string nome);

	/**
	*	Adiciona um espaco ao vetor de espacos de que o funcionario est� responsavel
	*/
    void AcrescentaEspaco(Espaco* espaco);

	/**
	*	Remove todos os espacos do vetor de espacos de que o funcionario est� responsavel
	*/
	void RemoveEspacos();

	/**
	*	Retorna um vetor com todos os espacos de que o funcionario � responsavel
	*/
	vector<Espaco *> getLocaisResponsavel() const;

	/**
	*	Passa dados do objeto para string para ser depois exportado para um ficheiro de texto 
	*/
	string getOutputString();

};

class EspacoInexistente    // exception for function RemoveEspaco
{
    size_t num_ID;
public:
    EspacoInexistente(size_t idEspaco) { num_ID = idEspaco; }
    int getNumID() { return num_ID; }
};