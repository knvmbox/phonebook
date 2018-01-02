#include "applicationmodel.hpp"


//-----------------------------------------------------------------------------
ApplicationModel::ApplicationModel() : QObject()
{
    Person first = {
        "Николай", "Валерьевич", "Иванов", "отдел 1", "111", "13-87", "+7-123-456-78-90"
    };

    Person second = {
        "Сергей", "Петрович", "Сидоров", "отдел 10", "333", "55-67", ""
    };


    m_persons.append(first);
    m_persons.append(second);
}

//-----------------------------------------------------------------------------
void ApplicationModel::findPerson(const QString&, const QString&)
{
    emit dataChanged();
}

//-----------------------------------------------------------------------------
const QList<Person>& ApplicationModel::data()
{
    return m_persons;
}
