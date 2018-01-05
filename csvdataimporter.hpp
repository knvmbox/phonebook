#ifndef CSVDATAIMPORTER_HPP
#define CSVDATAIMPORTER_HPP

#include <QSqlDatabase>

#include "dataimporter.hpp"
#include "person.hpp"


class CsvDataImporter : public DataImporter
{
public:
    CsvDataImporter(QSqlDatabase&, const QString&);

    void importData() override;

private:
    void clearDb();
    void insertPerson(const Person&);

private:
    QSqlDatabase &m_db;
    QString m_filename;
};

#endif // CSVDATAIMPORTER_HPP
