#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    qDebug() << this << "Client Created";
}

Client::~Client()
{
    qDebug() << this << "Client Destroyed";
}

void Client::setSocket(QTcpSocket *socket)
{
    m_socket = socket;
    connect(m_socket,&QTcpSocket::connected, this, &Client::connected);
    connect(m_socket,&QTcpSocket::disconnected, this, &Client::disconnected);
    connect(m_socket,&QTcpSocket::readyRead, this, &Client::readyRead);
    connect(m_socket,&QTcpSocket::bytesWritten, this, &Client::bytesWritten);
    connect(m_socket,&QTcpSocket::stateChanged, this, &Client::stateChanged);
    connect(m_socket,static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error),this,&Client::error);
}

void Client::connected()
{
    qDebug() << this << "Client Connected";
}

void Client::disconnected()
{
    qDebug() << this << "Client Disconnected";
}

void Client::readyRead()
{
    qDebug() << this << "ReadyRead signaled => " << m_socket->readAll();
}

void Client::bytesWritten(qint64 bytes)
{
    qDebug() << this << "BytesWritten Called " << bytes;
}

void Client::stateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << this << "stateChanged" << m_socket << socketState;
}

void Client::error(QAbstractSocket::SocketError socketError)
{
    qDebug() << this << "error" << m_socket << socketError;
}