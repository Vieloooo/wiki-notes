#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
    Q_OBJECT
//宏，发送信号时自动调用槽

public:
    explicit Scene(qreal x, qreal y, qreal width, qreal height, QObject *parent = 0);
    //显示调用

    ~Scene();
    //析构函数

    QPointF getScenePos();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QPointF m_pos;
//在浮点精度上表征平面上的点

signals:
    void updateContextMenu();

};

#endif
