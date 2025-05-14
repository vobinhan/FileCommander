#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>
#include <QFile>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
    void connectToServer(const QString &host, quint16 port);
    void sendFile(const QString &filePath);
    void disconnectFromHost();

signals:
    void uploadProgress(qint64 bytesSent, qint64 totalBytes);
    void statusMessage(const QString &message);
    void connected();
    void disconnected();

private:
    QTcpSocket *m_socket;
    qint64 m_fileSize;
};

#endif // TCPCLIENT_H