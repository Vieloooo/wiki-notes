#include "widgetbuildfile.h"
#include"ui_widgetbuildfile.h"
#include "mainwindow.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

WidgetBuildFile::WidgetBuildFile(QWidget *parent,QString SecondPath,QString FirstPath) //FirstPath是整个程序的存储路径，SecondPath是用户选中的存储路径
    : QWidget(parent)
    , ui(new Ui::WidgetBuildFile)
{
    ui->setupUi(this);
    setWindowTitle("Creating New File");
    ui->lineEdit_2->setText(FirstPath);
    ui->lineEdit_5->setText(SecondPath);
    FP=FirstPath;
    SP=SecondPath;

    ui->lineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit->setReadOnly(true);

    ui->lineEdit_2->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit_2->setReadOnly(true);

    ui->lineEdit_3->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit_3->setReadOnly(true);

    ui->lineEdit_4->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit_4->setReadOnly(true);
    if(SecondPath.isEmpty()){
        ui->listWidget_2->setEnabled(false);
        ui->lineEdit_5->setText("No path selected");
    }
    ui->lineEdit_5->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit_5->setReadOnly(true);

    ui->lineEdit_6->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit_6->setReadOnly(true);

    ui->lineEdit_7->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit_7->setReadOnly(true);

    ui->lineEdit_8->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit_8->setReadOnly(true);

}
WidgetBuildFile::~WidgetBuildFile()
{
    delete ui;
}

void WidgetBuildFile::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->lineEdit_7->setText(item->text());
    BuildPath = FP;

}

void WidgetBuildFile::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
   ui->lineEdit_7->setText(item->text());
   BuildPath = SP;
}

bool WidgetBuildFile::duplicate_check(QString Path,QString fileName){
    QDirIterator it(Path,QDir::AllEntries|QDir::NoDotAndDotDot| QDir::NoSymLinks);
    while(it.hasNext()){
        it.next();
        if(fileName==it.fileName()){
            return false;
        }
    }
    return true;
}

void WidgetBuildFile::on_CancelButton_clicked()
{
    this->close();
}

void WidgetBuildFile::on_ConfirmButton_clicked()
{
    QString fileName = ui->lineEdit_9->text();
    QString type = ui->lineEdit_7->text().toLower();
    QString newName;



    if(fileName.isEmpty()){
        QMessageBox::warning(this,"Error","File name can't be empty!");
    }else{
        if(type == "folder") newName = fileName;
        else newName = fileName+"."+type;


        if(duplicate_check(BuildPath,newName)){
            if(type=="folder"){
                QDir *dir = new QDir();
                bool ok=dir->mkdir(BuildPath+"\\"+newName);
                if(!ok) QMessageBox::warning(this,"Error","Failure to Create");
                else this->close();
            }
            else{
                QFile filePath(BuildPath+"\\"+newName);


                if(!filePath.open(QIODevice::WriteOnly))
                    QMessageBox::warning(this,"Error","Failure to Create");
                filePath.close();

               //
                   QJsonObject Ablock;
                   QJsonArray Blocks;
                   Ablock.insert("position",0);
                   Ablock.insert("mainInfo","header");
                   Blocks.append(Ablock);
                   qDebug()<<Blocks;
                   QJsonDocument rootDoc;
                   rootDoc.setArray(Blocks);
                   QByteArray rootStr = rootDoc.toJson(QJsonDocument::Compact);
                   QString jsonString(rootStr);
                   qDebug() << jsonString;

                   //QString fileName = jsonPath + realNameWithoutSuffix+".json";
                   QString jsonName = "C:/Users/vielo/Documents/QtProjects/MapNote/json/"+fileName+ ".json";
                   //QString fileName  = QFileDialog::getOpenFileName(this, "open");

                   qDebug()<<jsonName;
                   QFile file(jsonName);

                   if (!file.open(QFile::WriteOnly | QFile::Text)) {
                          QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
                          return;
                      }



                       QTextStream out(&file);

                       out << jsonString;
                       file.close();
               //


                this->close();
            }

        }else{
            QMessageBox::warning(this,"Error","Naming Duplicate");
        }
    }


}
