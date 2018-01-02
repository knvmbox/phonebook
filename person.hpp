#ifndef PERSON_HPP
#define PERSON_HPP

#include <QString>


struct Person
{
    QString firstname;
    QString middlename;
    QString lastname;

    QString depatment;
    QString room;

    QString phone;
    QString mobilePhone;

    QString shortName() const {
        return QString("%1%2%3")
            .arg(lastname)
            .arg(firstname.isEmpty() ? "" : QString(" %1.").arg(firstname[0]))
            .arg(middlename.isEmpty() ? "" : QString("%1.").arg(middlename[0]));
    }
};

#endif // PERSON_HPP
