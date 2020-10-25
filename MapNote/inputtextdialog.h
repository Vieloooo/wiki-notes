#ifndef INPUTTEXTDIALOG_H
#define INPUTTEXTDIALOG_H

#include <QDialog>

class QLabel;
class QTextEdit;
//单行文本编辑控件
class InputTextDialog : public QDialog
{
    Q_OBJECT
//宏，发送信号时自动调用槽

public:
    explicit InputTextDialog(QDialog *parent = 0);
//显式调用
    ~InputTextDialog();
//析构函数

    void initInputTextDialog();
    void setInputTextDialogText(const QString &text);
    QString getInputTextDialogText();
//实现字符串处理功能

private:
    QLabel      *m_inputTextLabel;
    QTextEdit   *m_inputTextEdit;
    QPushButton *m_okBtn;
    QPushButton *m_cancelBtn;

};

#endif
