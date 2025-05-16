#ifndef TCPSERVER_H
#define TCPSERVER_H

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

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
    bool startServer(quint16 port);
    void sendFile(const QString &filePath);
signals:

private slots:
    void readSocket(); //
    void discardSocket(); //
    void newConnection(); // 
    void AddToSocketList(QTcpSocket *socket); //

private:
    QTcpServer *Tcp_Server; // 
    QTcpSocket *TcpSocket;
    
};

#endif // TCPSERVER_H
