#include "imagedataevent.h"
#include "event_types.h"

ImageDataEvent::ImageDataEvent(const QList<ImageData> &items)
    : QEvent(static_cast<QEvent::Type>(ImageViewerEvent::ImageDataEvent))
    , listData(items)
{}
