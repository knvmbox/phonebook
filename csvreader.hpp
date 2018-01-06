#ifndef __CSVREADER_HPP__
#define __CSVREADER_HPP__

#include <QFile>
#include <QString>

#include "person.hpp"


class CsvReader
{
public:
    CsvReader(const QString&);

    const Person& data();
    bool readline();

private:
    bool processLine(const QString &line);

private:
    QFile m_file;
    Person m_person;
    int m_lines;
};

#endif // CSVREADER_HPP
