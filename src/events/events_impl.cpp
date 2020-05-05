#include "events_impl.h"
#include <QDebug>

ImageDataEvent::ImageDataEvent(const QList<ImageData> &items)
    : QEvent(static_cast<QEvent::Type>(ImageViewerEvent::ImageDataEvent))
    , listData(items)
{}

/////////////////////////////////////////////////////////////

ImageTaskEvent::ImageTaskEvent(const QString &sPath)
    : ImageTaskEvent(QStringList() << sPath)
{}

ImageTaskEvent::ImageTaskEvent(const QStringList &listPath)
    : QEvent(static_cast<QEvent::Type>(ImageViewerEvent::ImageTaskEvent))
    , listPath(listPath)
{}

/////////////////////////////////////////////////////////////

ImageEventStarted::ImageEventStarted()
    : QEvent(static_cast<QEvent::Type>(ImageViewerEvent::ImageEventStarted))
{}

/////////////////////////////////////////////////////////////

ImageEventFinished::ImageEventFinished()
    : QEvent(static_cast<QEvent::Type>(ImageViewerEvent::ImageEventFinished))
{}
