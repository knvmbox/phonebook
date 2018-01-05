#ifndef __CSVREADER_HPP__
#define __CSVREADER_HPP__

#include <QString>

#include "person.hpp"


class CsvReader
{
public:
    CsvReader(const QString&);

    const Person& data();
    bool readline();

private:
    Person m_person;
    int m_lines;
};

#endif // CSVREADER_HPP
