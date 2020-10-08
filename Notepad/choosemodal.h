#ifndef CHOOSEMODAL_H
#define CHOOSEMODAL_H

#include <QDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace Ui {
class chooseModal;
}

class chooseModal : public QDialog
{
    Q_OBJECT

public:
    explicit chooseModal(QWidget *parent = nullptr);
    ~chooseModal();

signals:
    void toPlainText();
    void toHeading1();


private slots:
  void on_heading1_clicked();
  void on_toPlain_clicked();
private:
    Ui::chooseModal *ui;
};

#endif
// CHOOSEMODAL_H
