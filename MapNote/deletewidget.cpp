#include "deletewidget.h"
#include "ui_deletewidget.h"

DeleteWidget::DeleteWidget(QWidget *parent,QString Name)
    : QWidget(parent)
    , ui(new Ui::DeleteWidget)
{
   ui->setupUi(this);
   setWindowTitle("Delete");
   ui->lineEdit->setText("Are you sure delete ");
   ui->lineEdit_2->setText("the \""+Name+"\"");
   ui->lineEdit->setEnabled(false);
   ui->lineEdit_2->setEnabled(false);
   ui->lineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
   ui->lineEdit_2->setStyleSheet("background:transparent;border-width:0;border-style:outset");

   setFixedSize(199,103);


}
DeleteWidget::~DeleteWidget()
{
    delete ui;
}

void DeleteWidget::on_confirm_clicked()
{
    emit to_ok();
    this->close();
}

void DeleteWidget::on_cancelButton_clicked()
{
    this->close();
}
