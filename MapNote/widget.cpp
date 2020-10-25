#include "widget.h"
#include "ui_widget.h"
#include "widgetbuildfile.h"
#include"deletewidget.h"
#include <iostream>
#include <string>
#include <vector>

#include <mainwindow.h>
using namespace std;
/**----------------KMP Alogrithem for searching file ---------------------------------*/
vector<int> GetNext(QString p)
{
    int pLen = p.size();
    vector<int> next(pLen, 0);
    next[0] = -1;
    int k = -1;
    int j = 0;
    while (j < pLen - 1)
    {
        //p[k]表示前缀，p[j]表示后缀
        if (k == -1 || p[j] == p[k])
        {
            ++k;
            ++j;
            next[j] = k;
        }
        else
        {
            k = next[k];
        }
    }
    return next;
}

int KmpSearch(QString s, QString p)
{
    int i = 0;
    int j = 0;
    int sLen = s.size();
    int pLen = p.size();
    vector<int> next = GetNext(p);
    while (i < sLen && j < pLen)
    {
        //①如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++
        if (j == -1 || s[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            //②如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]
            //next[j]即为j所对应的next值
            j = next[j];
        }
    }
    if (j == pLen)
        return i - j;
    else
        return -1;
}
/**----------------Universal Function(Not in Class)---------------------------------*/

QString Get_suffix(QString filepath){                   //"filepath" is absolutely file path,this function is to get the suffix without".",for example,it will
    QFileInfo *fileinfo = new QFileInfo(filepath);      //return "txt" when filepath is "E:\wikinote\sample1\china.txt"
    return fileinfo->suffix();                          //It will return an empty string if it's a folder
}

QString Get_name_nosuffix(QString filepath){
    QFileInfo *fileinfo = new QFileInfo(filepath);
    return fileinfo->baseName();                        //Get pure filename without suffix
}

QString Get_name(QString filepath){
    QFileInfo *fileinfo = new QFileInfo(filepath);
    return fileinfo->fileName();
}

/**---------------------------------------------------------------------------------*/
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    /**获取文件存储位置的根目录路径*/
    /*
    QString fileName = "D:\\Qt\\files\\untitled\\SavePath.txt";
    //保存(文件存储路径)的txt文件路径
    QFile f(fileName);
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream txtInput(&f);
    while(!txtInput.atEnd())
    {
        sPath = txtInput.readLine();
    }
    currentDir = QDir(sPath);
    f.close();

    */


    sPath = "C:/Users/vielo/Documents/QtProjects/MapNote/notes";
    CreatePath1 = sPath;
    currentDir = QDir(sPath);
    qDebug()<<currentDir;
    //初始化treeview_2，该框为项目文件浏览框
    InitTreeView_2();
    //将搜索框状态设置为可以编辑
    ui->SearchComboBox->setEditable(true);
    //初始化搜索结果显示框
    InitTableWidget();
    //按钮状态设置
    ui->SearchButton->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->SearchButton->setShortcut(tr("Ctrl+f"));
    ui->SearchButton->setToolTip("Ctrl+F");
    //RenameBoxInitialize
    HideRenameBox();

    ui->BuildFile->setToolTip("Build");
    ui->DeleteButton->setToolTip("Delete");
    ui->RenameButton->setToolTip("Rename");

    ui->CurrentPath->setText(sPath);
    ui->CurrentPath->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->CurrentPath->setReadOnly(true);


    //ui->tableWidget->hide();
   // ui->SearchTips->hide();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::InitTableWidget(){

    ui->tableWidget->setColumnCount(1);   //设置只有一列
    QStringList header;
    header << "Name";
    ui->tableWidget->setHorizontalHeaderLabels(header);   //设置行标题
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);//设置为无需拓展
    ui->tableWidget->setShowGrid(false);  //去掉格子框
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //禁止编辑
    ui->tableWidget->verticalHeader()->hide();   //去掉每一行前面的数字标号

}

void Widget::InitTreeView_2(){

    /**设置显示文件界面的基本状态*/
    filemodel = new QFileSystemModel(this);
    filemodel->setFilter(QDir::NoDotAndDotDot|QDir::AllDirs|QDir::Files);
    filemodel->setRootPath(sPath);  //不可删
    ui->treeView_2->setModel(filemodel);
    //隐藏Size
    ui->treeView_2->setColumnHidden(1,true);
    //隐藏Type
    ui->treeView_2->setColumnHidden(2,true);
    //隐藏Date Modified
    ui->treeView_2->setColumnHidden(3,true);
    //设置treeview_2的显示根目录
    ui->treeView_2->setRootIndex(filemodel->index(sPath));
}

void Widget::HideRenameBox(){

    ui->rename_ok->hide();
    ui->rename_cancel->hide();
    ui->rename_box->hide();
    ui->rename_box->clear();
    ui->rename_background->hide();
    ui->rename_background->setEnabled(false);
}

/**---------------------------------------------------------------------------------*/

static void updateComboBox(QComboBox *comboBox)
{
    /**更新搜索框，记录下之前的搜索记录*/
    if (comboBox->findText(comboBox->currentText()) == -1)
        comboBox->addItem(comboBox->currentText());
}

void Widget::on_SearchButton_clicked()
{
    ui->tableWidget->show();
    ui->SearchTips->show();
    find();
}

void Widget::showfile(QStringList &file_found_name,QStringList &file_found_path){

    ui->tableWidget->setRowCount(0); //每次展示搜索文件前都把行数归零
    int total = file_found_name.size();
    for(int i=0;i<total;i++){

        int rowCount = ui->tableWidget->rowCount();         //获取当前行数
        ui->tableWidget->insertRow(rowCount);              //插入新的一行
        QTableWidgetItem *Nameitem = new QTableWidgetItem;
        Nameitem->setText(file_found_name[i]);
        Nameitem->setTextAlignment(Qt::AlignLeft); //设置对齐方式
        Nameitem->setToolTip(file_found_path[i]);  //提示栏，将鼠标放在文件上时，会显示出该文件的路径
        ui->tableWidget->setItem(rowCount, 0, Nameitem);

    }

}

void Widget::find()
{
    QString filename;
    vector<int> next;
    if(!ui->SearchComboBox->currentText().isEmpty() && ui->SearchComboBox->currentText()!="Search Here"){
       updateComboBox(ui->SearchComboBox);
       filename = ui->SearchComboBox->currentText();   //获取要搜索的关键字
       QStringList file_found_name,file_found_path;    //两个list用于存储匹配的文件的名称和路径
       QDirIterator it(sPath,QDir::AllEntries|QDir::NoDotAndDotDot| QDir::NoSymLinks,QDirIterator::Subdirectories);  //当前路径下的文件遍历迭代器,"QDirIterator::Subdirectories"表示子文件内部也进行遍历
       while(it.hasNext()){
           it.next();
           if(KmpSearch(it.fileName(),filename)>=0){     //若当前文件名含有要查找的关键字，将其加入list
               file_found_name << it.fileName();
               file_found_path << it.filePath();
           }
       }
       showfile(file_found_name,file_found_path);       //将找到的文件展示在tablewidget中
    }
    else{                                               //若搜索框为空，将treevi_2框复原
         ui->treeView_2->setRootIndex(filemodel->index(sPath));
         ui->tableWidget->setRowCount(0);
         ui->tableWidget->hide();
         ui->SearchTips->hide();
      }

}

void Widget::on_SearchTips_clicked()
{
       QMessageBox::information(this,"Help","Hover cursor to check saving path\nClick for more details\nDouble click to open");
}

/**---------------------------------------------------------------------------------*/
//浏览本地，设置新的路径
void Widget::on_ChangePath_clicked()
{
    browse();
}

void Widget::browse()
{
    QString directory = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Change Path"), QDir::currentPath()));
    ui->treeView_2->setRootIndex(filemodel->index(directory));
    sPath = directory;  //更改路径后用sPath记录
    ui->CurrentPath->setText(sPath);
    /**将更改后的路径写入文档，以便下次读取，达到记录的目的*/
    QString fileName = "D:\\Qt\\files\\untitled\\SavePath.txt";
    QFile f(fileName);
    f.open(QIODevice::WriteOnly | QIODevice::Text); //以只写的方式打开
    QTextStream txtOutput(&f);
    txtOutput << directory;  //覆盖写入，用新路径覆盖原来的路径
    f.close();
}

/**---------------------------------------------------------------------------------*/

//点击搜索框中的文件，会将文件下的内容展示在treeview_2框中
void Widget::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    ui->treeView_2->setRootIndex(filemodel->index(item->toolTip()));
}
//将treevi_2框复原
void Widget::on_ResetButton_clicked()
{
    ui->treeView_2->setRootIndex(filemodel->index(sPath));
    ui->tableWidget->hide();
    ui->SearchTips->hide();
}

/**---------------------------------------------------------------------------------*/

void Widget::on_treeView_2_doubleClicked(const QModelIndex &index)
{
    CreatePath1 = filemodel->fileInfo(index).absoluteFilePath();
    if(!Get_suffix(CreatePath1).isEmpty())
    {
       // QDesktopServices::openUrl(QUrl(CreatePath1));
        //
        MainWindow *textComponents = new MainWindow(this,CreatePath1);
        textComponents->show();
        //open text module;

    }
}

void Widget::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{

    QString Path = item->toolTip();

    //QDesktopServices::openUrl(QUrl(Path));
    qDebug()<<Path;
    //open text module
    MainWindow *textComponents = new MainWindow(this,Path);
    textComponents->show();
    //
}

/**---------------------------------------------------------------------------------*/

void Widget::on_treeView_2_clicked(const QModelIndex &index)
{
    //创建文件时，点击treeview_2中的文件即获得创建路径,并保存
        CreatePath1 = sPath;
      CreatePath1 = filemodel->fileInfo(index).absoluteFilePath();
      CreatePath2 = filemodel->fileInfo(index).absolutePath();
}

void Widget::on_BuildFile_clicked()
{
    //点击创建文件按钮后，弹出新的创建文件窗口
    WidgetBuildFile *widgetbuildfile = new WidgetBuildFile(0,CreatePath1,sPath);
    widgetbuildfile->show();
}

/**---------------------------------------------------------------------------------*/

bool deleteDir(const QString &path)
{
    QDir dir(path);
    if(!dir.exists()){
        return true;
    }
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); //设置过滤
    QFileInfoList fileList = dir.entryInfoList(); // 获取所有的文件信息
    foreach (QFileInfo file, fileList){ //遍历文件信息
        if (file.isFile()){ // 是文件，删除
            file.dir().remove(file.fileName());
        }else{ // 递归删除
            deleteDir(file.absoluteFilePath());
        }
    }
    dir.rmpath(dir.absolutePath()); // 删除文件夹
    return true;
}

void Widget::on_DeleteButton_clicked()
{
   if(!CreatePath1.isEmpty()){
       DeleteWidget *deleteBox = new DeleteWidget(0,Get_name(CreatePath1));  //open delete question box
       deleteBox->show();                                              //Make sure user really want to delete this file
       QObject::connect(deleteBox,&DeleteWidget::to_ok,this,&Widget::deletefile);
   }
}

void Widget::deletefile(){

    if(Get_suffix(CreatePath1).isEmpty()){
        bool ok=deleteDir(CreatePath1);
        if(!ok){
            QMessageBox::warning(this,"Error","Fail to Delete");
        }
        CreatePath1.clear();
    }
    else{QFile file(CreatePath1);
        bool ok = file.remove();
        if(!ok){
            QMessageBox::warning(this,"Error","Fail to Delete");
        }
        CreatePath1.clear();
    }
}

/**---------------------------------------------------------------------------------*/

void Widget::on_RenameButton_clicked()
{
    if(!CreatePath1.isEmpty()){
        ui->rename_ok->show();
        ui->rename_cancel->show();
        ui->rename_box->show();
        ui->rename_background->show();
    }

}

void Widget::on_rename_ok_clicked()
{
    QString NewName = ui->rename_box->text();
    bool find=0;
    if(NewName.isEmpty()){
        QMessageBox::warning(this,"WARNING","Name can't be empty.");
    }else{

        QFile file(CreatePath1);
        QString filename = NewName+(Get_suffix(CreatePath1).isEmpty()?Get_suffix(CreatePath1):"."+Get_suffix(CreatePath1));
        QDirIterator it(CreatePath2,QDir::AllEntries|QDir::NoDotAndDotDot| QDir::NoSymLinks);

        while(it.hasNext()){
            it.next();
            if(filename==it.fileName()){
                QMessageBox::warning(this,"Error","\""+NewName+"\" already there");
                find=1;
                break;
            }
        }
        if(!find){
            bool ok;
            if(Get_suffix(CreatePath1).isEmpty()){ ok = file.rename(CreatePath2+"\\"+NewName);}
            else{ ok = file.rename(CreatePath2+"\\"+NewName+"."+Get_suffix(CreatePath1));}

            if(!ok){
                QMessageBox::warning(this,"Error","Rename Fail");
            }else{
                CreatePath1.clear();
                HideRenameBox();
            }
        }
    }

}

void Widget::on_rename_cancel_clicked()
{
    HideRenameBox();
}

/**---------------------------------------------------------------------------------*/

