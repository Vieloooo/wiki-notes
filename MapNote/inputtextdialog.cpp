#include <QtWidgets>
#include "inputtextdialog.h"

InputTextDialog::InputTextDialog(QDialog *parent) :
    QDialog(parent)
{
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    this->setFixedSize(330, 90);
//设置弹窗大小

    initInputTextDialog();
//文本框的初态
}

InputTextDialog::~InputTextDialog()
{

}
//析构函数

void InputTextDialog::initInputTextDialog()
{
    m_inputTextLabel = new QLabel("Input text:", this);
    QHBoxLayout *hLayout1 = new QHBoxLayout();
    hLayout1->addWidget(m_inputTextLabel);
    hLayout1->addStretch();

    m_inputTextEdit = new QTextEdit(this);
    QHBoxLayout *hLayout2 = new QHBoxLayout();
    hLayout2->addWidget(m_inputTextEdit);

    m_okBtn = new QPushButton("OK", this);
    m_cancelBtn = new QPushButton("Cancel", this);
    connect(m_okBtn, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(m_cancelBtn, SIGNAL(clicked(bool)), this, SLOT(close()));
    //信号与槽函数
    QHBoxLayout *hLayout3 = new QHBoxLayout();
    //水平布局
    hLayout3->addStretch();
    //添加一个可伸缩空间
    hLayout3->addWidget(m_okBtn);
     //添加控件
    hLayout3->addWidget(m_cancelBtn);
    //添加控件

    QVBoxLayout *vLayout = new QVBoxLayout();
    //垂直布局
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    vLayout->addLayout(hLayout3);
    //添加布局
    this->setLayout(vLayout);
}

void InputTextDialog::setInputTextDialogText(const QString &toPlainText)
{
    m_inputTextEdit->setPlainText(toPlainText);

}
//设置文本框

QString InputTextDialog::getInputTextDialogText()
{
    return m_inputTextEdit->toPlainText();
}
//返回文本框中内容
