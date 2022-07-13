#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent) {
    // 总界面设置部分
    this->setWindowTitle("南工骁鹰上位机调参软件");
    this->resize(screensize.width() / 3 * 2, screensize.height() / 3 * 2);
    this->move(screensize.width() / 6, screensize.height() / 6);
    this->setMinimumSize(500, 500);
    this->setMaximumSize(3000, 3000);

    // 菜单栏
    menu = new MyMenu(this);

    // 工具栏
    toolbar = new MyToolBar(this, menu->height());

    // 页面导航部分
    treewidget = new MyTreeWidget(this, menu->height() + toolbar->height());

    // 串口部分
    uart = new UART;

    // IMU子窗口
    // 状态窗口
    page_imu_state = new Page_IMU_State(this, treewidget->width(), treewidget->y());

    // 信号连接部分
    /*  uart    ----->  toolbar */
    connect(uart, &UART::OpenCOMSuccess, toolbar, &MyToolBar::OpenCOMSuccess);
    connect(uart, &UART::OpenCOMFailed, toolbar, &MyToolBar::OpenCOMFailed);
    connect(uart, &UART::CloseCOMSuccess, toolbar, &MyToolBar::CloseCOMSuccess);

    /*  toolbar ----->  mainwindow  */
    connect(toolbar, &MyToolBar::ToOpenCOM_SGN, this, &MainWindow::OpenUart);
    connect(toolbar, &MyToolBar::ToCloseCOM_SGN, this, &MainWindow::StopUart);

    /*  treewidegt  ----->  mainwindow  */
    connect(treewidget, &MyTreeWidget::itemClicked, this, &MainWindow::InterfaceSwitch);

    // Debug部分
}

MainWindow::~MainWindow(void) {
}

void MainWindow::OpenUart(const QString &com) {
    uart->OpenUartThread();
    uart->OpenCOM(com);
}

void MainWindow::StopUart(void) {
    uart->CloseUartThread();
    uart->CloseCOM();
}

void MainWindow::InterfaceSwitch(QTreeWidgetItem *item, int column) {
    int item_count = treewidget->CheckTreeItem(item);
    qDebug() << "item: " << item_count << "column: " << column << endl;
}