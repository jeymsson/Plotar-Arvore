#ifndef PILHA_H
#define PILHA_H

#include "Nol.h"
#include "funcoes.h"
using namespace std;

class Pilha{

private:
    Nol * Header;
    Nol * Trailer;
    int Num_nos;

    void insert_before(Nol * noh, int idade, string & texto);

    void push_back(int idade, string & nome);
public:
    Pilha();
    ~Pilha();
    Nol * getHeader();
    Nol * getTrailer();
    bool empty();


    void Push_back_Org(int idade, string & nome);
    void Push_back_No(Nol * no);
    void pop_back();
    void remove(Nol * noh);
    void clear();
    Nol* Buscar(int idade);
    string Print();
    int getNum_nos();

};

#endif // PILHA_H
