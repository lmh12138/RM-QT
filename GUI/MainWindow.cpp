#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent) {
    // 总界面设置部分
    this->setWindowTitle("南工骁鹰上位机调参软件");
    this->setFixedSize(screensize.width() / 3 * 2, screensize.height() / 3 * 2);
    this->move(screensize.width() / 6, screensize.height() / 6);

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

    /*  uart    ----->  mainwindow  */
    connect(uart, &UART::ReplyCOMCmd, this, &MainWindow::ReplyUartCmd);

    /*  uart    ----->  page_imu_state  */
    connect(uart, &UART::PAGE_IMU_STATE, page_imu_state, &Page_IMU_State::Refresh, Qt::QueuedConnection);

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
    uart->OpenCOM(com);
    uart->OpenUartThread();
}

void MainWindow::StopUart(void) {
    uart->CloseUartThread();
    uart->CloseCOM();
}

void MainWindow::InterfaceSwitch(QTreeWidgetItem *item, int column) {
    int item_count = treewidget->CheckTreeItem(item);
    QByteArray data;
    switch (item_count) {
        case 10:
            data = uart->SendCMD(10);
            uart->WriteData(data);
            page_imu_state->hide();
            break;
        case 11:
            data = uart->SendCMD(11);
            uart->WriteData(data);
            page_imu_state->show();
            break;
        case 12:
            data = uart->SendCMD(12);
            uart->WriteData(data);
            page_imu_state->hide();
            break;
        case 20:
            data = uart->SendCMD(20);
            uart->WriteData(data);
            page_imu_state->hide();
            break;
        case 30:
            data = uart->SendCMD(30);
            uart->WriteData(data);
            page_imu_state->hide();
            break;
        case 0:
            page_imu_state->hide();
            break;
        default:
            page_imu_state->hide();
            break;
    }
}

void MainWindow::ReplyUartCmd(void) {
    uart->WriteData(uart->SendReply());
}