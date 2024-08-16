#include "database.h"
#include <QDebug>
#include <QFile>
#include <QDateTime>

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{



}

static int localeCompare( void* /*arg*/, int len1, const void* data1,  int len2, const void* data2 )
{
    QString string1 = QString::fromUtf8((char*)data1,len1).toUpper();
    QString string2 = QString::fromUtf8((char*)data2,len2).toUpper();
    return QString::localeAwareCompare( string1, string2 );
}

static void upper(sqlite3_context *context,  int argc, sqlite3_value **argv){
    if( argc != 1 ) return;
    switch(sqlite3_value_type(argv[0]))
    {
    case SQLITE_NULL:
    {
        sqlite3_result_text( context, "NULL", 4, SQLITE_STATIC );
        break;
    }
    case SQLITE_TEXT:
    {
        QString str(reinterpret_cast<const char*>(sqlite3_value_text(argv[0])));
        str = str.toUpper();
        const char* cstr = static_cast<char*>( str.toUtf8().data());
        sqlite3_result_text(context, cstr, str.toUtf8().size() , SQLITE_TRANSIENT);
        break;
    }
    default:
        sqlite3_result_text( context, "NULL", 4, SQLITE_STATIC );
        break;
    }
}

bool DataBase::connectDb()
{
    if(!QFile(fname).exists()){
        qDebug() << fname << " не существует";
        return restoreDb();
    }else{
        return openDb();
    }
}

bool DataBase::openDb()
{
    if(sqlite3_open(fname.toStdString().c_str(), &db) == SQLITE_OK){
        qDebug() << "Соединение с базой данных установленно.";
        sqlite3_create_function(db, "upper", 1, SQLITE_UTF8, NULL, &upper, NULL, NULL);
        sqlite3_create_collation(db, "NOCASECOLLATE", SQLITE_UTF8, nullptr, &localeCompare );
        return true;
    }else{
        qDebug() << "Не удалось установить соединение с базой данных";
        return false;
    }
}

bool DataBase::restoreDb()
{
    if(!openDb())
        return false;
    QString sql[] = {"CREATE TABLE users ("
        "id         INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name       TEXT NOT NULL,"
        "password   TEXT"
        ");",
        "INSERT INTO users (name, password) "
        "VALUES ('user','123456');"

    };


    char *zErrMsg = 0;
    for(QString& query: sql){
        if(sqlite3_exec(db, query.toStdString().c_str(), nullptr, 0, &zErrMsg) == SQLITE_OK){
            qDebug() << "Запрос " << query << " выполнен успешно.";
        }else{
            qDebug() << "Ошибка! Запрос " << query << " Не выполнен!";
            qDebug() << "Текст сообщения об ошибке: " << zErrMsg;
            return false;
        }
    }
    qDebug() << "База данных создана.";
    return true;
}

void DataBase::closeDb()
{
    sqlite3_close(db);
}
