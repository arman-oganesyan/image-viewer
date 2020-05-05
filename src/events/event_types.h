#ifndef EVENT_TYPES_H
#define EVENT_TYPES_H

#include <QEvent>

enum class ImageViewerEvent
{
    ImageDataEvent = QEvent::User,
    ImageTaskEvent,
    ImageEventStarted,
    ImageEventFinished,
};

#endif // EVENT_TYPES_H
