#include <QtWidgets>
#include "link.h"
#include "node.h"

Link::Link(Node *fromNode, Node *toNode)
{
    m_fromNode = fromNode;
    m_toNode = toNode;

    m_fromNode->addLink(this);
    m_toNode->addLink(this);

    this->setZValue(-1);
    //
    adjust();
    //
}

Link::~Link()
{
    m_fromNode->removeLink(this);
    m_toNode->removeLink(this);
}
//析构函数

Node *Link::getFromNode() const
{
    return m_fromNode;
}

Node *Link::getToNode() const
{
    return m_toNode;
}

void Link::adjust()
{
    m_fromPoint = m_fromNode->pos();
//位置
    m_toPoint = m_toNode->pos();

    prepareGeometryChange();
//使目标准备进行几何上的变化
}

QRectF Link::boundingRect() const
{
    return QRectF(m_fromPoint, QSizeF(m_toPoint.x() - m_fromPoint.x(), m_toPoint.y() - m_fromPoint.y())).normalized();
}
//矩形

void Link::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    painter->setPen(QPen(Qt::black, 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    QLineF line(m_fromPoint, m_toPoint);

    painter->drawLine(line);

}
//绘制
