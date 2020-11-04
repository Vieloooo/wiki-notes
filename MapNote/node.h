#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>

class MindMapDialog;
class NodeInfoDialog;
class Scene;
class Link;
class Node : public QGraphicsItem
{
public:
    Node(MindMapDialog *mindMapDlg);
    ~Node();

    //基本存储信息
    int num,locatex,locatey,father,position=-1;
    QString CurrentText;
    //析构函数

    void setText(const QString &text);
    QString getText();
//字符串处理功能

    void insertLink(const QString &linkAddress);
    void insertBgImage(const QString &bgImagePath);

    void addLink(Link *link);
    void removeLink(Link *link);
    QList<Link *> getLinks();
//一种表示链表的模板类

    Link *getLinkFrom();
    QList<Link *> getLinksTo();
//一种表示链表的模板类

    void setBasePoint(QPointF basePoint);
    QPointF getBasePoint();
//浮点数精度表征平面上的点

    void showNodeInfo();
    void closeNodeInfo();

    QRectF outlineRect() const;
//使用坐标的浮点精度在平面中定义一个矩形

protected:
    QRectF boundingRect() const;
//使用坐标的浮点精度在平面中定义一个矩形

    QPainterPath shape() const;
//

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
//

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
//

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    MindMapDialog  *m_mindMapDlg;
    NodeInfoDialog *m_nodeInfoDlg;
    Scene          *m_nodeScene;

    QString         m_text;
    QString         m_bgImagePath;
    QList<Link *>   m_links;
    QPointF         m_basePoint;
//浮点数精度表征平面上的点

};

#endif
