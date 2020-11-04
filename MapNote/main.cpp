#include "mainwindow.h"
#include "mindmapdialog.h"
#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow textModule;
   Widget fileModule;
   //MindMapDialog mapModule;

    //textModule.setWindowTitle("Wiki-note");
    //textModule.show();
    //connect(*fileModule,)
   // mapModule.show();

        //fileModule.resize(40,600);
    fileModule.show();


    return a.exec();
}
