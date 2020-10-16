#ifndef MAININFO_H
#define MAININFO_H

#include <QDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonArray>


namespace Ui {
class MainInfo;
}

class MainInfo : public QDialog
{
    Q_OBJECT



public:
    explicit MainInfo(QWidget *parent = nullptr,int posi=0 ,QString jsonName="");
    ~MainInfo();
    QString Info= "";
    QString jsonFile ="";
    int position = 0;
    QJsonArray arr ;

private slots:
    void on_pushButton_clicked();

signals:


private:
    Ui::MainInfo *ui;
};

#endif // MAININFO_H
