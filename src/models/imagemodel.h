#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include "data/imagedata.h"

#include <QAbstractItemModel>
#include <QList>

class ImageModel : public QAbstractItemModel
{
    Q_OBJECT

    enum Role {
        Role_Path = Qt::UserRole + 1,
        Role_Width,
        Role_Height,

        Role_Count
    };

public:
    ImageModel(QObject* parent);

    void clear();
    void addItems(const ImageDataList& listData);

    // QAbstractItemModel interface
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

private:
    ImageDataList m_paths;
};

#endif // IMAGEMODEL_H
