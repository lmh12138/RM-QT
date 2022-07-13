#ifndef MYMENU_H
#define MTMENU_H

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

class MyMenu : public QMenuBar {
    Q_OBJECT
   public:
    explicit MyMenu(QWidget *parent = nullptr);
    void SetHeight(int height);
    int Height(void);

   private:
    QMenu *filemenu = new QMenu("文件");
    QMenu *editmenu = new QMenu("编辑");
    QAction *myac1 = new QAction();
    QAction *myac2 = new QAction();
    QAction *myac3 = new QAction();
    int menu_height = 30;

   signals:

   private slots:
    void pop1();
    void pop2();
    void pop3();
};

#endif  // MENU_H
