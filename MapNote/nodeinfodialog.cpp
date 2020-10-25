#include <QtWidgets>
#include "nodeinfodialog.h"
#include "node.h"

NodeInfoDialog::NodeInfoDialog(Node *node, QWidget *parent) :
    QDialog(parent)
{
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    this->resize(350, 160);
    if (!node)
        exit(-1);

    this->setModal(false);
    this->setAttribute(Qt::WA_DeleteOnClose);

    m_node = node;

    initNodeInfoDialog();
}

NodeInfoDialog::~NodeInfoDialog()
{

}
//析构函数

void NodeInfoDialog::initNodeInfoDialog()
{
    m_nameLabel = new QLabel("Name:", this);
    m_nameLabel->setFixedWidth(72);
    m_nameEdit = new QLineEdit(this);
    m_nameEdit->setReadOnly(true);
    m_nameEdit->setText(m_node->getText());
    QHBoxLayout *hLayout1 = new QHBoxLayout();
    hLayout1->addWidget(m_nameLabel);
    hLayout1->addWidget(m_nameEdit);

    m_xLabel = new QLabel("X:", this);
    m_xLabel->setFixedWidth(72);
    m_xEdit = new QLineEdit(this);
    m_xEdit->setReadOnly(true);
    m_xEdit->setText(tr("%1").arg(m_node->x(), 0, 'f', 2));
    QHBoxLayout *hLayout2 = new QHBoxLayout();
    hLayout2->addWidget(m_xLabel);
    hLayout2->addWidget(m_xEdit);

    m_yLabel = new QLabel("Y:", this);
    m_yLabel->setFixedWidth(72);
    m_yEdit = new QLineEdit(this);
    m_yEdit->setReadOnly(true);
    m_yEdit->setText(tr("%1").arg(m_node->y(), 0, 'f', 2));
    QHBoxLayout *hLayout3 = new QHBoxLayout();
    hLayout3->addWidget(m_yLabel);
    hLayout3->addWidget(m_yEdit);

    m_parentCountLabel = new QLabel("ParentCount:", this);
    m_parentCountLabel->setFixedWidth(72);
    m_parentCountEdit = new QLineEdit(this);
    m_parentCountEdit->setReadOnly(true);
    QHBoxLayout *hLayout4 = new QHBoxLayout();
    hLayout4->addWidget(m_parentCountLabel);
    hLayout4->addWidget(m_parentCountEdit);

    if (m_node->getLinkFrom()) {
        m_parentCountEdit->setText("1");
    }
    else {
        m_parentCountEdit->setText("0");
    }

    m_childCountLabel = new QLabel("ChildCount:", this);
    m_childCountLabel->setFixedWidth(72);
    m_childCountEdit = new QLineEdit(this);
    m_childCountEdit->setReadOnly(true);
    QHBoxLayout *hLayout5 = new QHBoxLayout();
    hLayout5->addWidget(m_childCountLabel);
    hLayout5->addWidget(m_childCountEdit);

    int childCount = m_node->getLinksTo().size();
    m_childCountEdit->setText(QString::number(childCount, 10));

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    vLayout->addLayout(hLayout3);
    vLayout->addLayout(hLayout4);
    vLayout->addLayout(hLayout5);
    this->setLayout(vLayout);
}
