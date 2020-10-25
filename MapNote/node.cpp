#include <QtWidgets>
#include "node.h"
#include "link.h"
#include "mindmapdialog.h"
#include "inputtextdialog.h"
#include "nodeinfodialog.h"
#include "scene.h"

Node::Node(MindMapDialog *mindMapDlg)
{
    this->setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
    this->setAcceptHoverEvents(true);

    m_mindMapDlg = mindMapDlg;
    m_nodeScene = m_mindMapDlg->getMindMapDialogScene();
}

Node::~Node()
{
    foreach (Link *link, m_links)
        delete link;
}
//析构函数

void Node::setText(const QString &text)
{
    m_text = text;

    prepareGeometryChange();
}

QString Node::getText()
{
    return m_text;
}

void Node::insertLink(const QString &linkAddress)
{
    m_text += linkAddress;

    prepareGeometryChange();
}

void Node::insertBgImage(const QString &bgImagePath)
{
    m_bgImagePath = bgImagePath;

    prepareGeometryChange();
}

void Node::addLink(Link *link)
{
    m_links.append(link);
}

void Node::removeLink(Link *link)
{
    m_links.removeOne(link);
}

QList<Link *> Node::getLinks()
{
    return m_links;
}

Link *Node::getLinkFrom()
{
    for (int i = 0; i < m_links.size(); i++) {
        Link *link = m_links.at(i);
        if (link) {
            Node *fromNode = link->getFromNode();
            if (fromNode && fromNode != this) {
                return link;
            }
        }
    }

    return 0;
}

QList<Link *> Node::getLinksTo()
{
    QList<Link *> linkList;
    for (int i = 0; i < m_links.size(); i++) {
        Link *link = m_links.at(i);
        if (link) {
            Node *toNode = link->getToNode();
            if (toNode && toNode != this) {
                linkList << link;
            }
        }
    }

    return linkList;
}

void Node::setBasePoint(QPointF basePoint)
{
    m_basePoint = basePoint;
}

QPointF Node::getBasePoint()
{
    return m_basePoint;
}

void Node::showNodeInfo()
{
    QRectF rect = outlineRect();
    int rectW = rect.width();
    int rectH = rect.height();

    int nodeX = this->x();
    int nodeY = this->y();

    int moveX = nodeX - rectW / 2.0;
    int moveY = nodeY + rectH / 2.0 + 5;

    m_nodeInfoDlg = new NodeInfoDialog(this);
    m_nodeScene->addWidget(m_nodeInfoDlg);

    m_nodeInfoDlg->move(moveX, moveY);
    m_nodeInfoDlg->show();
}

void Node::closeNodeInfo()
{
    if (m_nodeInfoDlg && m_nodeInfoDlg->isVisible()) {
        m_nodeInfoDlg->deleteLater();
        m_nodeInfoDlg = NULL;
    }
}

QRectF Node::outlineRect() const
{
    QFontMetricsF metrics = (QFontMetricsF)qApp->font();
    QRectF rect = metrics.boundingRect(m_text);
    rect.adjust(-10, -10, +20, +10);
    rect.translate(-rect.center());
    return rect;
}

QRectF Node::boundingRect() const
{
    return outlineRect().adjusted(-1, -1, +1, +1);
}

QPainterPath Node::shape() const
{
    QRectF rect = outlineRect();

    QPainterPath path;
    path.addRect(rect);

    return path;
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged) {
        if (!getLinkFrom()) {
            m_mindMapDlg->itemsMove();
        }
        else {
            setPos(m_basePoint.x(), m_basePoint.y());
        }
    }
    else if (change == ItemSelectedHasChanged) {
        m_mindMapDlg->onSceneUpdateContextMenu();
    }

    return QGraphicsItem::itemChange(change, value);
}

void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    InputTextDialog *inputTextDlg = new InputTextDialog(static_cast<QDialog*>(event->widget()));
    inputTextDlg->setInputTextDialogText(m_text);
    if (inputTextDlg->exec() == QDialog::Accepted) {
        QString text = inputTextDlg->getInputTextDialogText();
        if (!text.isEmpty()) {
            setText(text);
            CurrentText = text;
        }
    }
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    closeNodeInfo();

    update(boundingRect());
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!getLinkFrom()) {
        setBasePoint(QPointF(this->x(), this->y()));
    }
    locatex = x();
    locatey = y();
    update(boundingRect());
    QGraphicsItem::mouseMoveEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    showNodeInfo();

    if (!getLinkFrom()) {
        setBasePoint(QPointF(this->x(), this->y()));
    }

    update(boundingRect());
    QGraphicsItem::mouseReleaseEvent(event);
}

void Node::hoverEnterEvent(QGraphicsSceneHoverEvent */*event*/)
{
    showNodeInfo();

    this->setCursor(Qt::PointingHandCursor);
}

void Node::hoverLeaveEvent(QGraphicsSceneHoverEvent */*event*/)
{
    closeNodeInfo();

    this->setCursor(Qt::ArrowCursor);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget */*widget*/)
{
    if (option->state & QStyle::State_Selected) {
        painter->setPen(QPen(Qt::red, 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
    else {
        painter->setPen(QPen(Qt::black, 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
    painter->setBrush(Qt::white);

    QRectF rect = outlineRect();
    painter->drawRect(rect);

    if (!m_bgImagePath.isEmpty())
        painter->drawImage(rect, QImage(m_bgImagePath));

    painter->drawText(rect, Qt::AlignCenter, m_text);
}
