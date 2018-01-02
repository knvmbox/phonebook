#include <QDebug>

#include "personviewmodel.hpp"


//-----------------------------------------------------------------------------
PersonViewModel::PersonViewModel(ApplicationModel *model, QObject *parent) :
    AbstractModel(parent),
    m_model(model)
{
    addColumn("ФИО");
    addColumn("отдел");
    addColumn("комната");
    addColumn("телефон");
    addColumn("мобильный");

    connect(m_model, &ApplicationModel::dataChanged, this, &PersonViewModel::modelDataChanged);
}

//-----------------------------------------------------------------------------
QVariant PersonViewModel::displayData(const QModelIndex &index) const
{
    if(!index.isValid() || index.row() > m_data.size())
        return QVariant();

    switch(index.column()) {
    case 0:
        return m_data[index.row()].shortName();
    case 1:
        return m_data[index.row()].depatment;
    case 2:
        return m_data[index.row()].room;
    case 3:
        return m_data[index.row()].phone;
    case 4:
        return m_data[index.row()].mobilePhone;
    }

    return QVariant();
}

//-----------------------------------------------------------------------------
int PersonViewModel::rowCount(const QModelIndex&) const
{
    return m_data.size();
}

//-----------------------------------------------------------------------------
void PersonViewModel::modelDataChanged()
{
    beginResetModel();

    m_data = m_model->data();

    endResetModel();
}
