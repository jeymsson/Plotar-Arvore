#ifndef MANIPULACOES_H
#define MANIPULACOES_H

#include "pilha.h"
#include "funcoes.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "arvore.h"

using namespace std ; //(12[JBV,IOF];13[UI,AE, IH];5[HJK])

Pilha * importar_pilha(string & texto);
vector<string> split(string str, char delimiter);
string importar_by_Text();
void Exportar_Novo(string & s);
Arvore* Gerar_Arvore(string & texto_arvo);

#endif // MANIPULACOES_H


