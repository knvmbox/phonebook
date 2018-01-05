#ifndef __DATAIMPORTER_HPP__
#define __DATAIMPORTER_HPP__


class DataImporter
{
public:
    virtual ~DataImporter()
        {}

    virtual void importData() = 0;
};

#endif // DATAIMPORTER_HPP
