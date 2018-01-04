#include "person.hpp"


//-----------------------------------------------------------------------------
QString Person::shortName() const {
    return QString("%1%2%3")
        .arg(m_lastname)
        .arg(m_firstname.isEmpty() ? "" : QString(" %1.").arg(m_firstname[0]))
        .arg(m_middlename.isEmpty() ? "" : QString("%1.").arg(m_middlename[0]));
}

//-----------------------------------------------------------------------------
PersonBuilder& PersonBuilder::withFirstname(const QString &text) {
    m_person.m_firstname = prepare(text);
    return *this;
}

//-----------------------------------------------------------------------------
PersonBuilder& PersonBuilder::withMiddlename(const QString &text) {
    m_person.m_middlename = prepare(text);
    return *this;
}

//-----------------------------------------------------------------------------
PersonBuilder& PersonBuilder::withLastname(const QString &text) {
    m_person.m_lastname = prepare(text);
    return *this;
}

//-----------------------------------------------------------------------------
PersonBuilder& PersonBuilder::withDepartment(const QString &text) {
    m_person.m_depatment = text;
    return *this;
}

//-----------------------------------------------------------------------------
PersonBuilder& PersonBuilder::withRoom(const QString &text) {
    m_person.m_room = text;
    return *this;
}

//-----------------------------------------------------------------------------
PersonBuilder& PersonBuilder::withPhone(const QString &text) {
    m_person.m_phone = text;
    return *this;
}

//-----------------------------------------------------------------------------
PersonBuilder& PersonBuilder::withMobilephone(const QString &text) {
    m_person.m_mobilePhone = text;
    return *this;
}

//-----------------------------------------------------------------------------
QString PersonBuilder::prepare(const QString &text) const {
    return (text.left(1).toUpper() + text.mid(1));
}
