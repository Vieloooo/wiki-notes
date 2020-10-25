#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

class QLabel;
//QT界面中的标签类
class AboutDialog : public QDialog
//AboutDialog继承自QDialog
{
    Q_OBJECT
//宏，发送信号时自动调用槽

public:
    explicit AboutDialog(QWidget *parent = 0);
//显示调用

    virtual ~AboutDialog();
//虚函数，析构函数

    void initAboutDialog();

private:
    QLabel       *m_versionLabel;
    QLabel       *m_versionNumLabel;
    QLabel       *m_copyrightLabel;
    QLabel       *m_copyrightInfoLabel;
    QPushButton  *m_okBtn;

};

#endif
