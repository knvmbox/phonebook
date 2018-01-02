#ifndef ABSTARCTMODEL_HPP
#define ABSTARCTMODEL_HPP

#include <QAbstractListModel>
#include <QList>


class AbstractModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AbstractModel(QObject *parent = 0);

    virtual int columnCount(const QModelIndex&) const
        {   return m_columns.size();    }

    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);


    void addColumn(const QString &col)
        {    m_columns.append(col);    }
    const QList<QString>& columns() const
        {    return m_columns;    }

    virtual QVariant displayData(const QModelIndex &index) const = 0;

    virtual QVariant backgroundColor(const QModelIndex&) const
        {    return QVariant();   }
    virtual QVariant checkStateData(const QModelIndex&) const
        {    return QVariant();   }
    virtual QVariant editData(const QModelIndex&) const
        {    return QVariant();   }
    virtual QVariant textAlignment(const QModelIndex&) const
        {    return QVariant();   }

    virtual bool setCheckData(const QModelIndex&, const QVariant&)
        {    return false;   }
    virtual bool setValueData(const QModelIndex&, const QVariant&)
        {    return false;   }

signals:

public slots:

private:
    QList<QString> m_columns;
};

#endif // ABSTARCTMODEL_HPP
