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

int DataBase::login(const std::string &name, const std::string &password)
{
    std::string sql = "SELECT id FROM users WHERE name='"+name+"' and password='"+password+"'";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str() ,-1, &stmt, NULL);
    if( rc != SQLITE_OK ){
        qDebug() << "Не удалось выполнить запрос к базе данных " << sql.c_str();

    }
    while(sqlite3_step(stmt) == SQLITE_ROW )
    {
        return reinterpret_cast<const int> (sqlite3_column_int(stmt,0));
    }
    sqlite3_finalize(stmt);
    return 0;
}
DataBase::TreningsInMonth DataBase::getTreings(int month, int year)
{
    TreningsInMonth map;
    std::string sql = "SELECT * FROM trenings WHERE year="+std::to_string(year)+
                      " and month="+std::to_string(month)+" ORDER BY day, time";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str() ,-1, &stmt, NULL);
    if( rc != SQLITE_OK ){
        qDebug() << "Не удалось выполнить запрос к базе данных " << sql.c_str();
        return map;
    }

    int dayNum = 0;
    QVector <Trening> vec;
    while(sqlite3_step(stmt) == SQLITE_ROW )
    {
        Trening trening;
        trening.type = reinterpret_cast<const int> (sqlite3_column_int(stmt,1));
        trening.name = reinterpret_cast<const char*> (sqlite3_column_text(stmt,2));
        trening.place = reinterpret_cast<const char*> (sqlite3_column_text(stmt,3));
        trening.time = reinterpret_cast<const char*> (sqlite3_column_text(stmt,7));
        trening.day  = sqlite3_column_int(stmt,6);
        if(dayNum != trening.day){
            if(vec.size() > 0)
                map.insert(dayNum, vec);
            vec.clear();
            dayNum = trening.day;
        }
        vec.append(trening);
    }
    sqlite3_finalize(stmt);
    if(vec.size()>0){
        map.insert(dayNum, vec);
    }


    return map;
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
    QString sql[] = {
        "CREATE TABLE users ("
        "id         INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name       TEXT NOT NULL,"
        "password   TEXT"
        ");",
        "INSERT INTO users (name, password) "
        "VALUES ('user','123456');",
        "CREATE TABLE trenings ("
        "id          INTEGER PRIMARY KEY AUTOINCREMENT,"
        "type        INTEGER,"
        "name        TEXT NOT NULL,"
        "place       TEXT,"
        "year        INTGER,"
        "month       INTGER,"
        "day         INTGER,"
        "time        TEXT,"
        "duration    INTEGER,"
        "description TEXT,"
        "keywords    TEXT"
        ");",
        "INSERT INTO trenings (type, name, place, year, month, day, time, duration, description, keywords) "
        "VALUES (1,'Тренировка для примера 1','Где-то там', 2025, 4, 12, '10:00', 90,'Короктое описание.', ',пример 1, утро,');",
        "INSERT INTO trenings (type, name, place, year, month, day, time, duration, description, keywords) "
        "VALUES (2,'Тренировка для примера 2','Где-то здесь', 2025, 4, 12,  '18:00', 90,'Короктое описание 2.', ',пример 1, вечер,');",
        "INSERT INTO trenings (type, name, place, year, month, day, time, duration, description, keywords) "
        "VALUES (1,'Тренировка для примера 3','Где-то здесь', 2025, 4, 18,  '18:00', 90,'Короктое описание 3.', ',пример 2, вечер,');"

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
