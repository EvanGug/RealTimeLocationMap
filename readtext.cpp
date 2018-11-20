#include "readtext.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

ReadText::ReadText()
{
    init();
}

ReadText::~ReadText()
{
    database.close();
}

void ReadText::init()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MyDataBase.db");
        database.setUserName("root");
        database.setPassword("123456");
    }

    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    QSqlQuery sqlQuery;
    QString createSql = "create table LocationMap (id int primary key, "
                        "firstItem varchar(5), "
                        "uploadDateTime varchar(20), "
                        "locationDateTime varchar(20), "
                        "information varchar(20), "
                        "tempNumber varchar(5), "
                        "longitude varchar(10), "
                        "latitude varchar(10), "
                        "frequence varchar(5))";
    sqlQuery.prepare(createSql);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to create table." << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}

void ReadText::decodeFile(const QStringList &filePathList)
{
    int indexData = 1;
    for (int i = 0; i < filePathList.size(); i ++)
    {
        QFile file(filePathList[i]);
        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            QString err = QObject::tr("Could not open file for Reading");
            throw std::exception(err.toStdString().c_str());
        }

        QTextStream in(&file);
        QString strLine;

        while (in.readLineInto(&strLine))
        {
            strLine = strLine.mid(4, -1);
            QStringList strList = strLine.split("|", QString::SkipEmptyParts);

            if(strList.size() != 8)
            {
                QString err = QObject::tr("Component info format is wrong: %1").arg(strLine);
                throw std::exception(err.toStdString().c_str());
            }

            QSqlQuery sqlQuery;
            QString insertSql = "insert into LocationMap values(?, ?, ?, ?, ?, ?, ?, ?, ?)";
            sqlQuery.prepare(insertSql);
            sqlQuery.addBindValue(indexData);
            sqlQuery.addBindValue(strList[0]);
            sqlQuery.addBindValue(strList[1]);
            sqlQuery.addBindValue(strList[2]);
            sqlQuery.addBindValue(strList[3]);
            sqlQuery.addBindValue(strList[4]);
            sqlQuery.addBindValue(strList[5]);
            sqlQuery.addBindValue(strList[6]);
            sqlQuery.addBindValue(strList[7]);
            if(!sqlQuery.exec())
            {
                qDebug() << sqlQuery.lastError();
            }

            indexData ++;
        }
    }
    qDebug() << indexData;
}

void ReadText::readSql()
{
    QSqlQuery sqlQuery;
    sqlQuery.exec("select id,firstItem,uploadDateTime,locationDateTime,information,tempNumber,longitude,latitude,frequence from LocationMap");

    while(sqlQuery.next())
    {
        int uploadYear = sqlQuery.value(2).toString().split(" ", QString::SkipEmptyParts)[0].split("-", QString::SkipEmptyParts)[0].toInt();
        int uploadMonth = sqlQuery.value(2).toString().split(" ", QString::SkipEmptyParts)[0].split("-", QString::SkipEmptyParts)[1].toInt();
        int uploadDay = sqlQuery.value(2).toString().split(" ", QString::SkipEmptyParts)[0].split("-", QString::SkipEmptyParts)[2].toInt();
        int uploadHour = sqlQuery.value(2).toString().split(" ", QString::SkipEmptyParts)[1].split(":", QString::SkipEmptyParts)[0].toInt();
        int uploadMinute = sqlQuery.value(2).toString().split(" ", QString::SkipEmptyParts)[1].split(":", QString::SkipEmptyParts)[1].toInt();
        int uploadSecond = sqlQuery.value(2).toString().split(" ", QString::SkipEmptyParts)[1].split(":", QString::SkipEmptyParts)[2].toInt();

        int locationYear = sqlQuery.value(3).toString().split(" ", QString::SkipEmptyParts)[0].split("-", QString::SkipEmptyParts)[0].toInt();
        int locationMonth = sqlQuery.value(3).toString().split(" ", QString::SkipEmptyParts)[0].split("-", QString::SkipEmptyParts)[1].toInt();
        int locationDay = sqlQuery.value(3).toString().split(" ", QString::SkipEmptyParts)[0].split("-", QString::SkipEmptyParts)[2].toInt();
        int locationHour = sqlQuery.value(3).toString().split(" ", QString::SkipEmptyParts)[1].split(":", QString::SkipEmptyParts)[0].toInt();
        int locationMinute = sqlQuery.value(3).toString().split(" ", QString::SkipEmptyParts)[1].split(":", QString::SkipEmptyParts)[1].toInt();
        int locationSecond = sqlQuery.value(3).toString().split(" ", QString::SkipEmptyParts)[1].split(":", QString::SkipEmptyParts)[2].toInt();

        Component newComponent;
        newComponent.m_id = sqlQuery.value(0).toInt();
        newComponent.m_firstItem = sqlQuery.value(1).toString();
        newComponent.m_uploadDateTime.setDate(QDate(uploadYear, uploadMonth, uploadDay));
        newComponent.m_uploadDateTime.setTime(QTime(uploadHour, uploadMinute, uploadSecond));
        newComponent.m_locationDateTime.setDate(QDate(locationYear, locationMonth, locationDay));
        newComponent.m_locationDateTime.setTime(QTime(locationHour, locationMinute, locationSecond));
        newComponent.m_information = sqlQuery.value(4).toString();
        newComponent.m_tempNumber = sqlQuery.value(5).toString();
        newComponent.m_coordinate.setX(sqlQuery.value(6).toDouble());
        newComponent.m_coordinate.setY(sqlQuery.value(7).toDouble());
        newComponent.m_frequence = sqlQuery.value(8).toString();

        qDebug() << newComponent.m_id;
        qDebug() << newComponent.m_firstItem;
        qDebug() << newComponent.m_uploadDateTime;
        qDebug() << newComponent.m_locationDateTime;
        qDebug() << newComponent.m_information;
        qDebug() << newComponent.m_tempNumber;
        qDebug() << newComponent.m_coordinate;
        qDebug() << newComponent.m_frequence;

        m_data.push_back(newComponent);
    }
}

const QVector<ReadText::Component> &ReadText::getData() const
{
    return m_data;
}
