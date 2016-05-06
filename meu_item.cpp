#include "meu_item.h"


Meu_Item::Meu_Item()
{
    this->busca = NULL;
    this->pilha = new Pilha();

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
    No_Print(Desenho, this->pilha);
    update();
}

void Meu_Item::desenha_flecha_Esq(QPainter *Desenho, const int coord_X, const int coord_Y, int pont, int cabo)
{
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
    //Cabo da flecha
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

void Meu_Item::setPilha(Pilha *pilha)
{
    //Seta a Pilha.
    this->pilha = pilha;
}

Pilha *Meu_Item::getPilha()
{
    return this->pilha;
}

void Meu_Item::No_Print(QPainter *Desenho, Pilha *pilha)
{
    QRectF rect = limitadorPagina();
    int X_Final2 = this->x2 ;
    int Novo_x1 = this->x1;
    int     largura_no = (this->x2 - this->x1);
    int distancia = 30;
    int quantidade_Nos;

    Desenho-> eraseRect(rect); //aqui só apaga nessas margens..
    if(Ligado)
    {   Nol * trailer = pilha->getTrailer();
        if(pilha->getHeader()->getNext() != trailer ){

            Nol * ponteiro = pilha->getHeader()->getNext();
            int temp_x;
            QString Idade;
            QString Nomes;
            int ajuste_flecha = 2;

            while(ponteiro != trailer ){
                Idade = converter_Int_ToQstring(ponteiro->getIdade());
                Nomes = converter_StringToQstring(ponteiro->getNomes());

                //Estilo caneta
                if(ponteiro->getIdade() == this->busca){
                    QPen pen(Qt::red, 3);
                    Desenho->setPen(pen);
                } else{
                    QPen pen(Qt::black, 3);
                    Desenho->setPen(pen);
                }
                //Desenha quadrado
                Desenho->drawRect(Novo_x1,0,X_Final2,60);

                //Escreve
                Desenho->setFont(QFont("Arial", 18));
                Desenho->drawText(Novo_x1,0,X_Final2,60, Qt::AlignHCenter, Idade);
                Desenho->setFont(QFont("Arial", 13));
                Desenho->drawText(Novo_x1,0,X_Final2,60, Qt::AlignCenter, "\n" + Nomes);

                //Define as cordenadas do proximo no e da Seta.
                ponteiro = ponteiro->getNext();
                Novo_x1 = Novo_x1 + largura_no + distancia;
                quantidade_Nos++;
                temp_x = Novo_x1 - distancia;

                if(ponteiro != trailer) {
                    //Ajuste é para a seta não invadir uma caixa
                    desenha_flecha_Esq(Desenho, Novo_x1, (this->y2)/2, 8, Novo_x1 - distancia +ajuste_flecha);
                }
            }
            update();
            X_Final2 = ( Novo_x1 - distancia ) ;
            this->X_Final = X_Final2;
//            qDebug() << this->X_Final;

        }//Fim verificação se está vazio
    }//Fim do if(Ligado);
}

