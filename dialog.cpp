#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->pilha = new Pilha(); //Cria pilha.
    this->arvore= new Arvore();//Cria Arvore.

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

    ui->label_altura->setText(converter_Int_ToQstring(this->arvore->getAltura()));
    ui->label_qtd_nos->setText(converter_Int_ToQstring(this->arvore->getQtd_Nos()));
    ui->label_qtd_folhas->setText(converter_Int_ToQstring(this->arvore->getNum_Folhas()));

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_botaoOk_clicked()
{//Liga desliga
    this->Item->Ligado = (Item->Ligado ? false : true);

    ui->label_liga_desliga->setText((this->Item->Ligado ? "Ligado" : "Desligado") );

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
        this->arvore->Add_org(iIdade, std::string(sNome) );

            /*Arvore * arv = new Arvore();
            std::string strin = "Zen";
            arv->Add_org(10, string(strin));
            arv->Add_org(20, string(strin));
            arv->Add_org(30, string(strin));
            this->Item->setArvore(arv);*/

        this->Item->setArvore(this->arvore, QIdade);

        //Se o adicionado for o mesmo que está em cache para remoção atuaiza a lista.
        if(iIdade == this->ultimo_BUSCADO){
            adicionaEm_combo(iIdade);
        }

        //Atualiza a altura e a qtd de nos.
        ui->label_altura->setText(converter_Int_ToQstring(this->arvore->getAltura()));
        ui->label_qtd_nos->setText(converter_Int_ToQstring(this->arvore->getQtd_Nos()));
        ui->label_qtd_folhas->setText(converter_Int_ToQstring(this->arvore->getNum_Folhas()));

    }
    this->arvore->VLR();
    qDebug() << converter_StringToQstring(this->arvore->getVarredura()->Print());
}

void Dialog::on_botaoRemover_clicked(){

    if(ui->comboRemocao->count()  == 0){ //Se a quantidade de elementos da lista =0
        QMessageBox::information(this, tr("Botao Remover."), tr("Não existe elementos a serem removidos."));
    } else if(ui->comboRemocao->count()  == 1){ //Se Tiver somente um nome

        QMessageBox::StandardButton resposta;
        resposta = QMessageBox::question(this, tr("Botao Remover.")
                                         , tr("Deseja mesmo excluir este No da ULTIMA BUSCA? "));
        if(resposta == QMessageBox::No){
            QMessageBox::information(this, tr("Botao Remover."), tr("No nao removido."));
        } else if(resposta == QMessageBox::Yes){

            //Removendo do ultimo elemento BUSCADO
            Nol * remover = this->arvore->Busca_no(this->ultimo_BUSCADO);

            if(remover == NULL){
                QMessageBox::information(this, tr("Botao Remover."), tr("..NÃO REMOVIDO."));
            } else {
                this->arvore->Pop(remover->getIdade());
                this->Item->setArvore(this->arvore);
                ui->abas_Tab_Widget->setTabEnabled(1, false);
            }
        }
    } else {
        //  Posicao do item selecionado (indice +1).
        int posicao = (ui->comboRemocao->currentIndex() +1);

        //Removendo texto do ultimo elemento BUSCADO
        Nol * remover = this->arvore->Busca_no(this->ultimo_BUSCADO);

        if(remover == NULL){
            QMessageBox::information(this, tr("Botao Remover."), tr("..NÃO REMOVIDO."));
        } else {
            remover->setNome(posicao, "");
            remover->ordena();
            this->Item->setArvore(this->arvore);
        }
    }

adicionaEm_combo(this->ultimo_BUSCADO);
}


void Dialog::on_botaoBuscar_clicked()
{
    QString QBusca = ui->editaIdade->text();
    int     iBusca = converter_QstringToInt(QBusca);

    if(QBusca.isEmpty() ||  this->arvore->Busca_no(iBusca)->isSentinel()){
        qDebug() << "O valor buscado eh: NULO";
        QMessageBox::information(this, tr("Botao Buscar."), tr("Idade nao achada."));
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
        if(!this->arvore->Busca_no(iBusca)->isSentinel()){
            ui->abas_Tab_Widget->setTabEnabled(1, true);
            adicionaEm_combo(iBusca);
        } else {
            ui->abas_Tab_Widget->setTabEnabled(1, false);
        }
    }
}

//Adiciona os nomes da busca na tabela de remocao
void Dialog::adicionaEm_combo(int idade)
{
    ui->comboRemocao->clear();

    Nol * ponteiro = this->arvore->Busca_no(idade);
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

            this->arvore->clear();

            Arvore * arv = Gerar_Arvore(manipulacoes);
            if(arv->getRaiz()->isSentinel()){
                QMessageBox::information(this, tr("Importa."), tr("Texto da Arvore fora dos padrões."));
            } else {
                Arvore * temp = this->arvore;
                //this->arvore->clean
                this->arvore = arv;
                this->Item->setArvore(this->arvore);
                delete temp;

                if(!this->arvore->getRaiz()->isSentinel()){
                    this->arvore->VLR();
                    qDebug () << converter_StringToQstring(arv->getVarredura()->Print());
                }
                ui->label_altura->setText(converter_Int_ToQstring(this->arvore->getAltura()));
                ui->label_qtd_nos->setText(converter_Int_ToQstring(this->arvore->getQtd_Nos()));
                ui->label_qtd_folhas->setText(converter_Int_ToQstring(this->arvore->getNum_Folhas()));
            }
        }
    } else if(ui->comboImporta->currentIndex() == 1){ //Se for a partir de arquivo texto

        string manipulacoes = (importar_by_Text());

        Pilha * p = importar_pilha(manipulacoes);
        if(p == NULL){
            QMessageBox::information(this, tr("Importa."), tr("Texto da pilha no arquivo texto fora dos padrões."));
        } else {
            string manipulacoes = importar_by_Text();

            Arvore * arv;

            qDebug()<< "Arquivo: "<< converter_StringToQstring(manipulacoes);
            qDebug()<< "botaoGerar - 1";
            arv = Gerar_Arvore(manipulacoes);
            qDebug()<< "botaoGerar - 2";
            arv->VLR();
            //qDebug()<< converter_StringToQstring(arv->getVarredura()->Print());
            if(arv->getRaiz()->isSentinel()){
                QMessageBox::information(this, tr("Importa."), tr("Texto da Arvore fora dos padrões."));
            } else {
                Arvore * temp = this->arvore;

                this->arvore->clear();

                this->arvore = arv;
                this->Item->setArvore(this->arvore);
                delete temp;

                if(!this->arvore->getRaiz()->isSentinel()){
                    this->arvore->VLR();
                    qDebug () << converter_StringToQstring(arv->getVarredura()->Print());
                }
            }
        }
        ui->label_altura->setText(converter_Int_ToQstring(this->arvore->getAltura()));
        ui->label_qtd_nos->setText(converter_Int_ToQstring(this->arvore->getQtd_Nos()));
        ui->label_qtd_folhas->setText(converter_Int_ToQstring(this->arvore->getNum_Folhas()));
    }

}

void Dialog::on_botaoExporta_clicked()
{
    string varredura;
    if(ui->comboExportar->currentIndex() == 0){ //Se for a Pre
        this->arvore->VLR();
        varredura = this->arvore->getVarredura()->Print();

    } else if(ui->comboExportar->currentIndex() == 1){ //Se for a In
        this->arvore->LVR();
        varredura = this->arvore->getVarredura()->Print();

    } else if(ui->comboExportar->currentIndex() == 2){ //Se for a pos
        this->arvore->LRV();
        varredura = this->arvore->getVarredura()->Print();

    }


    if(this->arvore->getRaiz()->isSentinel()){
        varredura = "vazio.";
    }

    string s = varredura;
    ui->editaManipulacoes->setText(converter_StringToQstring(varredura));
    Exportar_Novo(s);

}


//Apagar Arvore
void Dialog::on_botaoApagarArvore_clicked()
{
    if(1==1){

        this->arvore->clear();
        this->Item->setArvore(this->arvore);

        ui->label_altura->setText(converter_Int_ToQstring(this->arvore->getAltura()));
        ui->label_qtd_nos->setText(converter_Int_ToQstring(this->arvore->getQtd_Nos()));
        ui->label_qtd_folhas->setText(converter_Int_ToQstring(this->arvore->getNum_Folhas()));
    }
}

void Dialog::on_botaoMostrarTrav_clicked()
{
    if(!this->arvore->getRaiz()->isSentinel()){
        string varredura;
        if(ui->comboTrav->currentIndex() == 0){ //Se for a Pre
            this->arvore->VLR();
            varredura = this->arvore->getVarredura()->Print();

        } else if(ui->comboTrav->currentIndex() == 1){ //Se for a In
            this->arvore->LVR();
            varredura = this->arvore->getVarredura()->Print();

        } else if(ui->comboTrav->currentIndex() == 2){ //Se for a pos
            this->arvore->LRV();
            varredura = this->arvore->getVarredura()->Print();

        }

        if(ui->comboTrav->currentIndex() == 3   ){ //Se for a original
            this->Item->setArvore(this->arvore);
            ui->label_altura->setText(converter_Int_ToQstring(this->arvore->getAltura()));
            ui->label_qtd_nos->setText(converter_Int_ToQstring(this->arvore->getQtd_Nos()));
            ui->label_qtd_folhas->setText(converter_Int_ToQstring(this->arvore->getNum_Folhas()));

            this->arvore->VLR();
            varredura = this->arvore->getVarredura()->Print();

        } else {
            if(this->arvore->getRaiz()->isSentinel()){
                varredura = "vazio.";
            }
            Arvore* Arv = Gerar_Arvore(varredura);
            this->Item->setArvore(Arv);

            ui->label_altura->setText(converter_Int_ToQstring(Arv->getAltura()));
            ui->label_qtd_nos->setText(converter_Int_ToQstring(Arv->getQtd_Nos()));
            ui->label_qtd_folhas->setText(converter_Int_ToQstring(Arv->getNum_Folhas()));
        }
        ui->editaTrav->setText(converter_StringToQstring(varredura));
    }

}
