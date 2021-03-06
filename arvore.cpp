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
    clear();
    delete this->raiz;
    delete this->mae;
    delete this->varredura;

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

void Arvore::Add_No(Nol *No)
{
    if(getRaiz()->isSentinel()){
        this->raiz = No;
        No->setPai(NULL);
    } else {
        for(int i = 0; i < No->getNumStrings(); i ++){
            Add_org(No->getIdade(), No->getNome(i+1));
        }
    }
}



void Arvore::VLR()
{
	Pilha * p = new Pilha();
	if (getRaiz()->isSentinel()) {
		p = NULL;
        this->varredura->clear();
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
        this->varredura->clear();
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
		LVR(No->getLeft(), p);
	}
	p->Push_back_No(No);

	if (!No->getRight()->isSentinel()) {
		LVR(No->getRight(), p);
	}
}

void Arvore::LRV()
{
	Pilha * p = new Pilha();
	if (getRaiz()->isSentinel()) {
		p = NULL;
        this->varredura->clear();
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
		LRV(No->getLeft(), p);
	}
	if (!No->getRight()->isSentinel()) {
		LRV(No->getRight(), p);
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
    int largura;
	if (getRaiz()->isSentinel()) {
		return 0;
	}
	else {
        largura = getMaxLargura(getRaiz());
	}
    return largura;
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

int  Arvore::getNum_Folhas() {
    Pilha *p = new Pilha;
    int n = 0;
    if (getRaiz()->isSentinel()) {
        cout << "Raiz vazia";
    }
    else {
        n = getNum_Folhas(getRaiz(), n);
    }
    return n;
}

int  Arvore::getNum_Folhas(Nol* r, int & n) {
    if (getRaiz()->isSentinel()) {
        cout << "\nRaiz vazia" << endl;
    }
    else {
        if (r->getLeft()->isSentinel() &&  r->getRight()->isSentinel()) {
            n++;
        }
        if (!r->getLeft()->isSentinel()) {
            getNum_Folhas(r->getLeft(), n);
        }

        if (!r->getRight()->isSentinel()) {
            getNum_Folhas(r->getRight(), n);
        }
    }
    return n;
}

//Pop Vazio
void Arvore::Pop(int chave)
{
    Nol * sentinel = NULL;
    Nol * rem = Busca_no(chave);
    if (rem->isSentinel()) {//Se nao achou
        return;
    }
    else { // se achou

        Nol* esq = rem->getLeft();
        Nol* dir = rem->getRight();

        if (!rem->isRoot()) {
            Nol* pai = rem->getPai();

            Nol* folha;
            int i = 0;
            if (pai->getLeft() == rem) {
                folha = dir;
                if (folha->isSentinel()) {
                    folha = esq;
                }
                pai->setLeft(folha);
                folha->setPai(pai);

                folha = dir;  // Re-seta o folha
                if (!folha->isSentinel()) {
                    while (!folha->getLeft()->isSentinel()) {
                        folha = folha->getLeft();
                    }
                    folha->setLeft(esq);
                    esq->setPai(folha);
                    //cin >> i;
                }
                else {
                    sentinel = dir;
                }
            }
            else {
                folha = esq;
                if (folha->isSentinel()) {
                    folha = dir;
                }
                pai->setRight(folha);
                folha->setPai(pai);

                folha = esq;
                if(!folha->isSentinel()){
                    while (!folha->getRight()->isSentinel()) {
                        folha = folha->getRight();
                    }
                    folha->setRight(dir);
                    dir->setPai(folha);
                    //cin >> i;
                }
                else {
                    sentinel = esq;
                }
            }

        }
        else { // Se o removido for a raiz
            Nol* esq = rem->getLeft();
            Nol* dir = rem->getRight();

            if (esq->isSentinel() && dir->isSentinel()) {  // Se so tem um no
                sentinel = esq;
                this->raiz = dir;
            }
            else {
                Nol* folha = dir;

                if (!folha->isSentinel()) {
                    while (!folha->getLeft()->isSentinel()) {
                        folha = folha->getLeft();
                    }
                }
                if (folha->isSentinel()) {
                    folha = esq;
                }

                this->raiz = folha;  // Filho mais esquerdo do filho direito Vira Raiz.

                //folha = dir;  // Re-seta folha
                if (folha == folha->getPai()->getLeft()) {  // tira ele como filho
                    folha->getPai()->setLeft(folha->getLeft());
                }
                else {
                    folha->getPai()->setRight(folha->getLeft());
                }

                this->raiz->setPai(NULL);// seta ele sem pai

                if (folha != esq) {
                    folha->setLeft(esq);//seta toda parte esquerda como filha parte 1/2
                    esq->setPai(folha);//seta toda parte esquerda como filha parte 2/2
                }

                while (!folha->getRight()->isSentinel()) {
                    folha = folha->getRight();
                }
                if (folha->getIdade() < dir->getIdade()) { //Tem que setar
                    folha->setRight(dir);
                }
            }

        }
        this->qtd_Nos--;

    }
    delete rem;
    delete sentinel;
}

void Arvore::clear() {
    while (!this->raiz->isSentinel()) {
        cout << this->raiz->getIdade() << " " << endl;
        Pop(this->raiz->getIdade());
    }
}

