#ifndef MEU_ITEM_H
#define MEU_ITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QString>
#include <QDebug>

#include "pilha.h"
#include "funcoes.h" //Para exibir os dados do no nas figuras
#include "arvore.h"

class Meu_Item :public QGraphicsItem  // class for customization
{
public:
    Meu_Item();
    ~Meu_Item();

    QRectF limitadorPagina() const;

    // overriding paint()
    void paint(QPainter * Desenho
               , const QStyleOptionGraphicsItem * Opcao
               , QWidget * widget);

    // item state
    int busca;
    bool Ligado;
    bool Pressionado;
    void setPilha(Pilha * pilha, QString QIdadeBusca);
    void setPilha(Pilha * pilha);
    Pilha * getPilha();
        Arvore * getArvore();
        void setArvore(Arvore * arvore);
        void setArvore(Arvore * arvore, QString QIdadeBusca);

private:
    Pilha * pilha;
        Arvore* arvore;

    int x1 = 0;
    int y1 = 0;
    int x2 = 100;
    int y2 = 60;
    int X_Final;


    void atualizaTudo();

protected:
    // overriding mouse events
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
void Desenha_No(QPainter *Desenho, Nol* noh, int X1, int X2, int Y1, int Y2);
void No_Pilha_Print(QPainter *Desenho, Pilha *pilha);
void No_Arv_Print(QPainter *Desenho, Arvore* arvore);
void desenha_flecha_Esq(QPainter *Desenho, const int coord_X, const int coord_Y, int seta, int cabo);

void VLR(Nol * No, QPainter *Desenho, int X1, int X2, int Y1, int X_pai);

int SomaDistancias();

};

#endif // MEU_ITEM_H

