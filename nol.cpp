#include "nol.h"


Nol::Nol()
{
	this->Next = NULL;
	this->Back = NULL;
	this->Pai = NULL;
	this->Sentinel = true;
	int num_string = 0;
}

Nol::~Nol()
{
}


void Nol::ordena()
{
    if ( !(this->nome3.empty()) ) {
        if (this->nome2.empty()) {
            nome2 = nome3;
            nome3 = "";
        }
        if (this->nome1.empty()) {
            nome1 = nome2;
            nome2 = nome3;
            nome3 = "";
        }
    }

    if ( !(this->nome2.empty()) ) {
        if (this->nome1.empty()) {
            nome1 = nome2;
            nome2 = nome3;
            nome3 = "";
        }
    }
}

void Nol::setTexto(string & texto)
{
	verificaNumStrings();
	ordena();
	if (this->nome1.empty()) {
		this->nome1 = texto;
	}
	else if (this->nome2.empty()) {
		this->nome2 = texto;
	}
	else if (this->nome3.empty()) {
		this->nome3 = texto;
	}
	else {
		cout << "\nNúmero máximo de nomes atingido no Nol";
	}
}

void Nol::setCoord_x(int x)
{
    this->coord_x = x;
}

int Nol::getCoord_x()
{
    return this->coord_x;
}

void Nol::setCoord_y(int y)
{
    this->coord_y = y;
}

int Nol::getCoord_y()
{
    return this->coord_y;
}

int Nol::getNumStrings()
{
	verificaNumStrings();
	return this->num_strings;
}

void Nol::verificaNumStrings()
{
	ordena();
	if (!this->nome3.empty()) {
		this->num_strings = 3;
	}
	else if (!this->nome2.empty()) {
		this->num_strings = 2;
	}
	else if (!this->nome1.empty()) {
		this->num_strings = 1;
	}
	else {
		this->num_strings = 0;
	}
}

Nol * Nol::getNext()
{
    return this->Next;
}

Nol * Nol::getBack()
{
    return this->Back;
}

Nol * Nol::getLeft()
{
    return getBack();
}

Nol * Nol::getRight()
{
    return getNext();
}

Nol * Nol::getPai()
{
    return this->Pai;
}

void Nol::setLeft(Nol * left)
{
    this->Back = left;
}

void Nol::setRight(Nol * right)
{
    this->Next = right;
}

void Nol::setPai(Nol * pai)
{
    this->Pai = pai;
}

bool Nol::isRoot()
{
    return (getPai() == NULL);
}

bool Nol::isSentinel()
{
    ((getLeft() == NULL  &&  getRight() == NULL) ? this->Sentinel = true : this->Sentinel = false);
    return (getLeft() == NULL  &&  getRight() == NULL);
}

int Nol::getIdade()
{
    return this->Idade;
}

string Nol::getNomes()
{
    this->ordena();
    if (!(this->nome3.empty())) {
        return string(this->nome1 + ", " + this->nome2 + ", " + this->nome3);
    }
    else if (!(this->nome2.empty())) {
        return string(this->nome1 + ", " + this->nome2);
    }
    else if (!(this->nome1.empty())) {
        return string(this->nome1);
    }
    return string("");
}

string Nol::getNome(int NumeroNome)
{
    string print;
    this->ordena();

    //NumeroNome nao pode ser < 3, já que tem so 3 nomes
    if (NumeroNome > 0 || NumeroNome < 3) {
        if (NumeroNome == 1) {
            print = this->nome1;
        }
        else if (NumeroNome == 2) {
            print = this->nome2;
        }
        else if (NumeroNome == 3) {
            print = this->nome3;
        }
    }
    else {
        print = "";
    }
    return print;
}

void Nol::setNome(int NumeroNome, string texto)
{
    //NumeroNome nao pode ser < 3, já que tem so 3 nomes
    if (NumeroNome > 0 || NumeroNome < 3) {
        if (NumeroNome == 1) {
            this->nome1 = texto;
        }
        else if (NumeroNome == 2) {
            this->nome2 = texto;
        }
        else if (NumeroNome == 3) {
            this->nome3 = texto;
        }
    }
    else {
        cout << "Não adicionado numero fora dos limites";
    }
}

int Nol::getQtd()
{
    if(getLeft()->isSentinel() && getRight()->isSentinel()){
        return 1;
    } else {
        int Qtd = 0;
        getQtd(this, Qtd);
    }
}

int Nol::getQtd(Nol* No, int Qtd)
{
    Qtd++;
    if(getLeft()->isSentinel() && getRight()->isSentinel()){
        return Qtd;
    } else {
        if(!No->getLeft()->isSentinel()){
            getQtd(No->getLeft(), Qtd);
        }
        if(!No->getRight()->isSentinel()){
            getQtd(No->getRight(), Qtd);
        }

    }
    return Qtd;
}



