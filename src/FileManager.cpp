#include "FileManager.h"
#include <QMessageBox>
#include <QStorageInfo>

FileManager::FileManager(QObject *parent) : QObject(parent) {}

QFileSystemModel* FileManager::getFileSystemModel(const QString &rootPath)
{
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(rootPath);
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
    return model;
}

bool FileManager::copyFile(const QString &source, const QString &destination)
{
    QString normalizedDest = QDir::cleanPath(destination);
    
    if (!validatePath(source) || !validatePath(normalizedDest)) {
        emit operationStatus("Invalid path", true);
        return false;
    }
    
    if (QFile::copy(source, normalizedDest)) {
        emit operationStatus(QString("Copied %1 to %2").arg(source, normalizedDest), false);
        return true;
    }
    emit operationStatus(QString("Failed to copy %1 to %2").arg(source, normalizedDest), true);
    return false;
}

bool FileManager::moveFile(const QString &source, const QString &destination)
{
    QString normalizedDest = QDir::cleanPath(destination);

    if (!validatePath(source) || !validatePath(normalizedDest)) {
        emit operationStatus("Invalid path", true);
        return false;
    }
    
    if (QFile::rename(source, normalizedDest)) {
        emit operationStatus(QString("Moved %1 to %2").arg(source, normalizedDest), false);
        return true;
    }
    emit operationStatus(QString("Failed to move %1 to %2").arg(source, normalizedDest), true);
    return false;
}

bool FileManager::deleteFile(const QString &path)
{
    if (!validatePath(path)) {
        emit operationStatus("Invalid path", true);
        return false;
    }
    
    QFileInfo fileInfo(path);
    if (fileInfo.isDir()) {
        QDir dir(path);
        if (dir.removeRecursively()) {
            emit operationStatus(QString("Deleted directory %1").arg(path), false);
            return true;
        }
    } else {
        if (QFile::remove(path)) {
            emit operationStatus(QString("Deleted file %1").arg(path), false);
            return true;
        }
    }
    emit operationStatus(QString("Failed to delete %1").arg(path), true);
    return false;
}

bool FileManager::createDirectory(const QString &path, const QString &name)
{
    QString fullPath = QDir::cleanPath(path + QDir::separator() + name);
    if (!validatePath(fullPath)) {
        emit operationStatus("Invalid path", true);
        return false;
    }
    
    if (QDir().mkdir(fullPath)) {
        emit operationStatus(QString("Created directory %1").arg(fullPath), false);
        return true;
    }
    emit operationStatus(QString("Failed to create directory %1").arg(fullPath), true);
    return false;
}

bool FileManager::renameFile(const QString &path, const QString &newName)
{
    QFileInfo fileInfo(path);
    QString newPath = QDir::cleanPath(fileInfo.path() + QDir::separator() + newName);
    
    if (!validatePath(path) || !validatePath(newPath)) {
        emit operationStatus("Invalid path", true);
        return false;
    }
    
    if (QFile::rename(path, newPath)) {
        emit operationStatus(QString("Renamed %1 to %2").arg(path, newName), false);
        return true;
    }
    emit operationStatus(QString("Failed to rename %1 to %2").arg(path, newName), true);
    return false;
}

QStringList FileManager::getDrives() const
{
    QStringList drives;
    for (const QStorageInfo &storage : QStorageInfo::mountedVolumes()) {
        if (storage.isValid() && storage.isReady()) {
            drives.append(storage.rootPath());
        }
    }
    return drives;
}

bool FileManager::validatePath(const QString &path)
{
    return path.startsWith("C:") || path.startsWith("D:");
}