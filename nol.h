#ifndef NOL_H
#define NOL_H

#include <iostream>
#include <string>

using namespace std;

class Nol {

protected: //Coordenadas de cada no
	int coord_x;
	int coord_y;
private:
	Nol * Next;
	Nol * Back;
	Nol * Pai;
	int Idade;
	string nome1;
	string nome2;
	string nome3;
	int num_strings;
	bool Sentinel;

public:
	Nol();
	~Nol();
	void ordena();
	void setTexto(string & texto);

	void setCoord_x(int x);
	int getCoord_x();
	void setCoord_y(int y);
	int getCoord_y();
	int getNumStrings();
	void verificaNumStrings();

	//Para Pilha
	Nol * getNext();
	Nol * getBack();

	//Para Arvore
	Nol * getLeft();
	Nol * getRight();
	Nol * getPai();
	void setLeft(Nol * left);
	void setRight(Nol * right);
	void setPai(Nol * pai);
	bool isRoot();
	bool isSentinel();

	int getIdade();
	string getNomes();
	string getNome(int NumeroNome);
	void   setNome(int NumeroNome, string texto);

	friend class Pilha;
	friend class Arvore;
};

#endif // NOL_H
