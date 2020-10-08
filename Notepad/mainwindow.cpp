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
#include <QBrush>
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
    QString initText = "<h1>Welcome to Wiki-Note</h1>"
                       "<h3>A HTML based editing tool with Mindmap.</h3>";
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
    //unreadable fuc1
    /*
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
        */

    //fuc 2, need to input suffix .html
    QFileDialog fileDialog(this, "Export Html");

    //new file name
    QString fileName = fileDialog.getSaveFileName();
    fileDialog.setDefaultSuffix("html");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
           QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
           return;
       }
    setWindowTitle("saveHtml"+fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toHtml();
    out << text;
    file.close();


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

void MainWindow::handleHeading2()
{

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();

    blockFmt.setHeadingLevel(2);
    QTextCharFormat fmt;
           fmt.setFontWeight(2 ? QFont::Bold : QFont::Normal);
           fmt.setProperty(QTextFormat::FontSizeAdjustment, 2);
           cursor.select(QTextCursor::LineUnderCursor);
           cursor.mergeCharFormat(fmt);
           ui->textEdit->mergeCurrentCharFormat(fmt);

    cursor.setBlockFormat(blockFmt);
    cursor.endEditBlock();
     //ui->textEdit->setText("");

}

void MainWindow::handleHeading3()
{

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();

    blockFmt.setHeadingLevel(3);
    QTextCharFormat fmt;
           fmt.setFontWeight(3 ? QFont::Bold : QFont::Normal);
           fmt.setProperty(QTextFormat::FontSizeAdjustment, 1);
           cursor.select(QTextCursor::LineUnderCursor);
           cursor.mergeCharFormat(fmt);
           ui->textEdit->mergeCurrentCharFormat(fmt);

    cursor.setBlockFormat(blockFmt);
    cursor.endEditBlock();


}

void MainWindow::handlePara()
{

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();

    blockFmt.setHeadingLevel(0);
    QTextCharFormat fmt;
           fmt.setFontWeight(0 ? QFont::Bold : QFont::Normal);
           fmt.setProperty(QTextFormat::FontSizeAdjustment, 0);
           cursor.select(QTextCursor::LineUnderCursor);
           cursor.mergeCharFormat(fmt);
           ui->textEdit->mergeCurrentCharFormat(fmt);

    cursor.setBlockFormat(blockFmt);
    cursor.endEditBlock();


}


void MainWindow::on_actionstyle_triggered()
{
    chooseModal  *modal = new chooseModal(this);
    modal->setWindowTitle("Style");
        modal->show();
       QObject::connect(modal, &chooseModal::toPlainText,this,&MainWindow::handlePlainText);
       QObject::connect(modal, &chooseModal::toHeading1,this,&MainWindow::handleHeading1);
       QObject::connect(modal, &chooseModal::toHeading2,this,&MainWindow::handleHeading2);
       QObject::connect(modal, &chooseModal::toHeading3,this,&MainWindow::handleHeading3);
       QObject::connect(modal, &chooseModal::toPara,this,&MainWindow::handlePara);
       QObject::connect(modal, &chooseModal::toRed,this,&MainWindow::handleRed);
       QObject::connect(modal, &chooseModal::toBlue,this,&MainWindow::handleBlue);
       QObject::connect(modal, &chooseModal::toYellow,this,&MainWindow::handleYellow);
       QObject::connect(modal, &chooseModal::toRedBackground,this,&MainWindow::handleRedBackground);
       QObject::connect(modal, &chooseModal::toBlueBackground,this,&MainWindow::handleBlueBackground);
       QObject::connect(modal, &chooseModal::toYellowBackground,this,&MainWindow::handleYellowBackground);

}



void MainWindow::handleRed()
{

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();
    QTextCharFormat fmt;
    fmt.setForeground(QColor(210, 55, 10,230));
    cursor.select(QTextCursor::LineUnderCursor);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->mergeCurrentCharFormat(fmt);
    cursor.setBlockFormat(blockFmt);
    cursor.endEditBlock();
}

void MainWindow::handleBlue()
{

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();
    QTextCharFormat fmt;
    fmt.setForeground(QColor(0, 172, 230,200));
    cursor.select(QTextCursor::LineUnderCursor);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->mergeCurrentCharFormat(fmt);
    cursor.setBlockFormat(blockFmt);
    cursor.endEditBlock();
}

void MainWindow::handleYellow()
{

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();
    QTextCharFormat fmt;

    fmt.setBackground(QColor(255, 209, 77,200));
    cursor.select(QTextCursor::LineUnderCursor);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->mergeCurrentCharFormat(fmt);
    cursor.setBlockFormat(blockFmt);
    cursor.endEditBlock();
}

void MainWindow::handleRedBackground()
{

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();
    QTextCharFormat fmt;
    fmt.setForeground(QColor(210, 55, 10,230));
    cursor.select(QTextCursor::LineUnderCursor);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->mergeCurrentCharFormat(fmt);
    cursor.setBlockFormat(blockFmt);
    cursor.endEditBlock();
}

void MainWindow::handleBlueBackground()
{

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();
    QTextCharFormat fmt;
    fmt.setBackground(QColor(0, 172, 230,60));
    cursor.select(QTextCursor::LineUnderCursor);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->mergeCurrentCharFormat(fmt);
    cursor.setBlockFormat(blockFmt);
    cursor.endEditBlock();
}

void MainWindow::handleYellowBackground()
{

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();
    QTextCharFormat fmt;

    fmt.setBackground(QColor(255, 209, 77,50));
    cursor.select(QTextCursor::LineUnderCursor);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->mergeCurrentCharFormat(fmt);
    cursor.setBlockFormat(blockFmt);
    cursor.endEditBlock();
}
