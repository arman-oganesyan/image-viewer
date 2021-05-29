#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QPointer>
#include <QUrl>
#include <QVariant>

#include "data/imagedata.h"

// fwd declaration
class QAbstractItemModel;
class QRunnable;
class ImageModel;

class Core : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int state READ state NOTIFY stateChanged)

public:
    explicit Core(QObject *parent = nullptr);

    enum State {
        Idle = 0,
        Working,
        Stopping,
    };

    Q_ENUM(State);

    Q_INVOKABLE void start(const QUrl&);
    Q_INVOKABLE void stop();
    Q_INVOKABLE QVariant model();

    int state() const;
    bool isWorking() const;

    // QObject interface
    bool event(QEvent *event) override;

signals:
    void stateChanged(int);

private:
    void setState(int);

    void tryExecute(bool bCheckForIdle = false);
    void requestToStart(QRunnable*);
    void incrementActive();
    void decrementActive();
    bool isJobFinished() const;


private:
    int m_nState;
    int m_nActive;
    int m_nRequestedToStart;
    QPointer<ImageModel> m_pModel;
    QList<QStringList> m_listPendings;

};
#endif // CORE_H
