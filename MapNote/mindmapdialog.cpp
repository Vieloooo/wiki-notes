#include <QtWidgets>
#include "mindmapdialog.h"
#include "node.h"
#include "link.h"
#include "scene.h"
#include "insertlinkdialog.h"
#include "nodeinfodialog.h"
#include "aboutdialog.h"


MindMapDialog::MindMapDialog(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::Window);
    this->resize(1268, 744);
//设置窗口大小
    initMindMapDialog();
    createActions();

    initViewActions();
    onShow();
}

MindMapDialog::~MindMapDialog()
{

}
//析构函数

void MindMapDialog::initMindMapDialog()
{
    m_scene = new Scene(0, 0, 50000, 60000);
    connect(m_scene, SIGNAL(updateContextMenu()), this, SLOT(onSceneUpdateContextMenu()));
    m_view = new QGraphicsView(this);
    m_view->setScene(m_scene);
    m_view->setDragMode(QGraphicsView::RubberBandDrag);
    m_view->setContextMenuPolicy(Qt::ActionsContextMenu);

    /**Node *node = new Node(this);
    node->setText("Node");
    node->setPos(m_scene->width() / 2.0, m_scene->height() / 2.0);
    m_scene->addItem(node);*/


    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(m_view);
    this->setLayout(hLayout);
}
//初始时思维导图的设置

void MindMapDialog::createActions()
{
    m_topMenu = new QMenu(this);

    m_actAdd = new QAction("Add", this);
    m_actAdd->setShortcut(tr("Ctrl+N"));
    connect(m_actAdd, SIGNAL(triggered(bool)), this, SLOT(onAdd()));
    m_topMenu->addAction(m_actAdd);

    m_actAddnode = new QAction("Addnode", this);
    m_actAddnode->setShortcut(tr("Ctrl+Q"));
    connect(m_actAddnode, SIGNAL(triggered(bool)), this, SLOT(onAddnode()));
    m_topMenu->addAction(m_actAddnode);

    m_actDel = new QAction("Delete", this);
    m_actDel->setShortcut(tr("Del"));
    connect(m_actDel, SIGNAL(triggered(bool)), this, SLOT(onDel()));
    m_topMenu->addAction(m_actDel);

    m_topMenu->addSeparator();

    m_actCut = new QAction("Cut", this);
    m_actCut->setShortcut(tr("Ctrl+X"));
    connect(m_actCut, SIGNAL(triggered(bool)), this, SLOT(onCut()));
    m_topMenu->addAction(m_actCut);

    m_actCopy = new QAction("Copy", this);
    m_actCopy->setShortcut(tr("Ctrl+C"));
    connect(m_actCopy, SIGNAL(triggered(bool)), this, SLOT(onCopy()));
    m_topMenu->addAction(m_actCopy);

    m_actPaste = new QAction("Paste", this);
    m_actPaste->setShortcut(tr("Ctrl+V"));
    connect(m_actPaste, SIGNAL(triggered(bool)), this, SLOT(onPaste()));
    m_topMenu->addAction(m_actPaste);

    m_topMenu->addSeparator();

    m_actInsertLink = new QAction("Insert Link", this);
    m_actInsertLink->setShortcut(tr("Ctrl+K"));
    connect(m_actInsertLink, SIGNAL(triggered(bool)), this, SLOT(onInsertLink()));
    m_topMenu->addAction(m_actInsertLink);

    m_actInsertBgImage = new QAction("Insert Background Image", this);
    connect(m_actInsertBgImage, SIGNAL(triggered(bool)), this, SLOT(onInsertBgImage()));
    m_topMenu->addAction(m_actInsertBgImage);

    m_topMenu->addSeparator();

    m_actProperty = new QAction("Property", this);
    connect(m_actProperty, SIGNAL(triggered(bool)), this, SLOT(onProperty()));
    m_topMenu->addAction(m_actProperty);

    m_topMenu->addSeparator();

    m_actAbout = new QAction("About", this);
    m_actAbout->setShortcut(tr("F1"));
    connect(m_actAbout, SIGNAL(triggered(bool)), this, SLOT(onAbout()));
    m_topMenu->addAction(m_actAbout);


    m_topMenu->addSeparator();

    m_actSave = new QAction ("Save",this);
    connect(m_actSave, SIGNAL(triggered(bool)),this,SLOT(onSave()));
    m_topMenu->addAction(m_actSave);

    m_topMenu->addSeparator();


}
//鼠标右键事件的定义


void MindMapDialog::initViewActions()
{
    QList<QAction *> acts = m_topMenu->actions();
    for (int i = 0; i < acts.count(); i++) {
        QAction *act = acts.at(i);
        if (act) {
            m_view->addAction(act);

        }
    }
}

Scene *MindMapDialog::getMindMapDialogScene()
{
    return m_scene;
}

Node *MindMapDialog::getSelectedNode()
{
    QList<QGraphicsItem *> items = m_scene->selectedItems();
    if (items.count() == 1) {
        return dynamic_cast<Node *>(items.first());
    }
    else {
        return 0;
    }
}
//

void MindMapDialog::adjustNodes(Node *fromNode, int nodeSpace)
{
    if (!fromNode)
        return;

    QStack<Node *> nodeStack;
    nodeStack.push(fromNode);
    while (!nodeStack.isEmpty()) {
        Node *topNode = nodeStack.top();
        nodeStack.pop();

        QList<Link *> linksTo = topNode->getLinksTo();
        for (int i = 0; i < linksTo.size(); i++) {
            Link *link = linksTo.at(i);
            if (link) {
                Node *toNode = link->getToNode();
                if (toNode) {
                    if (!toNode->getLinksTo().isEmpty()) {
                        nodeStack.push(toNode);
                    }
                    toNode->setBasePoint(QPointF(toNode->x(), toNode->y() + nodeSpace));
                    toNode->setPos(toNode->getBasePoint().x(), toNode->getBasePoint().y());
                    link->adjust();
                }
            }
        }
    }
}
//

void MindMapDialog::adjustNodesByLinkFrom(Link *linkFrom, int nodeY)
{
    if (linkFrom) {
        Node *fromNode = linkFrom->getFromNode();
        if (fromNode) {
            QList<Link *> linksTo = fromNode->getLinksTo();
            for (int i = 0; i < linksTo.size(); i++) {
                Link *link = linksTo.at(i);
                if (link) {
                    Node *toNode = link->getToNode();
                    if (toNode) {
                        if (toNode->y() < nodeY) {
                            toNode->setBasePoint(QPointF(toNode->x(), toNode->y() + 50));
                            toNode->setPos(toNode->getBasePoint());

                            adjustNodes(toNode, +50);
                        }
                        else {
                            toNode->setBasePoint(QPointF(toNode->x(), toNode->y() - 50));
                            toNode->setPos(toNode->getBasePoint());

                            adjustNodes(toNode, -50);
                        }
                    }
                    link->adjust();
                }
            }
        }
    }
}
//

void MindMapDialog::itemsMove()
{
    Node *selectedNode = getSelectedNode();
    if (selectedNode) {
        if (!selectedNode->getLinksTo().isEmpty()) {
            int moveX = selectedNode->x() - selectedNode->getBasePoint().x();
            int moveY = selectedNode->y() - selectedNode->getBasePoint().y();

            QStack<Node *> nodeStack;
            nodeStack.push(selectedNode);
            while (!nodeStack.isEmpty()) {
                Node *node = nodeStack.top();
                nodeStack.pop();

                if (node) {
                    QList<Link *> linksTo = node->getLinksTo();
                    for (int i = 0; i < linksTo.size(); i++) {
                        Link *link = linksTo.at(i);
                        if (link) {
                            Node *toNode = link->getToNode();
                            if (toNode) {
                                if (!toNode->getLinksTo().isEmpty()) {
                                    nodeStack.push(toNode);
                                }

                                toNode->setBasePoint(QPointF(toNode->x() + moveX, toNode->y() + moveY));
                                toNode->setPos(toNode->getBasePoint().x(), toNode->getBasePoint().y());
                                link->adjust();
                            }
                        }
                    }
                }
            }
        }
    }
}

void MindMapDialog::onSceneUpdateContextMenu()
{
    bool hasSelection = !m_scene->selectedItems().isEmpty();
    bool isItemsEmpty = m_scene->items().isEmpty();
    bool isNode = (getSelectedNode() != 0);
    bool isQueueEmpty = m_nodeQueue.isEmpty();

    m_actAdd->setEnabled(isNode || isItemsEmpty);
    m_actAddnode->setEnabled(1);
    m_actDel->setEnabled(hasSelection);

    m_actCut->setEnabled(isNode);
    m_actCopy->setEnabled(isNode);
    m_actPaste->setEnabled(!isQueueEmpty);

    m_actInsertLink->setEnabled(isNode);
    m_actInsertBgImage->setEnabled(isNode);

    m_actProperty->setEnabled(isNode);
}

void MindMapDialog::onAdd()
{
    Node *node = new Node(this);

    QList<QGraphicsItem *> items = m_scene->items();
    if (items.isEmpty()) {
        node->setPos(m_scene->width() / 2.0, m_scene->height() / 2.0);
        node->setBasePoint(node->pos());
        m_scene->addItem(node);

        node->num=TreeNodeNumber;
        node->locatex = m_scene->width() / 2.0;
        node->locatey = m_scene->height() / 2.0;
        node->father = TreeNodeNumber;
        node->setToolTip(QString::number(TreeNodeNumber,10));
        TreeNode.push_back(node);


        AdjacencyTable AT;
        Adjacencytable.push_back(AT);

        TreeNumber++;
        TreeNodeNumber++;




    }
    else {
        Node *fromNode = getSelectedNode();
        if (fromNode) {
            QList<Link *> linksTo = fromNode->getLinksTo();
            if (linksTo.isEmpty()) {
                node->setPos(fromNode->x() + 140, fromNode->y());
                node->setBasePoint(node->pos());
                m_scene->addItem(node);

                node->setToolTip(QString::number(TreeNodeNumber,10));
                node->num=TreeNodeNumber;
                node->locatex = -1;
                node->locatey = -1;
                node->father = fromNode->num;
                TreeNode.push_back(node);


                AdjacencyTable AT;
                Adjacencytable.push_back(AT);
                Adjacencytable[fromNode->num].son.push_back(TreeNodeNumber);
                TreeNodeNumber++;

                Link *newLink = new Link(fromNode, node);
                m_scene->addItem(newLink);

            }
            else {
                Link *link = linksTo.last();
                if (link) {
                    Node *toNode = link->getToNode();
                    if (toNode) {
                        node->setPos(toNode->x(), toNode->y() - 100);
                        node->setBasePoint(node->pos());
                        m_scene->addItem(node);

                        node->setToolTip(QString::number(TreeNodeNumber,10));
                        node->num=TreeNodeNumber;
                        node->locatex = -1;
                        node->locatey = -1;
                        node->father = fromNode->num;
                        TreeNode.push_back(node);

                        AdjacencyTable AT;
                        Adjacencytable.push_back(AT);
                        Adjacencytable[fromNode->num].son.push_back(TreeNodeNumber);
                        TreeNodeNumber++;


                        Link *newLink = new Link(fromNode, node);
                        m_scene->addItem(newLink);

                        //调整布局
                        adjustNodes(fromNode, +50);
                    }
                }
            }
      }
      else {
         delete node;
         node = NULL;
      }
  }
}

void MindMapDialog::onAddnode()
{
    Node *node = new Node(this);

    QList<QGraphicsItem *> items = m_scene->items();


        node->setPos(m_scene->width() / 2.0, m_scene->height() / 2.0);
        node->setBasePoint(node->pos());
        m_scene->addItem(node);

        node->num=TreeNodeNumber;
        node->locatex = m_scene->width() / 2.0;
        node->locatey = m_scene->height() / 2.0;
        node->father = TreeNodeNumber;
        node->setToolTip(QString::number(TreeNodeNumber,10));
        TreeNode.push_back(node);

        AdjacencyTable AT;
        Adjacencytable.push_back(AT);

        TreeNumber++;
        TreeNodeNumber++;

}
QVector<int> sort(QVector<int> &ivec,int plug)
{
      const int  COUNT = ivec.size();
      for(int i=1; i<COUNT; i++)
      {
            for(int j = 0; j<COUNT-i; ++j)
            {
                if(plug){
                    if(ivec[j]<ivec[j+1])
                       {
                            int temp = 0;
                            temp = ivec[j];
                            ivec[j] = ivec[j+1];
                            ivec[j+1] = temp;
                        }

                }else{
                    if(ivec[j]>ivec[j+1])
                       {
                            int temp = 0;
                            temp = ivec[j];
                            ivec[j] = ivec[j+1];
                            ivec[j+1] = temp;
                        }
                }

             }
        }
      return ivec;
}
void MindMapDialog::onDel()
{
    QStack<Node *> nodeStack;
    QList<QGraphicsItem *> items = m_scene->selectedItems();

    Node *A = getSelectedNode();
    QQueue<int> re_number;
    QVector<int> NumberThatDeleted;

    re_number.push_back(A->num);

    while(!re_number.isEmpty()){
        int k = re_number.first();
        NumberThatDeleted.push_front(k);
        re_number.pop_front();
        for(QVector<int>::iterator iter = Adjacencytable[k].son.begin();iter != Adjacencytable[k].son.end(); ++iter){
            re_number.push_back(*iter);
        }
    }
    int TotalDelete = NumberThatDeleted.size();



    NumberThatDeleted = sort(NumberThatDeleted,1);//从大到小
   for(int i = 0 ; i < TotalDelete ; i++ ){
        for(QVector<int>::iterator ite = Adjacencytable[TreeNode[NumberThatDeleted[i]]->num].son.begin(); ite!=Adjacencytable[TreeNode[NumberThatDeleted[i]]->num].son.end();ite++){
            if(*ite == NumberThatDeleted[i]) Adjacencytable[TreeNode[NumberThatDeleted[i]]->num].son.erase(ite);
        }

        QVector<AdjacencyTable>::iterator it = Adjacencytable.begin()+NumberThatDeleted[i];      //更新邻接表的表头
        QVector<Node *>::iterator iter = TreeNode.begin()+NumberThatDeleted[i];                  //更新存储节点的容器
        TreeNode.erase(iter);
        Adjacencytable.erase(it);
    }


    for(int j=0 ; j<TreeNode.size() ; ++j){   //更新节点类内的编号
        TreeNode[j]->num = j;
        TreeNode[j]->setToolTip(QString::number(j,10));
    }

    NumberThatDeleted = sort(NumberThatDeleted,0);//从小到大

    int p[100];
    memset(p,0,sizeof (p));
    int count=0;
    for(int k=0;k<TreeNodeNumber;++k){
        p[k] = count;
        if(count != TotalDelete && k == NumberThatDeleted[count]) {
            count++;
        }
    }
    TreeNodeNumber -= count;

    for(int i1 = 0; i1<Adjacencytable.size() ;i1++){
       for(int i2 = 0; i2<Adjacencytable[i1].son.size() ; i2++){
           Adjacencytable[i1].son[i2] -= p[Adjacencytable[i1].son[i2]];
           TreeNode[ Adjacencytable[i1].son[i2]]->father = i1;
       }
    }







    while (items.size() > 0) {
        Node *fromNode = dynamic_cast<Node *>(items.at(0));
        if (fromNode) {
            fromNode->closeNodeInfo();
            nodeStack.push(fromNode);
            while (!nodeStack.isEmpty()) {
                Node *node = nodeStack.top();
                nodeStack.pop();
                Link *parentLink = node->getLinkFrom();
                int nodeY = node->y();
                if (node) {
                    QList<Link *> linksTo = node->getLinksTo();
                    for (int i = 0; i < linksTo.size(); i++) {
                        Link *link = linksTo.at(i);
                        if (link) {
                            Node *toNode = link->getToNode();
                            if (toNode) {
                                if (toNode->getLinksTo().isEmpty()) {
                                    items.removeOne(toNode);
                                    delete toNode;
                                }
                                else {
                                    nodeStack.push(toNode);
                                }
                            }
                        }
                    }
                    items.removeOne(node);
                    delete node;

                    adjustNodesByLinkFrom(parentLink, nodeY);
                }
            }
        }
    }

}

void MindMapDialog::onCut()
{
    m_nodeQueue.clear();
    QStack<Node *> nodeStack;
    QStack<Node *> newNodeStack;

    Node *selectedNode = getSelectedNode();
    if (selectedNode) {
        nodeStack.push(selectedNode);

        Node *newNode = new Node(this);
        newNode->setText(selectedNode->getText());
        m_nodeQueue.push_back(newNode);
        newNodeStack.push(newNode);

        while (!nodeStack.isEmpty()) {
            Node *fromNode = nodeStack.top();
            nodeStack.pop();
            Link *parentLink = fromNode->getLinkFrom();
            int nodeX = fromNode->x();

            Node *newFromNode = newNodeStack.top();
            newNodeStack.pop();

            if (fromNode) {
                QList<Link *> linksTo = fromNode->getLinksTo();
                for (int i = 0; i < linksTo.size(); i++) {
                    Link *link = linksTo.at(i);
                    if (link) {
                        Node *toNode = link->getToNode();
                        if (toNode) {
                            Node *newNode = new Node(this);
                            newNode->setText(toNode->getText());
                            link = new Link(newFromNode, newNode);
                            m_nodeQueue.push_back(newNode);

                            if (!toNode->getLinksTo().isEmpty()) {
                                nodeStack.push(toNode);
                                newNodeStack.push(newNode);
                            }
                            else {
                                delete toNode;
                            }
                        }
                    }
                }
                delete fromNode;

                adjustNodesByLinkFrom(parentLink, nodeX);
            }
        }
    }
}

void MindMapDialog::onCopy()
{
    m_nodeQueue.clear();
    QStack<Node *> nodeStack;

    Node *selectedNode = getSelectedNode();
    if (selectedNode) {
        m_nodeQueue.push_back(selectedNode);
        nodeStack.push(selectedNode);

        while (!nodeStack.isEmpty()) {
            Node *fromNode = nodeStack.top();
            nodeStack.pop();
            if (fromNode) {
                QList<Link *> linksTo = fromNode->getLinksTo();
                for (int i = 0; i < linksTo.size(); i++) {
                    Link *linkTo = linksTo.at(i);
                    if (linkTo) {
                        Node *toNode = linkTo->getToNode();
                        if (toNode) {
                            if (!toNode->getLinksTo().isEmpty()) {
                                nodeStack.push(toNode);
                            }
                            m_nodeQueue.push_back(toNode);
                        }
                    }
                }
            }
        }
    }
}

void MindMapDialog::onPaste()
{
    QStack<Node *> nodeStack;
    QStack<Node *> newNodeStack;
    if (!m_nodeQueue.isEmpty()) {
        Node *topNode = m_nodeQueue.front();
        m_nodeQueue.pop_front();

        if (topNode) {
            Node *node = new Node(this);
            node->setText(topNode->getText());
            node->setPos(m_scene->getScenePos().x(), m_scene->getScenePos().y());
            node->setBasePoint(node->pos());
            m_scene->addItem(node);

            nodeStack.push(topNode);
            newNodeStack.push(node);
        }

        while (!nodeStack.isEmpty()) {
            Node *fromNode = nodeStack.top();
            nodeStack.pop();

            Node *parentNode = newNodeStack.top();
            newNodeStack.pop();

            QList<Link *> linksTo = fromNode->getLinksTo();
            for (int i = 0; i < linksTo.size(); i++) {
                Node *toNode = m_nodeQueue.front();
                m_nodeQueue.pop_front();

                if (toNode) {
                    QList<Link *> parentLinksTo = parentNode->getLinksTo();
                    Node *node = new Node(this);
                    node->setText(toNode->getText());

                    if (parentLinksTo.isEmpty()) {
                        node->setPos(parentNode->x() + 140, parentNode->y());
                        node->setBasePoint(node->pos());
                        m_scene->addItem(node);

                        Link *newLink = new Link(parentNode, node);
                        m_scene->addItem(newLink);
                    }
                    else {
                        Link *link = parentLinksTo.last();
                        if (link) {
                            Node *parentToNode = link->getToNode();
                            if (parentToNode) {
                                node->setPos(parentToNode->x(), parentToNode->y() - 100);
                                node->setBasePoint(node->pos());
                                m_scene->addItem(node);

                                Link *newLink = new Link(parentNode, node);
                                m_scene->addItem(newLink);

                                //调整布局
                                adjustNodes(parentNode, +50);
                            }
                        }
                    }

                    if (!toNode->getLinksTo().isEmpty()) {
                        nodeStack.push(toNode);
                        newNodeStack.push(node);
                    }
                }
            }
        }
    }
}

void MindMapDialog::onInsertLink()
{
    Node *selectedNode = getSelectedNode();
    if (selectedNode) {
        InsertLinkDialog *insertLinkDlg = new InsertLinkDialog(this);
        if (insertLinkDlg->exec() == QDialog::Accepted) {
            QString linkAddress = insertLinkDlg->getLinkAddress();

            linkAddress = " file://" + linkAddress;
            selectedNode->insertLink(linkAddress);
        }
    }
}

void MindMapDialog::onInsertBgImage()
{
    Node *selectedNode = getSelectedNode();
    if (selectedNode) {
        QString bgImagePath = QFileDialog::getOpenFileName(this, "Insert Background Image", QApplication::applicationDirPath(), "PNG(*.png);;JPEG(*.jpg *.jpeg);;BMP(*.bmp)");
        if (bgImagePath.isEmpty())
            return;

        selectedNode->insertBgImage(bgImagePath);
    }
}

void MindMapDialog::onProperty()
{
    Node *selectedNode = getSelectedNode();
    if (selectedNode) {
        NodeInfoDialog *nodeInfoDlg = new NodeInfoDialog(selectedNode, this);
        nodeInfoDlg->exec();
    }
}

void MindMapDialog::onAbout()
{
    AboutDialog *aboutDlg = new AboutDialog(this);
    aboutDlg->exec();
}

void MindMapDialog::onSave(){

    QString str;
    QFile f(MindGraphSavePath);
    f.open(QIODevice::WriteOnly | QIODevice::Text ); //以只写的方式
    QTextStream txtOutput(&f);
    for(int i=0;i<TreeNode.size();i++){  // num x y father string
        str = QString::number(TreeNode[i]->num,10)+" "+QString::number(TreeNode[i]->locatex,10)+" "+QString::number(TreeNode[i]->locatey,10)+" "+QString::number(TreeNode[i]->father,10)+" "+TreeNode[i]->CurrentText;
        txtOutput << str <<"\n";
    }
    f.close();

}

void MindMapDialog::onShow(){

    QString context;
    QFile f(MindGraphSavePath);
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream txtInput(&f);
    while(!txtInput.atEnd())
    {
        context = txtInput.readLine();
        QStringList strlist = context.split(" ");
        int num = strlist[0].toInt();
        int lx = strlist[1].toInt();
        int ly = strlist[2].toInt();
        int father = strlist[3].toInt();
        QString content;
        if(strlist.size() == 5) content = strlist[4];

        if(father == num){
            Node *node = new Node(this);
            node->setPos(lx,ly);
            node->setBasePoint(node->pos());
            m_scene->addItem(node);

            node->num=num;
            node->locatex = lx;
            node->locatey = ly;
            node->father = father;
            node->CurrentText =content;
            node->setText(content);
            node->setToolTip(QString::number(num,10));
            TreeNode.push_back(node);


            AdjacencyTable AT;
            Adjacencytable.push_back(AT);

            TreeNumber++;
            TreeNodeNumber++;

        }else{
            Node *fromNode = TreeNode[father];
            Node *node = new Node(this);
            if (fromNode) {
                QList<Link *> linksTo = fromNode->getLinksTo();
                if (linksTo.isEmpty()) {
                    node->setPos(fromNode->x() + 140, fromNode->y());
                    node->setBasePoint(node->pos());
                    m_scene->addItem(node);

                    node->setToolTip(QString::number(num,10));
                    node->num=num;
                    node->locatex = -1;
                    node->locatey = -1;
                    node->father = father;
                    node->CurrentText =content;
                    node->setText(content);
                    TreeNode.push_back(node);


                    AdjacencyTable AT;
                    Adjacencytable.push_back(AT);
                    Adjacencytable[father].son.push_back(num);
                    TreeNodeNumber++;

                    Link *newLink = new Link(fromNode, node);
                    m_scene->addItem(newLink);

                }
                else {
                    Link *link = linksTo.last();
                    if (link) {
                        Node *toNode = link->getToNode();
                        if (toNode) {
                            node->setPos(toNode->x(), toNode->y() - 100);
                            node->setBasePoint(node->pos());
                            m_scene->addItem(node);

                            node->setToolTip(QString::number(num,10));
                            node->num=num;
                            node->locatex = -1;
                            node->locatey = -1;
                            node->father = father;
                            node->CurrentText =content;
                            node->setText(content);
                            TreeNode.push_back(node);

                            AdjacencyTable AT;
                            Adjacencytable.push_back(AT);
                            Adjacencytable[father].son.push_back(num);
                            TreeNodeNumber++;


                            Link *newLink = new Link(fromNode, node);
                            m_scene->addItem(newLink);

                            //调整布局
                            adjustNodes(fromNode, +50);
                        }
                    }
                }
           }



       }
    }



}
