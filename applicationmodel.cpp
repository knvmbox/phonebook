#include <stdexcept>

#include <QSqlQuery>
#include <QVariant>

#include "applicationmodel.hpp"


//-----------------------------------------------------------------------------
ApplicationModel::ApplicationModel() : QObject()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("db/phonebook.db");

    if (!m_db.open()) {
        throw std::runtime_error("Can't open database");
    }
}

//-----------------------------------------------------------------------------
void ApplicationModel::findPerson(const QString &lastname_, const QString &phone_)
{
    QString lastname = lastname_.simplified().toLower();
    QString phone = phone_.simplified();


    m_persons.clear();

    if(!lastname.isEmpty() || !phone.isEmpty()) {
        QSqlQuery q(prepareSql(lastname, phone));
        q.exec();

        while(q.next()) {

            Person p = PersonBuilder()
                .withFirstname(q.value(0).toString())
                .withMiddlename(q.value(1).toString())
                .withLastname(q.value(2).toString())
                .withDepartment(q.value(3).toString())
                .withRoom(q.value(4).toString())
                .withPhone(q.value(5).toString())
                .withMobilephone(q.value(6).toString())
                .build();
            m_persons.append(p);
        }
    }

    emit dataChanged();
}

//-----------------------------------------------------------------------------
const QList<Person>& ApplicationModel::data()
{
    return m_persons;
}

//-----------------------------------------------------------------------------
QString ApplicationModel::prepareSql(const QString &lastname, const QString &phone)
{
    if(phone.isEmpty()) {
        QString sql = (
            "select firstname,              \n"
            "       middlename,             \n"
            "       lastname,               \n"
            "       department,             \n"
            "       room,                   \n"
            "       phone,                  \n"
            "       mobilephone             \n"
            "  from t_person p              \n"
            " where p.lastname like '%1'    \n"
        );
        return sql.arg(lastname + "%");

    } else if(lastname.isEmpty()) {
        QString sql = (
            "select firstname,              \n"
            "       middlename,             \n"
            "       lastname,               \n"
            "       department,             \n"
            "       room,                   \n"
            "       phone,                  \n"
            "       mobilephone             \n"
            "  from t_person p              \n"
            " where p.phone like '%1'    \n"
        );
        return sql.arg(phone + "%");
    } else {
        QString sql = (
            "select firstname,              \n"
            "       middlename,             \n"
            "       lastname,               \n"
            "       department,             \n"
            "       room,                   \n"
            "       phone,                  \n"
            "       mobilephone             \n"
            "  from t_person p              \n"
            " where p.lastname like '%1'    \n"
            "   and p.phone like '%2'       \n"
        );
        return sql.arg(lastname + "%").arg(phone + "%");
    }
}
