#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QMainWindow>

#include "choosemodal.h"

#include "maininfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,QString path = "");
    ~MainWindow();

    QString jsonfile ="";
    QString realNameWithoutSuffix="";

    //eternal path

    QString notePath = ":/notes/notes/";
    QString jsonPath = ":/Json/Json/";
public:
    Ui::MainWindow *ui;

public slots:
    void handlePlainText();

    void handleHeading1();

    void handleHeading2();

    void handleHeading3();

    void handleRed();

    void handleBlue();

    void handleYellow();

    void handleRedBackground();

    void handleBlueBackground();

    void handleYellowBackground();

    void handlePara();

    void handleDiv();

    void handleBullet();

    void handleCircle();

    void turnToPosition(int posi);


    void createJsonFile();

    void handleSearch(QString searchContent);

    void handleOpen(QString filePath);


private slots:

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

   // void on_actionchoose_triggered();

    void on_actioncopy_triggered();

    void on_actionpaste_triggered();

    void on_actioncut_triggered();

    void on_actionredo_triggered();

    void on_actionundo_triggered();

    void on_actionPrint_2_triggered();

    void on_actiontoPDF_triggered();

    void on_actiontoHTML_triggered();

    void on_actiontoMarkdown_triggered();

    void on_actionstyle_triggered();

   // void handleOpen(QString filePath);


    void on_actionMap_triggered();

    void on_actionFile_triggered();

private:
    QString currentFile ="";


};
#endif

// MAINWINDOW_H
