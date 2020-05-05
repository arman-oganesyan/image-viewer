#ifndef FOLDER_HANDLER_H
#define FOLDER_HANDLER_H

#include <QRunnable>
#include <QString>
#include <QPointer>

class Core;
class ImageFolder;

class FolderHandler : public QRunnable
{
public:
    FolderHandler(const QString&, QPointer<Core>);
    FolderHandler(const QStringList&, QPointer<Core>);
    ~FolderHandler() override;

    void run() override;

private:
    QStringList m_listTasks;
    QPointer<Core> m_pCore;
};

#endif // FOLDER_HANDLER_H
