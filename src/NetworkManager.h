#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QNetworkAccessManager>
#include <QFile>
#include <QDir>
#include <QNetworkReply>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);
    
    void uploadFile(const QUrl &url, const QString &filePath);
    void downloadFile(const QUrl &url, const QString &destination);
    void startServer(quint16 port);
    void connectToServer(const QString &host, quint16 port);
    void sendFileOverTcp(const QString &filePath);
    
signals:
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void networkStatus(const QString &message, bool isError);
    void fileReceived(const QString &filePath);
    
private slots:
    void onUploadFinished(QNetworkReply *reply);
    void onDownloadFinished(QNetworkReply *reply, const QString &destination);
    void onTcpConnected();
    void onTcpDisconnected();
    void onTcpReadyRead();
    
private:
    QNetworkAccessManager *m_networkManager;
    QTcpSocket *m_tcpSocket;
    QFile *m_currentFile;
    qint64 m_fileSize;
};

#endif // NETWORKMANAGER_H
