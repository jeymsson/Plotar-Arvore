#include "Arvore.h"



Arvore::Arvore()
{
	this->qtd_Nos = -1;//Seta quantidade de nos

	this->mae = new Nol();// Mae sentinela da raiz
	this->raiz = new Nol();

	expandSentinel(this->mae);
	mae->setRight(getRaiz());
	mae->setLeft(NULL);// Não terá left

	varredura = new Pilha();
}

Arvore::~Arvore()
{
	
}

void Arvore::expandSentinel(Nol * sentinela)
{
	sentinela->setRight(new Nol());
	sentinela->getRight()->setPai(sentinela);
	sentinela->setLeft(new Nol());
	sentinela->getLeft()->setPai(sentinela);
	sentinela->Sentinel = false;
	this->qtd_Nos++;
}

Nol * Arvore::getRaiz()
{
	return this->raiz;
}

Nol * Arvore::Busca_no(int chave)
{
	Nol * temp = getRaiz();
	while (!temp->isSentinel()) {
		if (chave == temp->getIdade()) {
			return temp;
		} else if (chave < temp->getIdade()) {
			temp = temp->getLeft();
		}
		else {
			temp = temp->getRight();
		}
	}
	return temp;
}

void Arvore::Add_org(int idade, string & nome)
{
	if (getRaiz()->isSentinel()) {
		expandSentinel(getRaiz());
		getRaiz()->Idade = idade;
		getRaiz()->setTexto(nome);
	}
	else {
		Nol * buscado = Busca_no(idade);
		Nol * pai = buscado->getPai();

		if (!buscado->isSentinel()) { // Se tiver achado algo
			//Tenta adicionar novo nome
			buscado->setTexto(nome);
		}
		else { //Se não tiver achado nada
			//O buscado´já é a sentinela que vai se adicionar
			expandSentinel(buscado);
			
			//(buscado == pai->getLeft() ? pai->setLeft(novo) : pai->setRight(novo));
			buscado->Idade = idade;
			buscado->setTexto(nome);
		}
	}
	
	
}

void Arvore::VLR()
{
	Pilha * p = new Pilha();
	if (getRaiz()->isSentinel()) {
		p = NULL;
	}
	else {
		VLR(getRaiz(), p);
		getVarredura()->clear();
		this->varredura = p;
	}
	//return p;
}
void Arvore::VLR(Nol * No, Pilha * p)
{
	p->Push_back_No(No);

	if (!No->getLeft()->isSentinel()) {
		VLR(No->getLeft(), p);
	}
	if (!No->getRight()->isSentinel()) {
		VLR(No->getRight(), p);
	}
}

void Arvore::LVR()
{
	Pilha * p = new Pilha();
	if (getRaiz()->isSentinel()) {
		p = NULL;
	}
	else {
		LVR(getRaiz(), p);
		getVarredura()->clear();
		this->varredura = p;
	}
	//return p;
}
void Arvore::LVR(Nol * No, Pilha * p)
{
	if (!No->getLeft()->isSentinel()) {
		VLR(No->getLeft(), p);
	}
	p->Push_back_No(No);

	if (!No->getRight()->isSentinel()) {
		VLR(No->getRight(), p);
	}
}

void Arvore::LRV()
{
	Pilha * p = new Pilha();
	if (getRaiz()->isSentinel()) {
		p = NULL;
	}
	else {
		LRV(getRaiz(), p);
		getVarredura()->clear();
		this->varredura = p;
	}
	//return p;
}
void Arvore::LRV(Nol * No, Pilha * p)
{
	if (!No->getLeft()->isSentinel()) {
		VLR(No->getLeft(), p);
	}
	if (!No->getRight()->isSentinel()) {
		VLR(No->getRight(), p);
	}
	p->Push_back_No(No);

}

Pilha * Arvore::getVarredura()
{
	return this->varredura;
}

int Arvore::getQtd_Nos()
{
	return this->qtd_Nos;
}

int  Arvore::getAltura() {
	Nol * r = getRaiz();
	if (r->isSentinel())
		return -1; // altura de árvore vazia é -1
		//Altura de uma arvore com um so no é 0
	else {
		int he = retornarAltura(r->getLeft());
		int hd = retornarAltura(r->getRight());
		if (he < hd) return hd + 1;
		else return he + 1;
	}
}

int Arvore::retornarAltura(Nol * r) {
	if (r->isSentinel())
		return -1; // altura de árvore vazia é -1
		//Altura de uma arvore com um so no é 0
	else {
		int he = retornarAltura(r->getLeft());
		int hd = retornarAltura(r->getRight());
		if (he < hd) return hd + 1;
		else return he + 1;
	}
}

int Arvore::getLargura()
{
	if (getRaiz()->isSentinel()) {
		return 0;
	}
	else {
		getMaxLargura(getRaiz());
	}
}

int Arvore::getMaxLargura(Nol* root)
{
	int maxLargura = 0;
	int Largura;
	int h = retornarAltura(root) +1;
	int i;

	/* Get width of each level and compare
	the width with maximum width so far */
	for (i = 1; i <= h; i++)
	{
		Largura = getWidth(root, i);
		if (Largura > maxLargura)
			maxLargura = Largura;
	}

	return maxLargura;
}

/* Get width of a given level */
int Arvore::getWidth(Nol* root, int level)
{

	if (root->isSentinel())
		return 0;

	if (level == 1)
		return 1;

	else if (level > 1)
		return getWidth(root->getLeft(), level - 1) +
		getWidth(root->getRight(), level - 1);
}
