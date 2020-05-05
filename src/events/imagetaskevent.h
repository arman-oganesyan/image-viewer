#ifndef IMAGETASKEVENT_H
#define IMAGETASKEVENT_H

#include "event_types.h"

#include <QEvent>
#include <QStringList>

class ImageTaskEvent : public QEvent
{
public:
    ImageTaskEvent(const QString& sPath);
    ImageTaskEvent(const QStringList& listPath);

    QStringList listPath;
};

#endif // IMAGETASKEVENT_H
