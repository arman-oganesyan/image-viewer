#include "imageeventstarted.h"
#include "event_types.h"

ImageEventStarted::ImageEventStarted()
    : QEvent(static_cast<QEvent::Type>(ImageViewerEvent::ImageEventStarted))
{}
