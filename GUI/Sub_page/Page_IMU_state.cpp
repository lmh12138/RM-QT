#include "Page_IMU_state.h"

Page_IMU_State::Page_IMU_State(QWidget *parent) : QWidget(parent) {
}

Page_IMU_State::Page_IMU_State(QWidget *parent, int x, int y) : QWidget(parent) {
    this->setParent(parent);
    this->setFixedSize(parent->width() - x, parent->height() - y);
    this->move(x, y);
}
