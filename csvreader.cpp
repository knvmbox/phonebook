#include <stdexcept>

#include <QStringList>

#include "csvreader.hpp"


//-----------------------------------------------------------------------------
CsvReader::CsvReader(const QString &filename) :
    m_file(filename),
    m_lines(0)
{
    if(!QFile(filename).exists())
        throw std::runtime_error("Файл не существует");
    if (!m_file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error("Не удалось открыть файл");
}

//-----------------------------------------------------------------------------
const Person& CsvReader::data()
{
    return m_person;
}

//-----------------------------------------------------------------------------
bool CsvReader::readline()
{
    while(!m_file.atEnd()) {
        QByteArray line = m_file.readLine();
        if(line.isEmpty())
            continue;
        if(processLine(QString(line)))
            return true;
    }

    return false;
}

//-----------------------------------------------------------------------------
bool CsvReader::processLine(const QString &line)
{
    QStringList list = line.split(";");
    if(list.size() < 6)
        return false;

    PersonBuilder pb;

    QString firstname = list[0].simplified();

    pb.withFirstname(firstname.toLower())
        .withMiddlename(list[1].simplified())
        .withLastname(list[2].simplified())
        .withDepartment(list[3].simplified())
        .withRoom(list[4].simplified())
        .withPhone(list[5].simplified());

    if(list.size() == 7)
        pb.withMobilephone(list[6].simplified());

    m_person = pb.build();
    return true;
}
