#ifndef MAININFO_H
#define MAININFO_H

#include <QDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"


namespace Ui {
class MainInfo;
}

class MainInfo : public QDialog
{
    Q_OBJECT



public:
    explicit MainInfo(QWidget *parent = nullptr);
    ~MainInfo();

private slots:
    void on_pushButton_clicked();

signals:


private:
    Ui::MainInfo *ui;
};

#endif // MAININFO_H
