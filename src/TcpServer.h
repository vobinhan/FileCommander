#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
    bool startServer(quint16 port);
    void stopServer();

signals:
    void fileReceived(const QString &filePath);
    void statusMessage(const QString &message);

private slots:
    void handleNewConnection();
    void readSocketData();

private:
    QTcpServer *m_server;
    QTcpSocket *m_clientSocket;
    QFile m_receivedFile;
    QString m_saveDir = "C:/FileCommander/Downloads/";
};

#endif // TCPSERVER_H