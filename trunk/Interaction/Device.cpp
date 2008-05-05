#include <QAbstractSocket>
#include <QUdpSocket>

#include "Device.h"

Device::Device(QString i, QString a, unsigned int p)
{
	enable = false;
	
	id = i;
	address = a;
	port = p;
	
	socket =  new QUdpSocket(this);	
	connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
	connect(socket, SIGNAL(readyRead()), this, SLOT(read()));

	socket->connectToHost(a, p);
	enable = true;	
	
	if(enable) {
		sendCommand(C_STOP, 0, 0);
	}
}

void Device::socketError(QAbstractSocket::SocketError error)
{
	enable = false;
	
	if(error == QAbstractSocket::RemoteHostClosedError || 
		error == QAbstractSocket::SocketTimeoutError ||
		error == QAbstractSocket::NetworkError || 
		error == QAbstractSocket::UnknownSocketError) {
		
		if(socket->state() == QAbstractSocket::UnconnectedState) {
			socket->connectToHost(address, port);
			enable = true;
		}
	}
}


/*
 * 	Передача пакетов
 */
 
void Device::sendCommand(int f, float v, float h)
{
	QByteArray ba;
	
	ba.append(QString("Command: %1 (param =  %2 , %3) \n").arg(f).arg(v).arg(h));
	// TODO: здесь должен быть реальный протокол

	this->write(ba);
} 
 
void Device::write(QByteArray ba)
{
	if(enable) {
		QHostAddress h(address);
		qint16 p = port;
		
		socket->writeDatagram(ba, h, p);	
	}
}

/*
 * 	Прием и разбор пакетов
 */
void Device::read()
{
 	 while(socket->hasPendingDatagrams()) {
		QByteArray data;
		data.resize(socket->pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;

		socket->readDatagram(data.data(), data.size(), &sender, &senderPort);                                 
		if(sender == QHostAddress(address)) process(data, sender);
     }
}

void Device::process(QByteArray d, QHostAddress h)
{
	inq.lock();	// Блокировка, т.к. в функции будет изменено состояние объекта
	
	DeviceValues next(d);
	
	if(!(next == current)) {
		// Состояние изменилось, не к добру
		current = next;
		emit stateChanged(id, next);
	}
	
	inq.unlock(); 	
}



	