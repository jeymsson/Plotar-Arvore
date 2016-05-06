#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsScene>

#include <QString>
#include <QMessageBox>
#include <QPainter>
#include <QDebug>

#include "meu_item.h"
#include "pilha.h"
#include "funcoes.h"
#include "manipulacoes.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_botaoOk_clicked();

    void on_botaoInserir_clicked();

    void on_botaoRemover_clicked();

    void on_botaoBuscar_clicked();

    void adicionaEm_combo(int idade);

    void on_botaoGerar_clicked();

    void on_botaoExporta_clicked();

private:
    Pilha * pilha;

    Ui::Dialog *ui;
    QGraphicsScene *Cenario;
    Meu_Item *Item;

    int ultimo_BUSCADO;
    QIntValidator * validaIdade;

};

#endif // DIALOG_H
