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
    No_Pilha_Print(Desenho, this->pilha);
    //Desenha_No(Desenho, getPilha()->getHeader()->getNext(), this->x1, this->x2, 0, 60);
    //No_Arv_Print(Desenho, this->arvore);
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
        QPen pen(Qt::red, 3);
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

