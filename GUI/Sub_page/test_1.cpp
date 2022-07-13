#include "test_1.h"

void GaugePlane::paintEvent(QPaintEvent *) {
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制外边框
    drawBorderOut(&painter);
    //绘制内边框
    drawBorderIn(&painter);
    //绘制背景
    drawBg(&painter);
    //绘制姿势仪背景
    drawPlane(&painter);
    //绘制玻璃遮罩层
    drawGlass(&painter);
    //绘制刻度尺
    drawScale(&painter);
    //绘制线条
    drawLine(&painter);
    //绘制指针
    drawPointer(&painter);
    //绘制手柄
    drawHandle(&painter);
}

void GaugePlane::drawBorderOut(QPainter *painter) {
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0, -radius, 0, radius);
    borderGradient.setColorAt(0, borderOutColorStart);
    borderGradient.setColorAt(1, borderOutColorEnd);
    painter->setBrush(borderGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugePlane::drawBorderIn(QPainter *painter) {
    int radius = 93;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0, -radius, 0, radius);
    borderGradient.setColorAt(0, borderInColorStart);
    borderGradient.setColorAt(1, borderInColorEnd);
    painter->setBrush(borderGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugePlane::drawBg(QPainter *painter) {
    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0, -radius, 0, radius);
    bgColor.setAlpha(255);
    borderGradient.setColorAt(0, bgColor);
    bgColor.setAlpha(150);
    borderGradient.setColorAt(1, bgColor);
    painter->setBrush(borderGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}

void GaugePlane::drawPlane(QPainter *painter) {
    double radius = 90;
    painter->save();
    painter->rotate(degValue);
    painter->setPen(Qt::NoPen);
    painter->setBrush(planeColor);
    QRect rect(-radius, -radius, radius * 2, radius * 2);

#if 0
    painter->drawPie(rect, 0, -16 * 180);
#else
    float offset = -(rollValue * radius / 100);
    float startAngle = 180 + offset;
    float endAngle = offset;
    float span = endAngle + startAngle;
    painter->drawChord(rect, -16 * startAngle, 16 * span);
#endif
    painter->restore();
}
