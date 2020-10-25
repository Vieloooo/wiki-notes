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
    // connect(this, SIGNAL(toPlainText()) ,this->parent(),SLOT(MainWindow::handlePlainText()));
    this->close();
}

void chooseModal::on_heading1_clicked()
{
    emit toHeading1();
    this->close();

}

void chooseModal::on_heading2_clicked()
{
    emit toHeading2();
    this->close();
}

void chooseModal::on_heading3_clicked()
{
    emit toHeading3();
    this->close();
}

void chooseModal::on_red_clicked()
{
    emit toRed();
    this->close();

}

void chooseModal::on_blue_clicked()
{
    emit toBlue();
    this->close();

}

void chooseModal::on_yellow_clicked()
{
    emit toYellow();
    this->close();

}

void chooseModal::on_redBackground_clicked()
{
    emit toRedBackground();
    this->close();
}

void chooseModal::on_blueBackground_clicked()
{
    emit toBlueBackground();
    this->close();
}

void chooseModal::on_yellowbackground_clicked()
{
    emit toYellowBackground();
    this->close();
}


void chooseModal::on_Para_clicked()
{
    emit toPara();
    this->close();
}

void chooseModal::on_Div_clicked()
{
    emit toDiv();
    this->close();
}

void chooseModal::on_pushButton_5_clicked()
{
    emit toBulletList();
    this->close();
}

void chooseModal::on_circleList_clicked()
{
    emit toCircleList();
    this->close();
}

void chooseModal::on_searcBut_clicked()
{
    QString searchContent = ui->lineEdit->text();

    emit pleaseSearch(searchContent);

    this->close();
}
