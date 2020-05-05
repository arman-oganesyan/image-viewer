#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <QString>
#include <QSize>
#include <QList>

struct ImageData {
    QString name;
    QSize sz;
};

using ImageDataList = QList<ImageData>;

#endif // IMAGEDATA_H
