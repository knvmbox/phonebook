#include <cassert>
#include <memory>

#include <QFile>
#include <QSqlQuery>
#include <QVariant>

#include "csvdataimporter.hpp"
#include "csvreader.hpp"
#include "person.hpp"


//-----------------------------------------------------------------------------
CsvDataImporter::CsvDataImporter(QSqlDatabase &db, const QString &filename) :
    m_db(db),
    m_filename(filename)
{
    assert(QFile(m_filename).exists());
}

//-----------------------------------------------------------------------------
void CsvDataImporter::importData()
{
    std::unique_ptr<CsvReader> reader(new CsvReader(m_filename));

    clearDb();
    while(reader->readline()) {
        Person p = reader->data();
        insertPerson(p);
    }
}

//-----------------------------------------------------------------------------
void CsvDataImporter::clearDb()
{
    QString sql = "delete from t_person";
    QSqlQuery q(sql);

    if(!q.exec()) {
        throw std::runtime_error("Не удалось очистить базу данных");
    }
}

//-----------------------------------------------------------------------------
void CsvDataImporter::insertPerson(const Person &p)
{
    QString sql = (
        "insert into t_person           \n"
        "values (?, ?, ?, ?, ?, ?, ?)   \n"
    );
    QSqlQuery q(sql);

    q.addBindValue(p.firstname().toLower());
    q.addBindValue(p.middlename().toLower());
    q.addBindValue(p.lastname().toLower());
    q.addBindValue(p.depatment());
    q.addBindValue(p.room());
    q.addBindValue(p.phone());
    q.addBindValue(p.mobilePhone());

    if(!q.exec()) {
        throw std::runtime_error("Не удалось добавить данные в базу данных");
    }
}
