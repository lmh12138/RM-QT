#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>

class MyTreeWidget : public QTreeWidget {
    Q_OBJECT
   public:
    explicit MyTreeWidget(QWidget *parent);
    explicit MyTreeWidget(QWidget *parent, int menutoolbar_height);
    int CheckTreeItem(QTreeWidgetItem *item);

   private:
    int tree_width = 100;
    int ident_height = 10;
    QTreeWidgetItem *item1 = new QTreeWidgetItem(this, QStringList("陀螺仪"));
    QTreeWidgetItem *item11 = new QTreeWidgetItem(item1, QStringList("状态"));
    QTreeWidgetItem *item12 = new QTreeWidgetItem(item1, QStringList("参数"));
    QTreeWidgetItem *item2 = new QTreeWidgetItem(this, QStringList("电机"));
    QTreeWidgetItem *item3 = new QTreeWidgetItem(this, QStringList("蜂鸣器"));
};

#endif  // MYTREEWIDGET_H
