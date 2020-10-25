#ifndef WIDGET_H
#define WIDGET_H

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
namespace Ui { class Widget; }
class QComboBox;
class QLabel;
class QPushButton;
class QTableWidget;
class QTableWidgetItem;
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QString sPath;

private slots:

    void find();
    void browse();
    void on_SearchButton_clicked();
    void showfile(QStringList &file_found_name,QStringList &file_found_path);
    void on_ChangePath_clicked();
    void InitTableWidget();
    void InitTreeView_2();
    void on_tableWidget_itemClicked(QTableWidgetItem *item);
    void on_ResetButton_clicked();
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);
    void on_BuildFile_clicked();
    void on_treeView_2_clicked(const QModelIndex &index);
    void on_SearchTips_clicked();
    void on_DeleteButton_clicked();
    void on_RenameButton_clicked();
    void HideRenameBox();
    void on_rename_ok_clicked();
    void on_rename_cancel_clicked();
    void deletefile();
    void on_treeView_2_doubleClicked(const QModelIndex &index);



private:
    Ui::Widget *ui;
    QFileSystemModel *dirmodel;
    QFileSystemModel *filemodel;
    QDir currentDir;
    QMenu *foldermenu;
    QString CreatePath1,CreatePath2;


};





#endif // WIDGET_H
