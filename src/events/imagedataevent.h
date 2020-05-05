#ifndef IMAGEDATAEVENT_H
#define IMAGEDATAEVENT_H

#include "data/imagedata.h"

#include <QEvent>

class ImageDataEvent : public QEvent
{
public:
    ImageDataEvent(const QList<ImageData>& items);

    QList<ImageData> listData;
};

#endif // IMAGEDATAEVENT_H
