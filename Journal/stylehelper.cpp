#include "stylehelper.h"
#include <QString>

QString StyleHelper::getMainStyle()
{
    return "QWidget#Widget{"
           "    background:#fff;"
           "}"

           //TabWidget
           "QTabWidget::pane{"
           "    border:none;"
           "}"

           //-----------------------
           //   Поля вкладки Логин
           //-----------------------

           //Поле Имя пользователя
           "QLineEdit#loginEdit{"
           "    border:1px solid #ccc;"
           "    background: #eee;"
           "    border-top-right-radius:3px;"
           "    border-bottom-right-radius:3px;"
           "    padding:3px;"
           "    font-size:12px;"
           "}"
           "QLineEdit#loginEdit[text=\"\"]{"
           "    color:#555;"
           "}"

           //Поле Пароль
           "QLineEdit#passwordEdit{"
           "    border:1px solid #ccc;"
           "    border-right:none;"
           "    background: #eee;"
           "    padding:3px;"
           "    font-size:12px;"
           "}"
           "QLineEdit#passwordEdit[text=\"\"]{"
           "    color:#555;"
           "}"

           //Наведение на поля Имя пользователя и Пароль
           "QWidget#loginTab QLineEdit::hover{"
           "    background-color: #f2f2f2;"
           "}"

           //Фокус полей Имя пользователя и Пароль
           "QWidget#loginTab QLineEdit::focus{"
           "    background-color: #fafafa;"
           "}"

           //Пиктограммы рядом с полями ввода
           "QLabel#loginIcoLabel, QLabel#passwordIcoLabel{"
           "    background: #f5f5f5;"
           "    border-top-left-radius:3px;"
           "    border-bottom-left-radius:3px;"
           "    border:1px solid #ccc;"
           "    border-right:none;"
           "    min-width:25px;"
           "}"


           //Кнопки Войти и Отмена
           "QPushButton#loginButton{"
           "    background:#5E98D1;"
           "    color:#fff;"
           "    border-radius:3px;"
           "    padding:5px;"
           "    font-size:14px;"
           "}"
           "QPushButton#loginButton::disabled{"
           "    background:#aaa;"
           "}"
           "QPushButton#loginButton::hover{"
           "    background:#1E83E1;"
           "}"
           "QPushButton#loginButton::focus{"
           "    border: 1px solid #00538e;"
           "    background:#1E83E1;"
           "}"
           "QPushButton#canselButton{"
           "    background:#ccc;"
           "    color:#fff;"
           "    border-radius:3px;"
           "    padding:5px;"
           "    font-size:14px;"
           "}"
           "QPushButton#canselButton::hover{"
           "    background:#E16053;"
           "}"
           "QPushButton#canselButton::focus{"
           "    background:#E16053;"
           "    border:1px solid #2ba4fb;"
           "}"


           //Кнопки Забыл пароль и  Новый пользователь
           "QPushButton#repasswordButton, QPushButton#newUserButton{"
           "    border:none;"
           "    color: #aaa;"
           "    font-size:12px;"
           "    text-align:left;"
           "    margin-top:10px;"
           "}"
           "QPushButton#repasswordButton::hover, QPushButton#newUserButton::hover{"
           "    color:#7098e5;"
           "    text-decoration:underline;"
           "}"

           //Сообщение об ошибке
           "QLabel#errorMsgLabel{"
           "    color:red;"
           "}"

           //------------------------
           //  Календарь
           //-----------------------
           "QWidget#calendarTab{"
           "    background:#eff4fd;"
           "}"
           "QWidget#daysContainerWidget{"
           "    background:#e1e8ed;"
           "}"
           "QLabel#headerLabel{"
           "    font-size:16px;"
           "    color:#555;"
           "}"
           "QScrollArea{"
           "    border:none;"
           "}"
           "QWidget#scrollAreaWidgetContents{"
           "    background:#e1e8ed;"
           "}"
           "QWidget#scrollAreaWidgetContents QLabel{"
           "    background:#fff;"
           "    padding:10px;"
           "}"
           "QTabWidget#infoTabWidget QTabBar::tab{"
           "    padding:10px;"
           "background: #eaeaf1;"
           "color:#8f8f8f;"
           "}"
           "QTabWidget#infoTabWidget QTabBar::tab:selected{"
           "background: #fafafa;"
           "color:#555;"
           "}"
           "QWidget#monthTab, QWidget#treningTab{"
           "    background:#fafafa;"
           "}"
           "QTabWidget#infoTabWidget::pane{"
           "    background:#fff;"
           "}";



}

/* Кнопка Показать/скрыть пароль */
QString StyleHelper::getPasswordModeButtonStyle()
{
    return "QPushButton#passwordModeButton{"
           "    border-top:1px solid #ccc;"
           "    border-right:1px solid #ccc;"
           "    border-bottom:1px solid #ccc;"
           "    background: #eee;"
           "    border-top-right-radius:3px;"
           "    border-bottom-right-radius:3px;"
           "    margin:0px;"
           "}";
}

QString StyleHelper::getPasswordModeButtonFocusStyle()
{
    return "QPushButton#passwordModeButton{"
           "    border-top:1px solid #ccc;"
           "    border-right:1px solid #ccc;"
           "    border-bottom:1px solid #ccc;"
           "    background: #fafafa;"
           "    border-top-right-radius:3px;"
           "    border-bottom-right-radius:3px;"
           "    margin:0px;"
           "}";
}

/* Виджет для выбора месяца и года  */
QString StyleHelper::getMonthFramleStyle()
{
    return "QPushButton{"
           "    background:#fff;"
           "    border:none;"
           "    min-height:" + QString::number(StyleHelper::lineEditHeight) + "px;"
           "}"
           "QPushButton#prevButton {"
           "    qproperty-icon: url(\":/images/left-arrow.png\");"
           "    border-top-left-radius:3px;"
           "    border-bottom-left-radius:3px;"
           "}"
           "QPushButton#nextButton {"
           "qproperty-icon: url(\":/images/right-arrow.png\");"
           "    border-top-right-radius:3px;"
           "    border-bottom-right-radius:3px;"
           "}"
           "QPushButton#prevButton::hover {"
           "   background:#eee;"
           "}"
           "QPushButton#nextButton::hover {"
           "   background:#eee;"
           "}"
           "QPushButton#addButton{"
           "    border-radius:3px;"
           "    color:#fff;"
           "    background: #545bde;"
           "    font-weight:bold;"
           "    padding-left:20px;"
           "   padding-right:20px;"
           "   margin-left:10px;"
           "}"
           "QPushButton#addButton::hover{"
           "   background:#646bee;"
           "}"
           "QComboBox{"
           "    background:#fff;"
           "    border:none;"
           "    min-height:" + QString::number(StyleHelper::lineEditHeight) + "px;"

           "    color:#777;"
           "    font-size:14px;"
           "}"
           "QComboBox::hover{"
           "    color:#000;"
           "}"
           "QComboBox#monthComboBox{"
           "   padding-left:10px;"
            "   min-width:65px;"
           "}"
            "QComboBox#yearComboBox{"
            "   min-width:35px;"
            "   padding-right:5px;"
            "}"
           "QComboBox#monthComboBox::drop-down{"
           "    border:none;"
           "    width: 0px;"
           "}"
           "QComboBox#yearComboBox::drop-down{"
           "    border:none;"
           "    width: 0px;"
           "}"
            "QComboBox QAbstractItemView{"
            "   outline:0px;"
            "}"
            "QComboBox QAbstractItemView::item:selected {"
            "   background-color: #646bee;"
            "   color:#fff;"
            "}";
}

QString StyleHelper::getLeftWidgetStyle()
{
    return "QWidget#leftWidget{"
           "    background:#fafafa;"
           "}";
}

QString StyleHelper::getCalendarButtonStyle(bool active)
{

    if(active){
        return "QPushButton#calendarButton {"
            "    background:#545bde;"
            "    border-radius:3px;"
            "    qproperty-icon: url(:/images/calendar-white.svg)"
            "}";
    }
    return "QPushButton#calendarButton {"
           "    background:#fafafa;"
           "    border-radius:3px;"
           "    qproperty-icon: url(:/images/calendar.svg)"
           "}"
           "QPushButton#calendarButton::hover {"
           "    background:#ddd;"
           "}";
}
QString StyleHelper::getProgressButtonStyle(bool active)
{

    if(active){
        return "QPushButton#progressButton {"
               "    background:#545bde;"
               "    border-radius:3px;"
               "    qproperty-icon: url(:/images/stats-white.svg);"
               "}";
    }
    return "QPushButton#progressButton {"
           "    background:#fafafa;"
           "    border-radius:3px;"
           "    qproperty-icon: url(:/images/stats.svg);"
           "}"
           "QPushButton#progressButton::hover {"
           "    background:#ddd;"
           "}";
}
QString StyleHelper::getSettingsButtonStyle(bool active)
{

    if(active){
        return "QPushButton#settingsButton {"
               "    background:#545bde;"
               "    border-radius:3px;"
               "    qproperty-icon: url(:/images/settings-white.svg);"
               "}";
    }
    return "QPushButton#settingsButton {"
           "    background:#fafafa;"
           "    border-radius:3px;"
           "    qproperty-icon: url(:/images/settings.svg);"
           "}"
           "QPushButton#settingsButton::hover {"
           "    background:#ddd;"
           "}";
}



