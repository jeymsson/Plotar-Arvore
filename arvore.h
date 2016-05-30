#ifndef ARVORE_H
#define ARVORE_H

#include "nol.h"
#include <string>
#include "pilha.h"

class Arvore
{
private:
    Nol * mae;
    Nol * raiz;
    int qtd_Nos;

    Pilha * varredura;
    void VLR(Nol * No, Pilha * p);
    void LVR(Nol * No, Pilha * p);
    void LRV(Nol * No, Pilha * p);

    //Altura e largura

    int  getWidth(Nol* root, int level);
    int  getNum_Folhas(Nol* r, int & n);

public:
    Arvore();
    ~Arvore();

    void  expandSentinel(Nol * sentinela);

        //Gets
    Nol * getRaiz();
    Pilha* getVarredura();
    int    getQtd_Nos();
        //Busca
    Nol* Busca_no(int chave);
        //Adição
    void Add_org(int idade, string & nome);
    void Add_No(Nol* No);

        //Vareduras
    void VLR();
    void LVR();
    void LRV();


    int  getAltura();
    int  retornarAltura(Nol * r);
    int  getLargura();
    int  getMaxLargura(Nol* root);
    int  getNum_Folhas();

    void Pop(int chave);
    void clear();

};

#endif // ARVORE_H
