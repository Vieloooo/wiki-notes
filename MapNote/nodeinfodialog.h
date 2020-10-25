#ifndef NODEINFODIALOG_H
#define NODEINFODIALOG_H

#include <QDialog>

class Node;
class QLabel;
class QLineEdit;
class NodeInfoDialog : public QDialog
{
    Q_OBJECT
//宏，发送信号时自动调用槽

public:
    explicit NodeInfoDialog(Node *node, QWidget *parent = 0);
    ~NodeInfoDialog();
//析构函数

    void initNodeInfoDialog();

private:
    QLabel    *m_nameLabel;
    QLineEdit *m_nameEdit;
    QLabel    *m_xLabel;
    QLineEdit *m_xEdit;
    QLabel    *m_yLabel;
    QLineEdit *m_yEdit;
    QLabel    *m_parentCountLabel;
    QLineEdit *m_parentCountEdit;
    QLabel    *m_childCountLabel;
    QLineEdit *m_childCountEdit;

    Node      *m_node;

};

#endif
