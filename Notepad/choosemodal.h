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

public slots:

    void on_toPlain_clicked();

private:
    Ui::chooseModal *ui;
};

#endif
// CHOOSEMODAL_H
