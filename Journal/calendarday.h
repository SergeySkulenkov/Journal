#ifndef CALENDARDAY_H
#define CALENDARDAY_H

#include <QWidget>
#include <QDate>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
class QBoxLayout;
class QLabel;
QT_END_NAMESPACE

class CalendarDayItemWidget;

class CalendarDay : public QWidget
{
    Q_OBJECT
public:
    explicit CalendarDay(QWidget *parent = nullptr);
    void setDate(QDate date);
    void paintEvent(QPaintEvent *);
    bool isSelected();
    void setSelected(bool flag = true);
    bool isToday();
    void addCalendarDayItemWidget(CalendarDayItemWidget* cdWidget);

protected:
    void mousePressEvent(QMouseEvent *event);
signals:
    void changeCurrentDaySignal(CalendarDay *ptr);

private:
    QBoxLayout* hBox;
    QBoxLayout* treningsBox;
    QLabel*     dayLabel;

    QDate       date;
    bool        selected;
    bool        today;



};

#endif // CALENDARDAY_H
