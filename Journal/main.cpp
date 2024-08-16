#include "widget.h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QFile>
#include <QDateTime>
#include <QTextStream>

void logToFile(QtMsgType type, const QMessageLogContext& context, const QString& message);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Загружаем файл переводов для системных окон и контекстого меню.
    QTranslator translator;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    if(translator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        a.installTranslator(&translator);
#else
    if(translator.load("qt_" + QLocale::system().name(), QLibraryInfo::path(QLibraryInfo::TranslationsPath)))
        a.installTranslator(&translator);
#endif

#ifndef QT_DEBUG
    qInstallMessageHandler(logToFile);
#endif

    Widget w;
    w.show();
    return a.exec();
}

void logToFile(QtMsgType type, const QMessageLogContext& context, const QString& message){
    QFile logFile("tace.log");
    if(!logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
        return;
    }
    QTextStream out(&logFile);
    QString dateTimeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    switch (type) {
    case QtDebugMsg:
    case QtWarningMsg:
    case QtCriticalMsg:
    case QtInfoMsg:
        out << dateTimeStr << " " << message << ", " << context.file << "\n";
        break;
    case QtFatalMsg:
        out << dateTimeStr << " " << "Fatal error: " << message << ", " << context.file << "\n";
        abort();
        break;
    }
    logFile.close();
}
