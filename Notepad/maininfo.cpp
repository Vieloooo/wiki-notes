#include "maininfo.h"
#include "ui_maininfo.h"

#include <QtDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonValue>

MainInfo::MainInfo(QWidget *parent,int posi , QString jsonName) :
    QDialog(parent),
    ui(new Ui::MainInfo)
{
    ui->setupUi(this);
    jsonFile = jsonName;
    position =posi;

    QFile file(jsonName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
           QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
           return;
       }
    QTextStream in(&file);
    QString text = in.readAll();

    //qDebug()<< text;
    QJsonDocument doc1 = QJsonDocument::fromJson(text.toUtf8());

    arr = doc1.array();

     qDebug()<<"maininfo begin ";
        qDebug()<<arr;
         //qDebug()<<jsonFile;
              //qDebug()<<position;


    //qDebug()<< "this is " + ar;
    file.close();

}

MainInfo::~MainInfo()
{
    delete ui;
}

void MainInfo::on_pushButton_clicked()
{
    qDebug()<<"maininfo begin";
     Info = ui->lineEdit->text();
     qDebug()<<arr;
          qDebug()<<jsonFile;
               qDebug()<<position;




     QJsonObject Ablock;
     Ablock.insert("position",position);
     Ablock.insert("mainInfo",Info);
     arr.append(Ablock);


     qDebug() << "after";
      qDebug()<<arr;
     QJsonDocument rootDoc;
     rootDoc.setArray(arr);
     QByteArray rootStr = rootDoc.toJson(QJsonDocument::Compact);
     QString jsonString(rootStr);
     qDebug() << jsonString;


     QFile file(jsonFile);

     if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
            return;
        }
        // setWindowTitle("save"+fileName);
         QTextStream out(&file);
         out << jsonString;
         file.close();


this->close();


}
