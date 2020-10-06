#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QString currentText = "<h1>hello</h1>";
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
   //ui->textEdit->setAcceptRichText((false));
    ui->textEdit->setText(currentText);

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
    QString fileName = QFileDialog::getOpenFileName(this, "Files");

       // An object for reading and writing files
       QFile file(fileName);

       // Store the currentFile name
       currentFile = fileName;

       // Try to open the file as a read only file if possible or display a
       // warning dialog box
       if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
           QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
           return;
       }

       // Set the title for the window to the file name
       setWindowTitle(fileName);

       // Interface for reading text
       QTextStream in(&file);

       // Copy text in the string
       QString text = in.readAll();

       // Put the text in the textEdit widget
       ui->textEdit->setText(text);

       // Close the file
       file.close();
}

void MainWindow::on_actionSave_triggered()
{
    //open a dialog for saving file
    QString fileName=QFileDialog::getSaveFileName(this,"save as");
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
            return;
        }

    currentFile=fileName;

    setWindowTitle(fileName);

    QTextStream out(&file);
    QString text= ui->textEdit->toPlainText();
    out << text;
    file.close();

}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("myPrinter");

    QPrintDialog printDialog(&printer,this);
    if(printDialog.exec()==QDialog::Rejected){
        QMessageBox::warning(this, "Warning", "Cannot Access Printer");
              return;
    }
     ui->textEdit->print(&printer);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}
