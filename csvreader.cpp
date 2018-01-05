#include <stdexcept>

#include <QFile>

#include "csvreader.hpp"


//-----------------------------------------------------------------------------
CsvReader::CsvReader(const QString &filename) :
    m_lines(0)
{
    if(!QFile(filename).exists())
        throw std::runtime_error("Не удалось открыть файл");

    PersonBuilder builder;


    builder.withFirstname("Николай")
        .withMiddlename("Иванович")
        .withLastname("Петров")
        .withDepartment("отдел 10")
        .withRoom("123")
        .withPhone("13-14");

    m_person = builder.build();
}

//-----------------------------------------------------------------------------
bool CsvReader::readline()
{
    return (m_lines++ <= 10);
}

//-----------------------------------------------------------------------------
const Person& CsvReader::data()
{
    return m_person;
}
