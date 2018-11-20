#ifndef READTEXT_H
#define READTEXT_H

#include <QDateTime>
#include <QPointF>
#include <QVector>
#include <QtSql>

class ReadText
{
public:
    ReadText();
    ~ReadText();

    struct Component
    {
        int m_id;
        QString m_firstItem;
        QDateTime m_uploadDateTime;
        QDateTime m_locationDateTime;
        QString m_information;
        QString m_tempNumber;
        QPointF m_coordinate;
        QString m_frequence;
    };

    void decodeFile(const QStringList &filePathList);

    void readSql();
    const QVector<Component> &getData() const;

private:
    QVector<Component> m_data;
    QSqlDatabase database;
//    QSqlQuery sqlQuery;

    void init();
};

#endif // READTEXT_H
