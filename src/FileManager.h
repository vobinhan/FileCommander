#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QFileSystemModel>
#include <QDir>

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);
    
    QFileSystemModel* getFileSystemModel(const QString &rootPath);
    bool copyFile(const QString &source, const QString &destination);
    bool moveFile(const QString &source, const QString &destination);
    bool deleteFile(const QString &path);
    bool createDirectory(const QString &path, const QString &name);
    bool renameFile(const QString &path, const QString &newName);
    
    QStringList getDrives() const;
    
signals:
    void operationStatus(const QString &message, bool isError);
    
private:
    bool validatePath(const QString &path);
};

#endif // FILEMANAGER_H