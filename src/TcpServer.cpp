#include "TcpServer.h"
#include <QDir>

TcpServer::TcpServer(QObject *parent) : QObject(parent), 
    m_server(new QTcpServer(this)), 
    m_clientSocket(nullptr) {}

bool TcpServer::startServer(quint16 port) {
    if (m_server->isListening()) {
        emit statusMessage("Server already running");
        return false;
    }

    QDir().mkpath(m_saveDir);
    
    if (!m_server->listen(QHostAddress::Any, port)) {
        emit statusMessage("Server error: " + m_server->errorString());
        return false;
    }
    
    connect(m_server, &QTcpServer::newConnection, this, &TcpServer::handleNewConnection);
    emit statusMessage(QString("Server started on port %1").arg(port));
    return true;
}

void TcpServer::handleNewConnection() {
    m_clientSocket = m_server->nextPendingConnection();
    connect(m_clientSocket, &QTcpSocket::readyRead, this, &TcpServer::readSocketData);
    connect(m_clientSocket, &QTcpSocket::disconnected, m_clientSocket, &QTcpSocket::deleteLater);
    emit statusMessage("Client connected");
}

void TcpServer::readSocketData() {
    if (!m_receivedFile.isOpen()) {
        QString filePath = m_saveDir + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
        m_receivedFile.setFileName(filePath);
        if (!m_receivedFile.open(QIODevice::WriteOnly)) {
            emit statusMessage("Cannot open file for writing");
            return;
        }
    }

    m_receivedFile.write(m_clientSocket->readAll());
    
    if (m_clientSocket->atEnd()) {
        m_receivedFile.close();
        emit fileReceived(m_receivedFile.fileName());
    }
}

void TcpServer::stopServer() {
    if (m_receivedFile.isOpen()) m_receivedFile.close();
    m_server->close();
}