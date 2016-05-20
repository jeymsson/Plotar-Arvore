#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->pilha = new Pilha(); //Cria pilha.

    //Desativa tab de remocao
    ui->abas_Tab_Widget->setTabEnabled(1, false);;

        //Cria cenario e adiciona ao "grafico".
        Cenario = new QGraphicsScene(this);
        ui->graphicsView->setScene(Cenario);
    //Adiciona a figura "Item" ao cenário.
    Item = new Meu_Item();
    Cenario->addItem(Item);

    //Inicializa o ultimo numero buscado.
    this->ultimo_BUSCADO = NULL;

    //Validador do campo idade.
    this->validaIdade =  new QIntValidator(0, 999, this);
    ui->editaIdade->setValidator(this->validaIdade);

        //Teste adicionando
    //this->pilha->Push_back_Org(10, std::string("Tex") );
    //this->Item->setPilha(this->pilha, converter_Int_ToQstring(10));

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_botaoOk_clicked()
{//Liga desliga
    this->Item->Ligado = (Item->Ligado ? false : true);

    ui->label->setText((this->Item->Ligado ? "Ligado" : "Desligado") );

    int i;
    QString s = ui->editaIdade->text();
    i = s.toInt();

    //ui->label->setText(s);
}

void Dialog::on_botaoInserir_clicked()
{
    QString QIdade = ui->editaIdade->text();
    QString QNome = ui->editaNome->text();
    int        iIdade = converter_QstringToInt(QIdade);
    std::string sNome = converter_QstringToString(QNome);

    if(QIdade.isEmpty()){
        QMessageBox::information(this, tr("Atenção."), tr("Nao tem idade digitada."));
    } else if(QNome.isEmpty()){
        QMessageBox::information(this, tr("Atenção."), tr("Nao tem nome digitado."));
    } else {
        this->pilha->Push_back_Org(iIdade, std::string(sNome) );

        //    Pilha * p = new Pilha();
        //    p->Push_back_Org(10, string("Zen"));
        //    p->Push_back_Org(20, string("Zen"));
        //    p->Push_back_Org(30, string("Zen"));
        //    this->Item->setPilha(p);

        this->Item->setPilha(this->pilha, QIdade);

        //Se o adicionado for o mesmo que está em cache para remoção atuaiza a lista.
        if(iIdade == this->ultimo_BUSCADO){
            adicionaEm_combo(iIdade);
        }
    }qDebug() << converter_StringToQstring(this->pilha->Print());
}

void Dialog::on_botaoRemover_clicked(){

    if(ui->comboRemocao->count()  == 0){ //Se a quantidade de elementos da lista =0
        QMessageBox::information(this, tr("Botao Remover."), tr("Não existe elementos a serem removidos."));
    } else if(ui->comboRemocao->count()  == 1){ //Se a quantidade de elementos da lista =0

        QMessageBox::StandardButton resposta;
        resposta = QMessageBox::question(this, tr("Botao Remover.")
                                         , tr("Deseja mesmo excluir este Nó da ULTIMA BUSCA? "));
        if(resposta == QMessageBox::No){
            QMessageBox::information(this, tr("Botao Remover."), tr("Nó não removido."));
        } else if(resposta == QMessageBox::Yes){

            //Removendo do ultimo elemento BUSCADO
            Nol * remover = this->pilha->Buscar(this->ultimo_BUSCADO);

            if(remover == NULL){
                QMessageBox::information(this, tr("Botao Remover."), tr("..NÃO REMOVIDO."));
            } else {
                this->pilha->remove(remover);
                this->Item->setPilha(this->pilha);
                ui->abas_Tab_Widget->setTabEnabled(1, false);
            }
        }
    } else {
        //  Posicao do item selecionado (indice +1).
        int posicao = (ui->comboRemocao->currentIndex() +1);

        //Removendo texto do ultimo elemento BUSCADO
        Nol * remover = this->pilha->Buscar(this->ultimo_BUSCADO);

        if(remover == NULL){
            QMessageBox::information(this, tr("Botao Remover."), tr("..NÃO REMOVIDO."));
        } else {
            remover->setNome(posicao, "");
            remover->ordena();
            this->Item->setPilha(this->pilha);
        }
    }

adicionaEm_combo(this->ultimo_BUSCADO);
}

void Dialog::on_botaoBuscar_clicked()
{
    QString QBusca = ui->editaIdade->text();
    int     iBusca = converter_QstringToInt(QBusca);

    if(QBusca.isEmpty()){
        qDebug() << "O valor buscado eh: NULO";
    } else {
        qDebug() << "O valor buscado eh: " << converter_Int_ToQstring(iBusca);
    }

    if(QBusca.isEmpty()){
        this->ultimo_BUSCADO = NULL;
        this->Item->busca = NULL;
        ui->abas_Tab_Widget->setTabEnabled(1, false);
    } else {
        //Seta o ultimo valor buscado no principal e no item
        this->ultimo_BUSCADO = iBusca;
        this->Item->busca = iBusca;
        //se retornou algo válido
        if(this->pilha->Buscar(iBusca) != NULL){
            ui->abas_Tab_Widget->setTabEnabled(1, true);
            adicionaEm_combo(iBusca);
        } else {
            ui->abas_Tab_Widget->setTabEnabled(1, false);
        }
    }
}

void Dialog::adicionaEm_combo(int idade)
{
    ui->comboRemocao->clear();

    Nol * ponteiro = this->pilha->Buscar(idade);
    if(ponteiro != NULL){
        if(ponteiro->getNome(1).empty()){
            return;
        } else {  //Se tiver nome.
            if(!(ponteiro->getNome(3).empty()) ){
                ui->comboRemocao->addItem(converter_StringToQstring(ponteiro->getNome(1)));
                ui->comboRemocao->addItem(converter_StringToQstring(ponteiro->getNome(2)));
                ui->comboRemocao->addItem(converter_StringToQstring(ponteiro->getNome(3)));

            } else if(!(ponteiro->getNome(2).empty()) ){
                ui->comboRemocao->addItem(converter_StringToQstring(ponteiro->getNome(1)));
                ui->comboRemocao->addItem(converter_StringToQstring(ponteiro->getNome(2)));

            } else if(!(ponteiro->getNome(1).empty()) ){
                ui->comboRemocao->addItem(converter_StringToQstring(ponteiro->getNome(1)));

            }

        }

    }

}

void Dialog::on_botaoGerar_clicked()
{
    QString manip = ui->editaManipulacoes->text();;


    if(ui->comboImporta->currentIndex() == 0){ //Se for a partir de texto
        if(manip.isEmpty()){
            QMessageBox::information(this, tr("Importa."), tr("Nao tem Pilha digitada."));;
        } else {
            string manipulacoes = converter_QstringToString(manip);

            Pilha * p = importar_pilha(manipulacoes);
            if(p == NULL){
                QMessageBox::information(this, tr("Importa."), tr("Texto da pilha fora dos padrões."));
            } else {
                Pilha * temp = this->pilha;
                this->pilha = p;
                this->Item->setPilha(this->pilha);
                this->Item->busca = this->pilha->getTrailer()->getIdade();
                delete temp;

                if(!this->pilha->empty()){
                    qDebug () << converter_StringToQstring(p->Print());
                }
            }
        }
    } else if(ui->comboImporta->currentIndex() == 1){ //Se for a partir de arquivo texto

        string manipulacoes = (importar_by_Text());

        Pilha * p = importar_pilha(manipulacoes);
        if(p == NULL){
            QMessageBox::information(this, tr("Importa."), tr("Texto da pilha no arquivo texto fora dos padrões."));
        } else {
            Pilha * temp = this->pilha;
            this->pilha = p;
            this->Item->setPilha(this->pilha);
            this->Item->busca = this->pilha->getTrailer()->getIdade();
            delete temp;

            if(!this->pilha->empty()){
                qDebug () << converter_StringToQstring(p->Print());
            }
            this->ui->editaManipulacoes->setText(converter_StringToQstring(p->Print()));
        }
    }

}

void Dialog::on_botaoExporta_clicked()
{
    if(ui->comboExportar->currentIndex() == 0){ //Se for a partir de texto
        string pilha = this->pilha->Print();
        if(this->pilha->empty()){
            pilha = "vazio.";
        }

        string s = pilha;
        Exportar_Novo(s);
    }
}

