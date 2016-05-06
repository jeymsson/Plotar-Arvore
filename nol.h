#ifndef NOL_H
#define NOL_H

#include <iostream>
#include <string>

using namespace std;

class Nol{

protected: //Coordenadas de cada no
    int coord_x;
    int coord_y;
private:
    Nol * Next;
    Nol * Back;
    int Idade;
    string nome1;
    string nome2;
    string nome3;

public:
    Nol();
    ~Nol();
    void ordena();
    void setTexto(string & texto);

    void setCoord_x(int x);
    int getCoord_x();
    void setCoord_y(int y);
    int getCoord_y();

    Nol * getNext();
    Nol * getBack();

    int getIdade();
    string getNomes();
    string getNome(int NumeroNome);
    void   setNome(int NumeroNome, string texto);

    friend class Pilha;
};

#endif // NOL_H
