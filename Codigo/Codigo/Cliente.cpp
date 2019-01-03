#include "Cliente.h"

int Cliente::nextClientID = 1;

//teste

Cliente::Cliente(string nome, int idade) : idCliente(nextClientID++)
{
	this->nome = nome;
	this->idade = idade;
	freqReserva = 0;
}

string Cliente::getNome() const
{
	return this->nome;
}

int Cliente::getIdade() const
{
	return this->idade;
}

int Cliente::getIDCliente() const
{
	return this->idCliente;
}

int Cliente::getFreqReserva() const
{
	return this->freqReserva;
}

int Cliente::getNextClientID()
{
	return nextClientID;
}

void Cliente::registaReserva()
{
	freqReserva++;
}

void Cliente::decNReservas()
{
	freqReserva--;
}

ostream& operator << (ostream& ofs, const Cliente *cliente)
{
	ofs << cliente->getIDCliente() << "; " << cliente->getNome() << "; " << cliente->getIdade() << " anos; " << cliente->getFreqReserva() << " reservas feitas";
	return ofs;
}

bool Cliente::operator==(const Cliente &c2) const
{
	if ((this->getNome() == c2.getNome()) && (this->getIDCliente() == c2.getIDCliente()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Cliente::resetNextClientID()
{
	nextClientID = 1;
}

void Cliente::setNextClientID(int novoID)
{
	nextClientID = novoID;
}

void Cliente::setID(size_t id)
{
	this->idCliente = id;
}