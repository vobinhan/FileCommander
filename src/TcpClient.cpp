#include "TcpClient.h"

TcpClient::TcpClient(QObject *parent) : QObject(parent),
    TcpSocket(new QTcpSocket(this))
{
}

bool TcpClient::connectToServer(const QString &host, quint16 port) {

    connect(TcpSocket, &QTcpSocket::readyRead, this, &TcpClient::readSocket);
    connect(TcpSocket, &QTcpSocket::disconnected, this, &TcpClient::discardSocket);

    TcpSocket->connectToHost(QHostAddress(host), port);
    
    if(TcpSocket->waitForConnected(30000))
    {        
        return true;
    }
    else
    {
        return false;
    }
}

void TcpClient::readSocket()
{
    QByteArray buffer;

    QDataStream socketStream(TcpSocket);
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

    // QString SaveFilePath = QCoreApplication::applicationDirPath() + "/" + fileName;
    QString SaveFilePath = QFileDialog::getExistingDirectory(nullptr, "Chose folder save file");
    if (SaveFilePath.isEmpty()) return;
    QString filePath = QDir(SaveFilePath).filePath(fileName);

    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly)){
        file.write(buffer);

        file.close();
    }

}

void TcpClient::discardSocket()
{
    // Remove client form list when client is disconnected 
    TcpSocket->deleteLater();
    TcpSocket=nullptr;
}

bool TcpClient::sendFile(QString &filePath)
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

                return true;
            }
            else
            {
                qDebug() << "File not open!";
                return false;
            }
        }
        else
        {
            qDebug() << "Client socket not open!";
            return false;
        }
    }
    else
    {
        qDebug() << "Client socket is invalid!";
        return false;
    }
}
