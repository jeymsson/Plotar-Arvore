#include "meu_item.h"


Meu_Item::Meu_Item()
{
    this->busca = NULL;
    this->pilha = new Pilha();
    this->arvore = new Arvore();

    this->Pressionado = false;
    this->Ligado = true;
    setFlag(ItemIsMovable);

    this->X_Final = this->x2 ;

    /*std::string string = "Tex";
    getArvore()->Add_org(8, string);
    getArvore()->Add_org(4, string);
    getArvore()->Add_org(12, string);
    getArvore()->Add_org(2, string);
    getArvore()->Add_org(1, string);
    getArvore()->Add_org(3, string);
    getArvore()->Add_org(6, string);
    getArvore()->Add_org(5, string);
    getArvore()->Add_org(7, string);
    getArvore()->Add_org(10, string);
    getArvore()->Add_org(14, string);
    getArvore()->Add_org(9, string);
    getArvore()->Add_org(11, string);
    getArvore()->Add_org(13, string);
    getArvore()->Add_org(15, string);*/


}

Meu_Item::~Meu_Item()
{
    this->pilha->~Pilha();
}

QRectF Meu_Item::limitadorPagina() const
{
    // outer most edges
    return QRectF(this->x1, this->y1, this->X_Final, this->y2);
}

void Meu_Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressionado =true;
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Meu_Item::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressionado =false;
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

void Meu_Item::paint(QPainter *Desenho
                     , const QStyleOptionGraphicsItem *Opcao
                     , QWidget *widget)
{
    //No_Pilha_Print(Desenho, this->pilha);
    //Desenha_No(Desenho, getPilha()->getHeader()->getNext(), this->x1, this->x2, 0, 60);
    No_Arv_Print(Desenho, this->arvore);
    update();
}

void Meu_Item::desenha_flecha_Esq(QPainter *Desenho, const int coord_X, const int coord_Y, int pont, int cabo)
{
    int altura_level = 50;

    int tam = pont;
    //Organiza poligono
    QPolygon seta;
    seta << QPoint(coord_X -tam, coord_Y);
    seta << QPoint(coord_X -tam, coord_Y + tam);
    seta << QPoint(coord_X, coord_Y + tam/2);
    //Caneta
    Desenho->setPen(QPen(Qt::black, 4));
    //estampas
    QBrush esta(Qt::red, Qt::SolidPattern);
    //agulha..
    QPainterPath agulha;
    agulha.addPolygon(seta);
    //Cabo da flecha //(largura, altura_esq,  , altura_dir)
    Desenho->drawLine( cabo, (coord_Y + tam/2), (coord_X - tam), (coord_Y + tam/2) );
    //Desenha e costuro estampa..
    Desenho->drawPolygon(seta);
    Desenho->fillPath(agulha, esta);
}

void Meu_Item::setPilha(Pilha *pilha, QString QIdadeBusca)
{
    //Seta a Pilha.
    this->pilha = pilha;

    //Seta o valor de busca para tornar o noh com cor diferente
    if(QIdadeBusca.isEmpty()){
        this->busca = NULL;
    } else {
        this->busca = converter_QstringToInt(QIdadeBusca);
    }
}

void Meu_Item::setArvore(Arvore *arvore, QString QIdadeBusca)
{
    //Seta a Arvore.
    this->arvore = arvore;

    //Seta o valor de busca para tornar o noh com cor diferente
    if(QIdadeBusca.isEmpty()){
        this->busca = NULL;
    } else {
        this->busca = converter_QstringToInt(QIdadeBusca);
    }
}

void Meu_Item::setPilha(Pilha *pilha)
{
    //Seta a Pilha.
    this->pilha = pilha;
}

void Meu_Item::setArvore(Arvore *arvore)
{
    //Seta a Arvore.
    this->arvore = arvore;
}

Pilha *Meu_Item::getPilha()
{
    return this->pilha;
}

Arvore *Meu_Item::getArvore()
{
    return this->arvore;
}

void Meu_Item::Desenha_No(QPainter *Desenho, Nol *noh, int X1, int X2, int Y1, int Y2)
{
    int Novo_x1 = X1;
    int X_Final2 = X2;
    QString Idade;
    QString Nomes;

    Idade = converter_Int_ToQstring(noh->getIdade());
    Nomes = converter_StringToQstring(noh->getNomes());
    //Estilo caneta
    if(noh->getIdade() == this->busca){
        QPen pen(Qt::red, 5);
        Desenho->setPen(pen);
    } else{
        QPen pen(Qt::black, 3);
        Desenho->setPen(pen);
    }
    //Desenha quadrado
    Desenho->drawRect(Novo_x1,Y1,X_Final2,Y2);
    //Escreve
    Desenho->setFont(QFont("Arial", 18));
    Desenho->drawText(Novo_x1,Y1,X_Final2,Y2, Qt::AlignHCenter, Idade);
    Desenho->setFont(QFont("Arial", 13));
    Desenho->drawText(Novo_x1,Y1,X_Final2,Y2, Qt::AlignCenter, "\n" + Nomes);

}

void Meu_Item::No_Pilha_Print(QPainter *Desenho, Pilha *pilha)
{
    QRectF rect = limitadorPagina();
    int X_Final2 = this->x2 ;
    int Novo_x1 = this->x1;
    int     largura_no = (this->x2 - this->x1);
    int distancia = 40;

    Desenho-> eraseRect(rect); //aqui só apaga nessas margens..
    if(Ligado)
    {   Nol * trailer = pilha->getTrailer();
        if(pilha->getHeader()->getNext() != trailer ){

            Nol * ponteiro = pilha->getHeader()->getNext();
            int temp_x;
            int ajuste_flecha = 2;

            while(ponteiro != trailer ){

                Desenha_No(Desenho, ponteiro, Novo_x1, X_Final2, 0, 60 );

                //Define as cordenadas do proximo no e da Seta.
                ponteiro = ponteiro->getNext();
                Novo_x1 = Novo_x1 + largura_no + distancia;
                temp_x = Novo_x1 - distancia;

                if(ponteiro != trailer) {
                    //Ajuste é para a seta não invadir uma caixa
                    desenha_flecha_Esq(Desenho, Novo_x1, (this->y2)/2, 8, Novo_x1 - distancia /*+ajuste_flecha*/);
                }
            }
            update();
            X_Final2 = ( Novo_x1 - distancia ) ;
            this->X_Final = X_Final2;
//            qDebug() << this->X_Final;

        }//Fim verificação se está vazio
    }//Fim do if(Ligado);
}

void Meu_Item::No_Arv_Print(QPainter *Desenho, Arvore* arvore)
{
    if(!getArvore()->getRaiz()->isSentinel()){
        if (!this->Ligado) {
        }
        else {
            VLR(arvore->getRaiz(), Desenho, this->x1, this->x2, 0, SomaDistancias());
        }
    }
}

void Meu_Item::VLR(Nol * No, QPainter *Desenho, int X1, int X2, int Y1, int largura)
{
    //p->Push_back_No(No);
    ////Declarando variaveis.
    int Novo_x1 = X1;
    int X_Final2 = X2;
    int     largura_no = (this->x2 - this->x1);

    ////Distancia de altura
    int distancia_X = 40;
    int distancia_Y = 60;

    ////Setando dentro do no.
    No->setCoord_x(X1);
    No->setCoord_y(Y1);

    ////Desenhando
    Desenha_No(Desenho, No, Novo_x1, X_Final2, Y1, 60 );

    //Larg_Filhos = Larg_Filhos;


    Y1 += distancia_Y;

    int X_old = Novo_x1;
    if (!No->getLeft()->isSentinel()) {
        //Novo_x1 = Novo_x1 - largura_no - distancia_X - distancia_X/2;
        Novo_x1 = Novo_x1 - (largura_no/2 + distancia_X/2) ;
        Novo_x1 = Novo_x1 - (largura_no/2 + distancia_X/2)  - distancia_X*(this->arvore->getMaxLargura(No));

        X_Final2 = X_Final2 ;

        VLR(No->getLeft(), Desenho, Novo_x1, X_Final2, Y1, largura/2);

        Desenho->drawLine(X1, Y1, Novo_x1 + X_Final2, Y1 + distancia_Y/2);

        //Organiza poligono
        int tam = 8;
        QPolygon seta;
        seta << QPoint(Novo_x1 + X_Final2 +tam, Y1 + distancia_Y/2 - tam);
        seta << QPoint(Novo_x1 + X_Final2 +tam, Y1 + distancia_Y/2 + tam/2);
        seta << QPoint(Novo_x1 + X_Final2     , Y1 + distancia_Y/2        );
        Desenho->drawPolygon(seta);


        update();
    }
    if (!No->getRight()->isSentinel()) {
        Novo_x1 = Novo_x1 + (largura_no/2 + distancia_X/2) ;
        Novo_x1 = Novo_x1 + (largura_no/2 + distancia_X/2) + distancia_X*(this->arvore->getMaxLargura(No));
        X_Final2 = X_Final2 ;

        if(Novo_x1 == X_old){
            Novo_x1 = Novo_x1 + (largura_no/2 + distancia_X/2) ;
            Novo_x1 = Novo_x1 + (largura_no/2 + distancia_X/2) + distancia_X*(this->arvore->getMaxLargura(No));
            X_Final2 = X_Final2 ;
        }
        VLR(No->getRight(), Desenho, Novo_x1, X_Final2, Y1, No->getCoord_x());
        Desenho->drawLine(X1 + X_Final2, Y1, Novo_x1, Y1 + distancia_Y/2);

        //Organiza poligono
        int tam = 8;
        QPolygon seta;
        seta << QPoint(Novo_x1 -tam, Y1 + distancia_Y/2 - tam  );
        seta << QPoint(Novo_x1 -tam, Y1 + distancia_Y/2 + tam/2);
        seta << QPoint(Novo_x1     , Y1 + distancia_Y/2        );
        Desenho->drawPolygon(seta);

        update();
    }
    update();
}


int Meu_Item::SomaDistancias()
{
    int larg = getArvore()->getMaxLargura(getArvore()->getRaiz());
    int distancia_X = 40;
    return (larg - 1) * distancia_X;
}

