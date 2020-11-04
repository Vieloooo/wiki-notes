#ifndef UABIRUANA_H
#define UABIRUANA_H

#include <QWidget>
#include <QJsonArray>
#include<QListWidgetItem>
namespace Ui {
class UabiruanA;
}

class UabiruanA : public QWidget
{
    Q_OBJECT

public:
    explicit UabiruanA(QWidget *parent = nullptr,QString jsonPath= "");
    ~UabiruanA();
    QString path;
     QJsonArray array ;

private slots:
     void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

signals:
     void writePosi(int position);

private:
    Ui::UabiruanA *ui;
};

#endif // UABIRUANA_H
