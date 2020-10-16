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
    void toHeading2();
    void toHeading3();
    void toRed();
    void toBlue();
    void toYellow();
    void toRedBackground();
    void toBlueBackground();
    void toYellowBackground();
    void toPara();
    void toDiv();
    void toBulletList();
    void toCircleList();

    void pleaseSearch(QString searchContent);



private slots:
  void on_heading1_clicked();

  void on_toPlain_clicked();

  void on_heading2_clicked();

  void on_heading3_clicked();

  void on_red_clicked();

  void on_blue_clicked();

  void on_yellow_clicked();

  void on_redBackground_clicked();

  void on_blueBackground_clicked();

  void on_yellowbackground_clicked();

  void on_Para_clicked();

  void on_Div_clicked();

  void on_pushButton_5_clicked();

  void on_circleList_clicked();

  void on_searcBut_clicked();


private:
    Ui::chooseModal *ui;
};

#endif
// CHOOSEMODAL_H
