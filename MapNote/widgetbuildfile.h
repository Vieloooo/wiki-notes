#ifndef WIDGETBUILDFILE_H
#define WIDGETBUILDFILE_H

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
class WidgetBuildFile;
}
class QComboBox;
class QLabel;
class QPushButton;
class QTableWidget;
class QTableWidgetItem;
QT_END_NAMESPACE


class WidgetBuildFile : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetBuildFile(QWidget *parent = nullptr,QString CreatePath = nullptr,QString FirstPath=nullptr);
    ~WidgetBuildFile();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_listWidget_2_itemClicked(QListWidgetItem *item);
    void on_CancelButton_clicked();
    bool duplicate_check(QString Path,QString fineName);
    void on_ConfirmButton_clicked();

private:
    Ui::WidgetBuildFile *ui;
    QString BuildPath,FP,SP,Type; //FP=FirstPath,SP=SecondPath


};
#endif // WIDGETBUILDFILE_H
