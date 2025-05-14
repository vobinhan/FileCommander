#include "NetworkManager.h"
#include <QFileInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>

NetworkManager::NetworkManager(QObject *parent) : QObject(parent),
    m_networkManager(new QNetworkAccessManager(this)),
    m_tcpSocket(new QTcpSocket(this)),
    m_currentFile(nullptr),
    m_fileSize(0)
{
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &NetworkManager::onUploadFinished);
    connect(m_tcpSocket, &QTcpSocket::connected, this, &NetworkManager::onTcpConnected);
    connect(m_tcpSocket, &QTcpSocket::disconnected, this, &NetworkManager::onTcpDisconnected);
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &NetworkManager::onTcpReadyRead);
}

void NetworkManager::uploadFile(const QUrl &url, const QString &filePath)
{
    QFile *file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly)) {
        emit networkStatus(QString("Failed to open file %1").arg(filePath), true);
        delete file;
        return;
    }
    
    QNetworkRequest request(url);
    QNetworkReply *reply = m_networkManager->put(request, file);
    file->setParent(reply);
    
    connect(reply, &QNetworkReply::uploadProgress, this, &NetworkManager::uploadProgress);
    emit networkStatus(QString("Uploading %1 to %2").arg(filePath, url.toString()), false);
}

void NetworkManager::downloadFile(const QUrl &url, const QString &destination)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = m_networkManager->get(request);
    
    connect(reply, &QNetworkReply::downloadProgress, this, &NetworkManager::downloadProgress);
    connect(reply, &QNetworkReply::finished, this, [this, reply, destination]() {
        onDownloadFinished(reply, destination);
    });
    
    emit networkStatus(QString("Downloading %1 to %2").arg(url.toString(), destination), false);
}

void NetworkManager::startServer(quint16 port)
{
    // Server implementation is in TcpServer class
    emit networkStatus(QString("Server started on port %1").arg(port), false);
}

void NetworkManager::connectToServer(const QString &host, quint16 port)
{
    m_tcpSocket->connectToHost(host, port);
    emit networkStatus(QString("Connecting to %1:%2").arg(host).arg(port), false);
}

void NetworkManager::sendFileOverTcp(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists()) {
        emit networkStatus(QString("File %1 does not exist").arg(filePath), true);
        return;
    }
    
    m_currentFile = new QFile(filePath);
    if (!m_currentFile->open(QIODevice::ReadOnly)) {
        emit networkStatus(QString("Failed to open file %1").arg(filePath), true);
        delete m_currentFile;
        m_currentFile = nullptr;
        return;
    }
    
    m_fileSize = m_currentFile->size();
    
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    
    out << qint64(0) << qint64(0) << fileInfo.fileName();
    out.device()->seek(0);
    out << qint64(block.size() - sizeof(qint64)) << m_fileSize;
    
    m_tcpSocket->write(block);
}

void NetworkManager::onUploadFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        emit networkStatus("Upload completed successfully", false);
    } else {
        emit networkStatus(QString("Upload error: %1").arg(reply->errorString()), true);
    }
    reply->deleteLater();
}

void NetworkManager::onDownloadFinished(QNetworkReply *reply, const QString &destination)
{
    if (reply->error() == QNetworkReply::NoError) {
        QFile file(destination);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(reply->readAll());
            file.close();
            emit networkStatus(QString("Download completed to %1").arg(destination), false);
        } else {
            emit networkStatus(QString("Failed to save file to %1").arg(destination), true);
        }
    } else {
        emit networkStatus(QString("Download error: %1").arg(reply->errorString()), true);
    }
    reply->deleteLater();
}

void NetworkManager::onTcpConnected()
{
    emit networkStatus("Connected to server", false);
}

void NetworkManager::onTcpDisconnected()
{
    emit networkStatus("Disconnected from server", false);
    if (m_currentFile) {
        m_currentFile->close();
        delete m_currentFile;
        m_currentFile = nullptr;
    }
}

void NetworkManager::onTcpReadyRead()
{
    static qint64 bytesReceived = 0;
    static QString fileName;
    static QFile *file = nullptr;
    
    QDataStream in(m_tcpSocket);
    in.setVersion(QDataStream::Qt_5_15);
    
    if (bytesReceived == 0) {
        if (m_tcpSocket->bytesAvailable() < sizeof(qint64) * 2)
            return;
        
        qint64 blockSize, fileSize;
        in >> blockSize >> fileSize >> fileName;
        
        QString savePath = QDir::tempPath() + QDir::separator() + fileName;
        file = new QFile(savePath);
        if (!file->open(QIODevice::WriteOnly)) {
            emit networkStatus(QString("Failed to open file %1").arg(savePath), true);
            delete file;
            file = nullptr;
            return;
        }
        
        bytesReceived = 0;
        m_fileSize = fileSize;
        emit networkStatus(QString("Receiving file %1").arg(fileName), false);
    }
    
    bytesReceived += m_tcpSocket->bytesAvailable();
    file->write(m_tcpSocket->readAll());
    
    if (bytesReceived == m_fileSize) {
        file->close();
        emit fileReceived(file->fileName());
        delete file;
        file = nullptr;
        bytesReceived = 0;
    }
}
