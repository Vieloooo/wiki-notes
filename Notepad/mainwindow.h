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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    Ui::MainWindow *ui;

public slots:
    void MainWindow::handlePlainText();

    void MainWindow::handleHeading1();

    void MainWindow::handleHeading2();

    void MainWindow::handleHeading3();

    void MainWindow::handleRed();

    void MainWindow::handleBlue();

    void MainWindow::handleYellow();

    void MainWindow::handleRedBackground();

    void MainWindow::handleBlueBackground();

    void MainWindow::handleYellowBackground();

    void MainWindow::handlePara();


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

private:
    QString currentFile ="";

};
#endif // MAINWINDOW_H
