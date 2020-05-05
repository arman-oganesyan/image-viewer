#include "imagetaskevent.h"

ImageTaskEvent::ImageTaskEvent(const QString &sPath)
    : ImageTaskEvent(QStringList() << sPath)
{}

ImageTaskEvent::ImageTaskEvent(const QStringList &listPath)
    : QEvent(static_cast<QEvent::Type>(ImageViewerEvent::ImageTaskEvent))
    , listPath(listPath)
{}
