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
	int  retornarAltura(Nol * r);
	int  getWidth(Nol* root, int level);
	
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
	int  getLargura();
	int  getMaxLargura(Nol* root);

	
	

};

#endif // ARVORE_H
