#ifndef MINDMAPDIALOG_H
#define MINDMAPDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QQueue>
#include"node.h"

typedef struct AdjacencyTable{
    QVector<int> son;
}AdjacencyTable;

typedef struct TreeNode{
    int x,y,num,father;
    QString text;
}treenode;

class QGraphicsView;
//视图窗口部件，使场景内容可视化
class Scene;
class QMenu;
class Node;
class Link;
class MindMapDialog : public QWidget
{
    Q_OBJECT
//宏，发送信号时自动调用槽

public:
    explicit MindMapDialog(QWidget *parent = 0,QString HtmlPath= "");
    //显示调用

    ~MindMapDialog();
    QString mapPath="C:/Users/vielo/Documents/QtProjects/MapNote/map";
    QString jsonPath="C:/Users/vielo/Documents/QtProjects/MapNote/Json";

    //析构函数
    void initMindMapDialog();
    void createActions();
    void initViewActions();

    Scene *getMindMapDialogScene();

    Node *getSelectedNode();
    void adjustNodes(Node *fromNode, int nodeSpace);
    void adjustNodesByLinkFrom(Link *linkFrom, int nodeY);

    void itemsMove();
    QString MindGraphSavePath = "C:/Users/vielo/Documents/QtProjects/MapNote/map";



private:
    QGraphicsView  *m_view;
    Scene          *m_scene;

    QMenu          *m_topMenu;
    QMenu          *m_secMenu;
    //菜单栏里面菜单，可以显示文本和图标，但是并不负责执行操作，类似label

    QAction        *m_actAdd;
    QAction        *m_actDel;
    QAction        *m_actCut;
    QAction        *m_actCopy;
    QAction        *m_actPaste;
    QAction        *m_actAddnode;
    QAction        *m_actInsertLink;
    QAction        *m_actInsertBgImage;
    QAction        *m_actProperty;
    QAction        *m_actAbout;
    QAction        *m_actSave;
    QAction        *m_actOpen;
    QAction        *m_actSend;
//  QAction类提供了抽象的用户界面action

    QQueue<Node *>  m_nodeQueue;
//定义一个node型队列
    int TreeNumber=0,TreeNodeNumber=0;

    QVector<AdjacencyTable> Adjacencytable;

    QVector<Node *> TreeNode;


public slots:
    void onSceneUpdateContextMenu();
    void onAdd();
    void onAddnode();
    void onDel();
    void onCut();
    void onCopy();
    void onPaste();
    void onInsertLink();
    void onInsertBgImage();
    void onProperty();
    void onAbout();
    void onSave();
    void onShow();
    void onOpen();
    void handlePosition(int position);
    void onSend();

signals:
    void toPosition(int posi);
};



#endif
