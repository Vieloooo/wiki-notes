#include "uabiruana.h"
#include "ui_uabiruana.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QColorDialog>
#include <QComboBox>
#include <QFontComboBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QTextCodec>
#include <QTextEdit>
#include <QStatusBar>
#include <QToolBar>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QTextList>
#include <QtDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QMimeData>
#include <QMimeDatabase>
#include <QBrush>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <widget.h>
#include <mindmapdialog.h>
#include "widget.h"


UabiruanA::UabiruanA(QWidget *parent,QString jsonPath) :
    QWidget(parent),
    ui(new Ui::UabiruanA)
{
    ui->setupUi(this);
    path = jsonPath;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
           QMessageBox::warning(this, "Warning", "Cannot open file: ") ;
           return;
       }
    QTextStream in(&file);
    QString text = in.readAll();

    //qDebug()<< text;
    QJsonDocument doc1 = QJsonDocument::fromJson(text.toUtf8());

    array = doc1.array();


     qDebug()<<"json begin ";
        qDebug()<<array;
         //qDebug()<<jsonFile;
              //qDebug()<<position;
    ui->listWidget->clear();
    for(QJsonArray::iterator it = array.begin() ; it != array.end() ; it++){
        QString ss = (*(*it).toObject().constFind("mainInfo")).toString();
        int num = (*(*it).toObject().constFind("position")).toInt();
       qDebug()<<num<<"\n";
        QListWidgetItem *item = new QListWidgetItem;
        item ->setText(ss);
        item ->setTextAlignment(Qt::AlignLeft);
        item ->setToolTip(QString::number(num,10));
        ui->listWidget->addItem(item);
    }

    //qDebug()<< "this is ahhhhhhh";
    file.close();
}

UabiruanA::~UabiruanA()
{
    delete ui;
}

void UabiruanA::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int position = item -> toolTip().toInt();
    emit writePosi(position);
    this->close();

}
