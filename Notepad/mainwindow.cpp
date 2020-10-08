#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QColorDialog>
#include <QComboBox>
#include <QFontComboBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QMenu>
#include <QMenuBar>
#include <QTextCodec>
#include <QTextEdit>
#include <QStatusBar>
#include <QToolBar>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QTextList>
#include <QtDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QMimeData>
#include <QMimeDatabase>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif
#include <QPrinter>
#if QT_CONFIG(printpreviewdialog)
#include <QPrintPreviewDialog>
#endif
#endif
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   this->setCentralWidget(ui->textEdit);
    QString initText = "<h1>welcome to Notepad</h1><h5>this is a heading5</h5>";
    ui->textEdit->setText(initText);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());

}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"files");
    QFile file(fileName);
    currentFile=fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
           QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
           return;
       }
    setWindowTitle("In"+currentFile);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"save");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
           QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
           return;
       }

    currentFile = fileName;
        setWindowTitle("save"+fileName);
        QTextStream out(&file);
        QString text = ui->textEdit->toHtml();
        out << text;
        file.close();

}



void MainWindow::on_actioncopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionpaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actioncut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionredo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionundo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionPrint_2_triggered()
{
    QPrinter printer;

       printer.setPrinterName("wiki-printer");

       QPrintDialog pDialog(&printer, this);
        //error callback
       if(pDialog.exec() == QDialog::Rejected){
           QMessageBox::warning(this, "Warning", "Cannot Access Printer");
           return;
       }


       ui->textEdit->print(&printer);
}


void MainWindow::on_actiontoPDF_triggered()
{
    QFileDialog fileDialog(this, "Export PDF");
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
        fileDialog.setMimeTypeFilters(QStringList("application/pdf"));
        fileDialog.setDefaultSuffix("pdf");

        //iferr
        if (fileDialog.exec() != QDialog::Accepted)
            return;

        //get pdf filename
        QString fileName = fileDialog.selectedFiles().first();
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        //write pdf file
        ui->textEdit->document()->print(&printer);

        statusBar()->showMessage(tr("Exported \"%1\"")
                                    .arg(QDir::toNativeSeparators(fileName)));
}

void MainWindow::on_actiontoHTML_triggered()
{
    QFileDialog fileDialog(this, "Export HTML");
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
        fileDialog.setMimeTypeFilters(QStringList("text/html"));
        fileDialog.setDefaultSuffix("html");

        //iferr
        if (fileDialog.exec() != QDialog::Accepted)
            return;

        //new file name
        QString fileName = fileDialog.selectedFiles().first();
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::NativeFormat);
        printer.setOutputFileName(fileName);

         //write it
        ui->textEdit->document()->print(&printer);

        statusBar()->showMessage(tr("Exported \"%1\"")
                                    .arg(QDir::toNativeSeparators(fileName)));
}

void MainWindow::on_actiontoMarkdown_triggered()
{

        //fuc 1, need to input suffix .md
        QFileDialog fileDialog(this, "Export Markdown");

        //new file name
        QString fileName = fileDialog.getSaveFileName();
        fileDialog.setDefaultSuffix("md");
        QFile file(fileName);

        if (!file.open(QFile::WriteOnly | QFile::Text)) {
               QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
               return;
           }
        setWindowTitle("saveMarkdown"+fileName);
        QTextStream out(&file);
        QString text = ui->textEdit->toMarkdown();
        out << text;
        file.close();


    /* fuc2 with some error ,device not open
    QFileDialog fileDialog(this, "Export MD");
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
        fileDialog.setMimeTypeFilters(QStringList("text/markdown"));
        fileDialog.setDefaultSuffix("md");

        //iferr
        if (fileDialog.exec() != QDialog::Accepted)
            return;

        //new file name
        QString fileName = fileDialog.selectedFiles().first();
        QFile file(fileName);
        QTextStream out(&file);
        QString text = ui->textEdit->toMarkdown();
        out << text;
        file.close();

        */
}

void MainWindow::handlePlainText()
{
    ui->textEdit->toPlainText();
         //ui->textEdit->setText("");
}

void MainWindow::handleHeading1()
{

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();

    blockFmt.setHeadingLevel(1);

    QTextCharFormat fmt;
           fmt.setFontWeight(1 ? QFont::Bold : QFont::Normal);
           fmt.setProperty(QTextFormat::FontSizeAdjustment, 3);
           cursor.select(QTextCursor::LineUnderCursor);
           cursor.mergeCharFormat(fmt);
           ui->textEdit->mergeCurrentCharFormat(fmt);

    cursor.setBlockFormat(blockFmt);
    cursor.endEditBlock();

    //success setting the tag to h5 and updating  the style
     //ui->textEdit->setText("");

}


void MainWindow::on_actionstyle_triggered()
{
    chooseModal  *modal = new chooseModal(this);
        modal->show();
       QObject::connect(modal, &chooseModal::toPlainText,this,&MainWindow::handlePlainText);
       QObject::connect(modal, &chooseModal::toHeading1,this,&MainWindow::handleHeading1);

}
