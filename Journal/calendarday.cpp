#include "calendarday.h"
#include <QBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QSpacerItem>
#include "stylehelper.h"
#include "calendardayitemwidget.h"
#include <QStyleOption>
#include <QPainter>


CalendarDay::CalendarDay(QWidget *parent)
    : QWidget{parent}
{
    hBox        = new QBoxLayout(QBoxLayout::LeftToRight);
    treningsBox = new QBoxLayout(QBoxLayout::TopToBottom);
    dayLabel    = new QLabel;

    this->setObjectName("mainWidget");
    dayLabel->setObjectName("dayLabel");


    setLayout(hBox);
    hBox->addWidget(dayLabel);
    hBox->addLayout(treningsBox);
    treningsBox->addSpacerItem(new QSpacerItem(1,0, QSizePolicy::Expanding,QSizePolicy::Fixed));

    dayLabel->setWordWrap(true);
    dayLabel->setFixedWidth(100);

    setStyleSheet(StyleHelper::getCalendarDayStyle());
    layout()->setContentsMargins(1,1,1,1);

    setMouseTracking(true);

}

void CalendarDay::setDate(QDate date)
{
    this->date  = date;
    today = false;
    QString dayNumberStr = QString::number(date.day());
    QString dayName      = date.toString("dddd");
    dayName[0]           = dayName[0].toUpper();
    QString html = "<p style=\""+StyleHelper::getCalendarDayNumberStyle()+"\">"
                   +dayNumberStr+
                   "<br><span style=\""+StyleHelper::getCalendarDayNameStyle()+"\">"+dayName+"</span></p>";
    dayLabel->setText(html);
    if(date==QDate::currentDate()){
        setStyleSheet(StyleHelper::getCalendarCurrentDayStyle());
        today = true;
    }
}

void CalendarDay::paintEvent(QPaintEvent *)
{

        QStyleOption opt;
        opt.init(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void CalendarDay::setSelected(bool flag)
{
    selected = flag;
    if(selected && today){
        setStyleSheet(StyleHelper::getCalendarCurrentSelectedDayStyle());
    }else if(selected && !today){
        setStyleSheet(StyleHelper::getCalendarDaySelectedStyle());
    }else if(!selected && today){
        setStyleSheet(StyleHelper::getCalendarCurrentDayStyle());
    }else{
        setStyleSheet(StyleHelper::getCalendarDayStyle());
    }
}

bool CalendarDay::isToday()
{
    return today;
}

void CalendarDay::addCalendarDayItemWidget(CalendarDayItemWidget *cdWidget)
{
    treningsBox->addWidget(cdWidget);
}


void CalendarDay::mousePressEvent(QMouseEvent *event)
{
    changeCurrentDaySignal(this);
}

bool CalendarDay::isSelected(){
    return selected;
}
