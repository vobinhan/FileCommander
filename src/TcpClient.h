#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QMetaType>
#include <QList>
#include <QStandardPaths>
#include <QTcpServer>
#include <QTcpSocket>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
    bool connectToServer(const QString &host, quint16 port);
    // void sendFile(const QString &filePath);
    bool sendFile(QString &filePath);

private slots:
    void readSocket();
    void discardSocket();

private:
    QTcpSocket *TcpSocket;
};

#endif // TCPCLIENT_H
