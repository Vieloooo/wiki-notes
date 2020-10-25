#include <QtWidgets>
#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    this->setFixedSize(400, 100);
//设置弹出窗口的大小

    initAboutDialog();
//初始化about对话框
}

AboutDialog::~AboutDialog()
{

}
//析构函数

void AboutDialog::initAboutDialog()
{
    m_versionLabel = new QLabel("Version:", this);
    m_versionNumLabel = new QLabel("1.0", this);
    QHBoxLayout *hLayout1 = new QHBoxLayout();
    hLayout1->addWidget(m_versionLabel);
//添加部件
    hLayout1->addWidget(m_versionNumLabel);
    hLayout1->addStretch();
//按比例分配空余空间

    m_copyrightLabel = new QLabel("Copyright:", this);
    m_copyrightInfoLabel = new QLabel("Copyright 2020. All rights reserved", this);
    QHBoxLayout *hLayout2 = new QHBoxLayout();
//水平布局
    hLayout2->addWidget(m_copyrightLabel);
    hLayout2->addWidget(m_copyrightInfoLabel);
    hLayout2->addStretch();
//按比例分配空余空间

    m_okBtn = new QPushButton("OK", this);
    connect(m_okBtn, SIGNAL(clicked(bool)), this, SLOT(close()));
//单击后发出信号至槽，关闭窗口
    QHBoxLayout *hLayout3 = new QHBoxLayout();
    hLayout3->addStretch();
//按比例分配空余空间
    hLayout3->addWidget(m_okBtn);

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    vLayout->addSpacing(4);
//将两个layout相加，在该布局末尾加上一个长度为4的空白项

    vLayout->addLayout(hLayout3);
    this->setLayout(vLayout);
//设置布局
}
