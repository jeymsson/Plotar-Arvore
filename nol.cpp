#include "nol.h"


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

Nol::Nol()
{
    this->Next = NULL;
    this->Back = NULL;
}

Nol::~Nol()
{
}


void Nol::setTexto(string & texto)
{
    ordena();
    if (this->nome1.empty()) {
        this->nome1 = texto;
    } else if (this->nome2.empty()) {
        this->nome2 = texto;
    } else if (this->nome3.empty()) {
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

Nol * Nol::getNext()
{
    return this->Next;
}

Nol * Nol::getBack()
{
    return this->Back;
}

int Nol::getIdade()
{
    return this->Idade;
}

string Nol::getNomes()
{
    this->ordena();
    if(!(this->nome3.empty()) ){
        return string(this->nome1 + ", " + this->nome2 + ", " + this->nome3);
    } else if(!(this->nome2.empty()) ){
        return string(this->nome1 + ", " + this->nome2);
    } else if(!(this->nome1.empty()) ){
        return string(this->nome1);
    }
    return string("");
}

string Nol::getNome(int NumeroNome)
{
    string print;
    this->ordena();

    //NumeroNome nao pode ser < 3, já que tem so 3 nomes
    if(NumeroNome > 0  || NumeroNome < 3){
               if(NumeroNome == 1 ){
            print=  this->nome1;
        } else if(NumeroNome == 2 ){
            print=  this->nome2;
        } else if(NumeroNome == 3 ){
            print=  this->nome3;
        }
    } else {
        print = "";
    }
    return print;
}

void Nol::setNome(int NumeroNome, string texto)
{
    //NumeroNome nao pode ser < 3, já que tem so 3 nomes
    if(NumeroNome > 0  || NumeroNome < 3){
               if(NumeroNome == 1 ){
            this->nome1 = texto;
        } else if(NumeroNome == 2 ){
            this->nome2 = texto;
        } else if(NumeroNome == 3 ){
            this->nome3 = texto;
        }
    } else {
        cout << "Não adicionado numero fora dos limites";
    }
}

