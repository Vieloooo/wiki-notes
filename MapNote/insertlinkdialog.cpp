#include <QtWidgets>
#include "insertlinkdialog.h"

InsertLinkDialog::InsertLinkDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    this->resize(400, 90);

    initInsertLinkDialog();
}

InsertLinkDialog::~InsertLinkDialog()
{

}
//析构函数

void InsertLinkDialog::initInsertLinkDialog()
{
    m_addressLabel = new QLabel("Address:", this);

    m_addressEdit = new QLineEdit(this);
    m_browseBtn = new QPushButton("Browse", this);
    connect(m_browseBtn, SIGNAL(clicked(bool)), this, SLOT(onBrowse()));
    QHBoxLayout *hLayout1 = new QHBoxLayout();
    hLayout1->addWidget(m_addressLabel);
    hLayout1->addWidget(m_addressEdit);
    hLayout1->addWidget(m_browseBtn);
//向布局中添加控件

    m_okBtn = new QPushButton("OK", this);
    connect(m_okBtn, SIGNAL(clicked(bool)), this, SLOT(accept()));
    m_cancelBtn = new QPushButton("Cancel", this);
    connect(m_cancelBtn, SIGNAL(clicked(bool)), this, SLOT(close()));
    QHBoxLayout *hLayout2 = new QHBoxLayout();
    hLayout2->addStretch();
//平均分配布局

    hLayout2->addWidget(m_okBtn);
    hLayout2->addWidget(m_cancelBtn);
//向布局中添加小布局

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    this->setLayout(vLayout);
    //设置为布局
}

QString InsertLinkDialog::getLinkAddress()
{
    return m_addressEdit->text();
}
//在文本框内插入链接

void InsertLinkDialog::onBrowse()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Insert Link", QApplication::applicationDirPath(), "All files(*)");
    if (fileName.isEmpty())
        return;

    m_addressEdit->setText(fileName);
}
//搜索链接文件位置
