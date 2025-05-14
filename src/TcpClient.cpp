#include "TcpClient.h"

TcpClient::TcpClient(QObject *parent) : QObject(parent),
    m_socket(new QTcpSocket(this)),
    m_fileSize(0)
{
    connect(m_socket, &QTcpSocket::connected, this, &TcpClient::connected);
    connect(m_socket, &QTcpSocket::disconnected, this, &TcpClient::disconnected);
}

void TcpClient::connectToServer(const QString &host, quint16 port) {
    m_socket->connectToHost(host, port);
    if (!m_socket->waitForConnected(2000)) {
        emit statusMessage("Connection error: " + m_socket->errorString());
    }
}

void TcpClient::sendFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        emit statusMessage("Cannot open file: " + file.errorString());
        return;
    }

    m_fileSize = file.size();
    qint64 bytesSent = 0;
    const qint64 chunkSize = 1024 * 1024; // 1MB chunks

    while (!file.atEnd()) {
        QByteArray chunk = file.read(chunkSize);
        qint64 bytesWritten = m_socket->write(chunk);
        if (bytesWritten == -1) {
            emit statusMessage("Write error: " + m_socket->errorString());
            break;
        }
        bytesSent += bytesWritten;
        emit uploadProgress(bytesSent, m_fileSize);
        m_socket->waitForBytesWritten();
    }

    file.close();
    emit statusMessage("File sent successfully");
}

void TcpClient::disconnectFromHost() {
    m_socket->disconnectFromHost();
}
