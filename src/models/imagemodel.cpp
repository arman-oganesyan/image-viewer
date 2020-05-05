#include "imagemodel.h"
#include <QDebug>

ImageModel::ImageModel(QObject* parent)
    : QAbstractItemModel(parent)
{}

void ImageModel::addItems(const ImageDataList &listData)
{
    if (!listData.isEmpty())
    {
        beginInsertRows(QModelIndex(), m_paths.size(), m_paths.size() + listData.size() - 1);
        m_paths.append(listData);
        endInsertRows();
    }
}

void ImageModel::clear()
{
    emit beginResetModel();
    m_paths.clear();
    emit endResetModel();
}

QModelIndex ImageModel::index(int row, int column, const QModelIndex &parent) const
{
    if (row < 0 || row >= m_paths.size() || parent.isValid())
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex ImageModel::parent(const QModelIndex &) const
{
    return QModelIndex();
}

int ImageModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_paths.size();
}

int ImageModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 1;
}

QVariant ImageModel::data(const QModelIndex &index, int role) const
{
    if (index.row() >= m_paths.size())
        return QVariant();

    if (role >= Role_Path && role < Role_Count)
    {
        ImageData imageData = m_paths[index.row()];

        switch (role)
        {
            case Role_Path:     return imageData.name;
            case Role_Height:   return imageData.sz.width();
            case Role_Width:    return imageData.sz.width();
            default:            return QVariant();
        }
    }

    return QVariant();
}

QHash<int, QByteArray> ImageModel::roleNames() const
{
    static QHash<int, QByteArray> hashRoles {
        {Role_Path, "path"},
        {Role_Width, "imageWidth"},
        {Role_Height, "imageHeight"}
    };

    return hashRoles;
}
