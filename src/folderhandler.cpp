#include "folderhandler.h"

#include "core.h"
#include "data/imagedata.h"
#include "events/events.h"

#include <QDirIterator>
#include <QImageReader>
#include <QCoreApplication>

const int kMaxFilesPerTask = 1000;
const int kMaxFoldersPerTask = 50;

FolderHandler::FolderHandler(const QString &rPath, QPointer<Core> pCore)
    : FolderHandler(QStringList() << rPath, pCore)
{}

FolderHandler::FolderHandler(const QStringList& listPath, QPointer<Core> pCore)
    : m_listTasks(listPath)
    , m_pCore(pCore)
{
    QCoreApplication::postEvent(m_pCore, new ImageEventStarted());

    setAutoDelete(true);
}

FolderHandler::~FolderHandler()
{
    QCoreApplication::postEvent(m_pCore, new ImageEventFinished());
}

void FolderHandler::run()
{
    for (const QString& sTaskPath : m_listTasks)
    {
        // Process files in this block
        {
            QDirIterator iteratorImages(sTaskPath, {{"*.jpg"}}, QDir::Files);

            ImageDataList listData;
            listData.reserve(kMaxFilesPerTask);
            int nFiles = 0;

            while(iteratorImages.hasNext())
            {
                QString path = iteratorImages.next();
                QFileInfo info = iteratorImages.fileInfo();

                QImageReader reader(path);
                if (reader.canRead())
                {
                    listData.push_back( ImageData { info.filePath(), reader.size() } );
                    ++nFiles;
                }

                if (nFiles >= kMaxFilesPerTask)
                {
                    QCoreApplication::postEvent(m_pCore.data(), new ImageDataEvent(listData));
                    nFiles = 0;
                    listData.clear();
                }
            }

            if (nFiles)
                QCoreApplication::postEvent(m_pCore.data(), new ImageDataEvent(listData));
        }

        // Process dirs in this block
        {
            QStringList listDirs;
            listDirs.reserve(kMaxFoldersPerTask);
            int nDirs = 0;

            QDirIterator iteratorFolders(sTaskPath, QDir::Dirs | QDir::NoDotAndDotDot);
            while(iteratorFolders.hasNext())
            {
                QString path = iteratorFolders.next();
                if (!QDir(path).isEmpty(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot))
                {
                    listDirs << path;
                    ++nDirs;
                }

                if (nDirs >= kMaxFoldersPerTask)
                {
                    QCoreApplication::postEvent(m_pCore, new ImageTaskEvent(listDirs));
                    nDirs = 0;
                    listDirs.clear();
                }
            }

            if (nDirs)
                QCoreApplication::postEvent(m_pCore, new ImageTaskEvent(listDirs));
        }
    }
}
