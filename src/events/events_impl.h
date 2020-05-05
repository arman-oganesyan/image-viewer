#ifndef IMAGEDATAEVENT_H
#define IMAGEDATAEVENT_H

#include "events.h"
#include "imagedata.h"

#include <QEvent>

class ImageDataEvent : public QEvent
{
public:
    ImageDataEvent(const QList<ImageData>& items);

    QList<ImageData> listData;
};

/////////////////////////////////////////////////////////////

class ImageTaskEvent : public QEvent
{
public:
    ImageTaskEvent(const QString& sPath);
    ImageTaskEvent(const QStringList& listPath);

    QStringList listPath;
};

/////////////////////////////////////////////////////////////

class ImageEventStarted : public QEvent
{
public:
    ImageEventStarted();
};

/////////////////////////////////////////////////////////////

class ImageEventFinished : public QEvent
{
public:
    ImageEventFinished();
};

#endif // IMAGEDATAEVENT_H
