#ifndef STYLEHELPER_H
#define STYLEHELPER_H

class QString;


class StyleHelper
{
public:
    static QString getMainStyle();                          //QSS основных элементов интерфейса
    static QString getPasswordModeButtonStyle();            //QSS кнопки изменения типа отображения символов пароля
    static QString getPasswordModeButtonFocusStyle();       //QSS кнопки изменения типа отображения символов пароля,
                                                            //когда поле Пароль в фокусе
    static QString getMonthFramleStyle();
    static QString getLeftWidgetStyle();
    static QString getCalendarButtonStyle(bool active=false);
    static QString getProgressButtonStyle(bool active=false);
    static QString getSettingsButtonStyle(bool active=false);

    static const int lineEditHeight = 30;                   //Высота QLineEdit
    static const int leftWidgetIconWidth = 20;              //Ширина иконки
};

#endif // STYLEHELPER_H
