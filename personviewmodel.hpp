#ifndef __PERSONVIEWMODEL_HPP__
#define __PERSONVIEWMODEL_HPP__

#include "abstractmodel.hpp"
#include "applicationmodel.hpp"


class PersonViewModel : public AbstractModel
{
public:
    PersonViewModel(ApplicationModel*, QObject *parent = 0);

    QVariant displayData(const QModelIndex&) const override;
    int rowCount(const QModelIndex&) const override;

private:
    void modelDataChanged();

private:
    ApplicationModel *m_model;
    QList<Person> m_data;
};

#endif // PERSONVIEWMODEL_HPP
