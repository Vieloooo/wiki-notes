#ifndef INSERTLINKDIALOG_H
#define INSERTLINKDIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class InsertLinkDialog : public QDialog
{
    Q_OBJECT
//宏，发送信号时自动调用槽

public:
    explicit InsertLinkDialog(QWidget *parent = 0);
//显示调用

    ~InsertLinkDialog();
//析构函数

    void initInsertLinkDialog();

    QString getLinkAddress();
//实现字符串处理功能

private:
    QLabel      *m_addressLabel;
    QLineEdit   *m_addressEdit;
    QPushButton *m_browseBtn;
    QPushButton *m_okBtn;
    QPushButton *m_cancelBtn;

public slots:
    void onBrowse();

};

#endif
