#include "pilha.h"

#include <iostream>

Pilha::Pilha(){
    this->Header = new Nol();
    this->Trailer = new Nol();

    Header->Back = NULL;
    Trailer->Back = Header;
    Trailer->Next = NULL;
    Header->Next = Trailer;
}

Pilha::~Pilha(){
    clear();
    delete getTrailer();
    delete getHeader();
}

void Pilha::insert_before(Nol * noh, int idade, string & texto)
{
    if (noh == getHeader()) {
        cout << "\nNão se pode adicionar antes do Sentinela Header.";
    } else {
        Nol * n = new Nol();
        n->Idade = idade;
        n->setTexto(texto);

        n->Next = noh;
        n->Back = noh->Back;
        noh->Back->Next = n;
        noh->Back = n;
    }
}

void Pilha::remove(Nol * noh)
{
    if (noh == getHeader()  || noh == getTrailer()) {
        cout << "\nNão se pode Remover Sentinelas.";
    } else {
        noh->Back->Next = noh->Next;
        noh->Next->Back = noh->Back;

        delete noh;
    }
}

Nol * Pilha::getHeader()
{
    return this->Header;
}

Nol * Pilha::getTrailer()
{
    return this->Trailer;
}

bool Pilha::empty(){
    return (this->Header->Next == this->Trailer);
}

void Pilha::push_back(int idade, string & nome)
{
    insert_before(this->getTrailer(), idade, nome);
}

void Pilha::Push_back_Org(int idade, string & nome)
{
    Nol * temp = getHeader()->Next;
    while (temp->Next != NULL  &&  temp != getTrailer()) {
        if (temp->Idade == idade) {
            temp->setTexto(nome);
            return;
        }
        temp = temp->Next;
    }
    push_back(idade, nome);
}

void Pilha::pop_back()
{
    if (empty()) {
        cout << "Nao, desimpilheirado, Estrutura vazia.";
    } else {
        remove(getTrailer()->Back);
    }
}

void Pilha::clear()
{
    while (!empty()) {
        pop_back();
    }
}

Nol *Pilha::Buscar(int idade)
{   Nol * retorna = NULL;

    Nol * trailer  = getTrailer();
    Nol * ponteiro = getHeader()->getNext();
    if(ponteiro != trailer){// Se tiver elementos

        //Percorre o caminho até achar o valor ou ate chegar ao fim
        while(ponteiro->getNext() != trailer && ponteiro->getIdade() != idade){
            ponteiro = ponteiro->getNext();
        }
        if(ponteiro->getIdade() != idade){//Se nao achou sai.
            return retorna;
        } else { // Se tiver a idade entra.
            retorna = ponteiro;
        }
    }
    return retorna;
}

string Pilha::Print()
{
    string print;

    if (empty()) {
        print = "";
    } else {
        Nol * temp = getHeader()->Next;

        print =  "(";
        while (temp != NULL  &&   temp != getTrailer())
        {
            print = print+ conv_IntToString(temp->Idade) + "[";
            if ( !(temp->nome3.empty()) ) {
                print = print+ temp->nome1 + ", " + temp->nome2 + ", " + temp->nome3 + "]";
            } else if ( !(temp->nome2.empty()) ) {
                print = print+ temp->nome1 + ", " + temp->nome2 + "]";
            } else if ( !(temp->nome1.empty()) ) {
                print = print+ temp->nome1 + "]";
            }

            if ( temp->Next != getTrailer() ) {
                print = print+ ";";
            }
            temp = temp->Next;
        }
        print = print + ")";
    }
    return print;
}

