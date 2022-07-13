#include "UartComboBox.h"

UartComboBox::UartComboBox(QWidget *parent) : QComboBox(parent) {
    // 扫描可用串口
    scanActivePort();
}

// 扫描可用串口
void UartComboBox::scanActivePort() {
    // 先清空列表项，防止多次刷新后重叠
    clear();

    // 串口端口号列表
    QStringList serialPortName;

    // 自动扫描当前可用串口，返回值追加到字符数组中
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        // 不携带有串口设备信息的文本
        serialPortName << info.portName();
    }

    if (serialPortName.count() == 0) {
        NoneCOM();
    }
    // 可用串口号，显示到串口选择下拉框中
    this->addItems(serialPortName);
}

// 重写鼠标点击事件
void UartComboBox::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // 扫描可用串口
        scanActivePort();

        // 弹出下拉框
        showPopup();

        // 设置固定值
    }
}