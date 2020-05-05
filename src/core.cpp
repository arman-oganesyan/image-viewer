#include "core.h"

#include <QCoreApplication>
#include <QThreadPool>
#include <QQmlEngine>

#include "models/imagemodel.h"
#include "folderhandler.h"
#include "events/events.h"

Core::Core(QObject *parent)
    : QObject(parent)
    , m_nState(State::Idle)
    , m_nActive(0)
    , m_nRequestedToStart(0)
    , m_pModel(new ImageModel(this))
{
    qmlRegisterUncreatableType<Core>("CoreState", 1, 0, "CoreState", QString());
}

void Core::start(const QUrl& folder)
{
    setState(State::Working);
    m_nActive = 0;
    m_nRequestedToStart = 0;
    m_listPendings.clear();
    m_pModel->clear();
    QCoreApplication::postEvent(this, new ImageTaskEvent(folder.toLocalFile()));
}

void Core::stop()
{
    setState(State::Stopping);
    m_listPendings.clear();
}

QVariant Core::model()
{
    return QVariant::fromValue(m_pModel.data());
}

int Core::state() const
{
    return m_nState;
}

bool Core::isWorking() const
{
    return state() == State::Working;
}

bool Core::event(QEvent *event)
{
    if (!event)
        return QObject::event(event);

    if (event->type() == static_cast<QEvent::Type>(ImageViewerEvent::ImageDataEvent))
    {
        if (ImageDataEvent* pImageEvent = dynamic_cast<ImageDataEvent*>(event))
        {
            m_pModel->addItems(pImageEvent->listData);
            return true;
        }
    }
    else if (event->type() == static_cast<QEvent::Type>(ImageViewerEvent::ImageTaskEvent))
    {
        if (isWorking())
        {
            if (ImageTaskEvent* pTaskEvent = dynamic_cast<ImageTaskEvent*>(event))
            {
                m_listPendings << pTaskEvent->listPath;
                tryExecute();
            }
        }

        return true;
    }
    else if (event->type() == static_cast<QEvent::Type>(ImageViewerEvent::ImageEventStarted))
    {
        incrementActive();
        tryExecute();
        return true;
    }
    else if (event->type() == static_cast<QEvent::Type>(ImageViewerEvent::ImageEventFinished))
    {
        decrementActive();
        tryExecute(true);
        return true;
    }

    return QObject::event(event);
}

void Core::tryExecute(bool bCheckForIdle)
{
    if (isWorking())
    {
        if (m_nActive <= QThreadPool::globalInstance()->maxThreadCount() && !m_listPendings.isEmpty())
            requestToStart(new FolderHandler(m_listPendings.takeFirst(), this));
        else if (bCheckForIdle && isJobFinished())
            setState(State::Idle);
    }
    else if (!m_nActive)
    {
        setState(State::Idle);
        m_listPendings.clear();
    }
}

void Core::requestToStart(QRunnable *pRunnable)
{
    ++m_nRequestedToStart;
    QThreadPool::globalInstance()->start(pRunnable);
}

void Core::incrementActive()
{
    ++m_nActive;
    --m_nRequestedToStart;
}

void Core::decrementActive()
{
    --m_nActive;
}

bool Core::isJobFinished() const
{
    return !m_nActive && !m_nRequestedToStart && m_listPendings.isEmpty();
}

void Core::setState(int nState)
{
    if (nState != m_nState)
    {
        m_nState = nState;
        emit stateChanged(m_nState);
    }
}
