#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QRect>
#include <QWidget>

#include "MyMenu.h"
#include "MyToolBar.h"
#include "MyTreeWidget.h"
#include "Page_IMU_state.h"
#include "Uart.h"
class MainWindow : public QWidget {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void OpenUart(const QString &com);
    void StopUart(void);

    void InterfaceSwitch(QTreeWidgetItem *item, int column);

   private:
    MyMenu *menu;
    MyToolBar *toolbar;
    MyTreeWidget *treewidget;
    UART *uart;
    QRect screensize = QApplication::desktop()->screenGeometry();

    Page_IMU_State *page_imu_state;

   private slots:
};

#endif  // WINDOW_H
