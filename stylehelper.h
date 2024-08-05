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

    static const int lineEditHeight = 30;                   //Высота QLineEdit
};

#endif // STYLEHELPER_H
