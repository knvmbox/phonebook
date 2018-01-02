#ifndef APPLICATIONMODEL_HPP
#define APPLICATIONMODEL_HPP

#include <QList>
#include <QObject>

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
    QList<Person> m_persons;
};

#endif // APPLICATIONMODEL_HPP
