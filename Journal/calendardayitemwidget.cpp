#include "calendardayitemwidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>

CalendarDayItemWidget::CalendarDayItemWidget( int type, QString timeStr, QString title, QWidget* parent)
{
    QHBoxLayout* box = new QHBoxLayout;
    setLayout(box);

    typeLabel = new QLabel;
    typeLabel->setFixedSize(20,20);
    setColorType(static_cast<ColorType>(type));
    box->addWidget(typeLabel);

    timeLabel = new QLabel;
    timeLabel->setFixedWidth(100);
    timeLabel->setText(timeStr);
    box->addWidget(timeLabel);

    titleLabel = new QLabel;
    titleLabel->setText(title);
    box->addWidget(titleLabel);

    setAutoFillBackground(true);
    setMouseTracking(true);


}

void CalendarDayItemWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug() << "doubleClick";
    emit doubleClickSignal(id);
}

void CalendarDayItemWidget::setColorType(ColorType type)
{
    QString bg;
    switch (type) {
    case Red:
        bg = "red";
        break;
    case Green:
        bg = "green";
        break;
    case Blue:
        bg = "blue";
        break;
    }
    typeLabel->setStyleSheet("background-color:"+bg);
}

void CalendarDayItemWidget::paintEvent(QPaintEvent *)
{

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
