#include "imageeventfinished.h"
#include "event_types.h"

ImageEventFinished::ImageEventFinished()
    : QEvent(static_cast<QEvent::Type>(ImageViewerEvent::ImageEventFinished))
{}
