#ifndef APPLICATIONMODEL_HPP
#define APPLICATIONMODEL_HPP

#include <QList>
#include <QObject>
#include <QSqlDatabase>

#include "person.hpp"


class ApplicationModel : public QObject
{
    Q_OBJECT
public:
    ApplicationModel();

    const QList<Person>& data();
    void findPerson(const QString&, const QString&);

signals:
    void dataChanged();

public slots:

private:
    QString prepareSql(const QString&, const QString&);

private:
    QList<Person> m_persons;
    QSqlDatabase m_db;
};

#endif // APPLICATIONMODEL_HPP
