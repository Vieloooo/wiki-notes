#include "maininfo.h"
#include "ui_maininfo.h"

#include <QtDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainInfo::MainInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainInfo)
{
    ui->setupUi(this);
}

MainInfo::~MainInfo()
{
    delete ui;
}

void MainInfo::on_pushButton_clicked()
{
    QString Info = ui->lineEdit->text();

    this->close();
     qDebug() <<Info;

}
