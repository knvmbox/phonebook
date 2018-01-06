#ifndef __PERSON_HPP__
#define __PERSON_HPP__

#include <QDebug>
#include <QString>


///////////////////////////////////////////////////////////////////////////////
class PersonBuilder;

///////////////////////////////////////////////////////////////////////////////
class Person
{
    friend PersonBuilder;

public:
    const QString& firstname() const
        {   return m_firstname;   }
    const QString& middlename() const
        {   return m_middlename;   }
    const QString& lastname() const
        {   return m_lastname;   }

    const QString& depatment() const
        {   return m_depatment;   }
    const QString& room() const
        {   return m_room;   }

    const QString& phone() const
        {   return m_phone;   }
    const QString& mobilePhone() const
        {   return m_mobilePhone;   }

    QString shortName() const;

private:
    QString m_firstname;
    QString m_middlename;
    QString m_lastname;

    QString m_depatment;
    QString m_room;

    QString m_phone;
    QString m_mobilePhone;
};

///////////////////////////////////////////////////////////////////////////////
class PersonBuilder
{
public:
    const Person& build()
        {   return m_person;   }

    PersonBuilder& withFirstname(const QString &text);
    PersonBuilder& withMiddlename(const QString &text);
    PersonBuilder& withLastname(const QString &text);
    PersonBuilder& withDepartment(const QString &text);
    PersonBuilder& withRoom(const QString &text);
    PersonBuilder& withPhone(const QString &text);
    PersonBuilder& withMobilephone(const QString &text);

private:
    QString prepare(const QString &text) const;

private:
    Person m_person;
};

#endif // PERSON_HPP
