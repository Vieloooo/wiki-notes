#include "choosemodal.h"
#include "ui_choosemodal.h"

chooseModal::chooseModal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooseModal)
{
    ui->setupUi(this);
}

chooseModal::~chooseModal()
{
    delete ui;
}

void chooseModal::on_toPlain_clicked()
{
    emit toPlainText();
     connect(this, SIGNAL(toPlainText()) ,this->parent(),SLOT(MainWindow::handlePlainText()));
    this->close();
}
