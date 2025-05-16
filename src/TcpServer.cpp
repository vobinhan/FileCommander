#include "TcpServer.h"
#include <QProgressBar>
#include <QStatusBar>

TcpServer::TcpServer(QObject *parent) : QObject(parent),
    Tcp_Server(new QTcpServer(this))
{
    
}

bool TcpServer::startServer(quint16 port) 
{
    Tcp_Server = new QTcpServer(); // Init server object
    if(Tcp_Server->listen(QHostAddress::AnyIPv4, port))
    {
        connect(Tcp_Server, &QTcpServer::newConnection, this, &TcpServer::newConnection);
        return true;
    }
    else
    {
        return false;
    }
}

void TcpServer::newConnection() 
{
    while (Tcp_Server->hasPendingConnections())
        // Add new comming TCP Client in Server
        AddToSocketList(Tcp_Server->nextPendingConnection());
}

void TcpServer::AddToSocketList(QTcpSocket *socket)
{
    connect(socket, &QTcpSocket::readyRead, this, &TcpServer::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &TcpServer::discardSocket);
}  

void TcpServer::readSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray buffer;

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_6_0);

    socketStream.startTransaction();
    socketStream >> buffer; // get data on socket stream or from client socket

    if(!socketStream.commitTransaction())
    {
        return;
    }

    QString header = buffer.mid(0,128); // extect header data

    

    QString fileName = header.split(",")[0].split(":")[1];
    QString fileExt = fileName.split(".")[1];
    QString fileSize = header.split(",")[1].split(":")[1];



    buffer = buffer.mid(128);

    QString SaveFilePath = QFileDialog::getExistingDirectory(nullptr, "Chose folder save file");
    if (SaveFilePath.isEmpty()) return;
    QString filePath = QDir(SaveFilePath).filePath(fileName);

    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly)){
        file.write(buffer);

        file.close();
    }

}

void TcpServer::discardSocket()
{
    // Remove client form list when client is disconnected 
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
        
    socket->deleteLater();
}

void TcpServer::sendFile(const QString &filePath)
{
    if(TcpSocket)
    {
        if(TcpSocket->isOpen())
        {
            QFile filedata(filePath);
            if(filedata.open(QIODevice::ReadOnly))
            {
                QFileInfo fileinfo(filedata);
                QString FileNameWithExt(fileinfo.fileName());

                QDataStream socketstream(TcpSocket);
                socketstream.setVersion(QDataStream::Qt_6_0);

                // this code use send file name also with data
                QByteArray header;
                header.prepend("file name: " + FileNameWithExt.toUtf8() + ", file size: " + QString::number(filedata.size()).toUtf8()); // .toUtf8()
                header.resize(128);

                // Now lets add file data
                QByteArray ByteFileData = filedata.readAll();
                ByteFileData.prepend(header);

                // Write in socket
                socketstream << ByteFileData;
            }
            else
            {
                qDebug() << "File not open!";
            }
        }
        else
        {
            qDebug() << "Client socket not open!";
        }
    }
    else
    {
        qDebug() << "Client socket is invalid!";
    }
}
