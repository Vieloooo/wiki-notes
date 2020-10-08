#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Wiki-note");
    w.setWindowIcon(QIcon(":/imgs/Icons/mainIcon.png"));
    w.show();
    return a.exec();
}
