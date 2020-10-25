#ifndef DELETEWIDGET_H
#define DELETEWIDGET_H
#include<QWidget>
#include<QFileSystemModel>
#include<QFileDialog>
#include<QFile>
#include<QDir>
#include<QtCore>
#include<QtGui>
#include<QDialog>
#include<QtWidgets>


QT_BEGIN_NAMESPACE
namespace Ui {
class DeleteWidget;
}
class QComboBox;
class QLabel;
class QPushButton;
class QTableWidget;
class QTableWidgetItem;
QT_END_NAMESPACE


class DeleteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeleteWidget(QWidget *parent = nullptr,QString Name = nullptr);
    ~DeleteWidget();
signals:
    void to_ok();
    void to_cancel();

private slots:
    void on_confirm_clicked();

    void on_cancelButton_clicked();

private:
    Ui::DeleteWidget *ui;


};
#endif // DELETEWIDGET_H
