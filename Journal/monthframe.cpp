#include "monthframe.h"
#include "ui_monthframe.h"
#include <QDate>
#include <QAbstractItemView>
#include <QStyledItemDelegate>
#include "stylehelper.h"

MonthFrame::MonthFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::MonthFrame)
{
    ui->setupUi(this);
    setup();
}

MonthFrame::~MonthFrame()
{
    delete ui;
}

int MonthFrame::getMonth()
{
    return ui->monthComboBox->currentIndex()-1;
}

int MonthFrame::getYear()
{
    return ui->yearComboBox->currentText().toInt();
}

void MonthFrame::setMonth(int month)
{
    ui->monthComboBox->setCurrentIndex(month - 1);
}

void MonthFrame::setYear(int year)
{
    ui->yearComboBox->setCurrentText(QString::number(year));
}

void MonthFrame::setMonthYear(int month, int year)
{
    setMonth(month);
    setYear(year);
}

bool MonthFrame::addMonth(int value)
{
    int m = ui->monthComboBox->currentIndex() + value;
    if(m > 11){
        ui->monthComboBox->setCurrentIndex(0);
        int y = ui->yearComboBox->currentText().toInt() + 1;
        m = 0;
        if(y > QDate::currentDate().year())
            return false;
        setYear(y);
    }
    if(m < 0){
        ui->monthComboBox->setCurrentIndex(11);
        int y = ui->yearComboBox->currentText().toInt() - 1;
        m = 11;
        if(y < ui->yearComboBox->itemText(0).toInt())
            return false;
        setYear(y);
    }
    ui->monthComboBox->setCurrentIndex(m);
    return true;
}

void MonthFrame::prevMonthSlot()
{
    addMonth(-1);
}
void MonthFrame::nextMonthSlot()
{
    addMonth(1);
}
void MonthFrame::setup()
{
    int month = QDate::currentDate().month();
    int year  = QDate::currentDate().year();
    ui->monthComboBox->addItems(months);
    ui->monthComboBox->setMaxVisibleItems(12);
    for(int i=2020; i<= year; i++){
        ui->yearComboBox->addItem(QString::number(i));
    }
    setMonthYear(month, year);
    connect(ui->prevButton, &QPushButton::clicked,this,&MonthFrame::prevMonthSlot);
    connect(ui->nextButton, &QPushButton::clicked,this,&MonthFrame::nextMonthSlot);

    ui->nextButton->setToolTip("Следующий месяц");
    ui->prevButton->setToolTip("Предыдущий месяц");
    ui->addButton->setToolTip("Добавить тренировку");

    this->setStyleSheet(StyleHelper::getMonthFramleStyle());

}

