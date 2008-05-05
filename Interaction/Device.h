#ifndef DEVICE_H_
#define DEVICE_H_

#include <QObject>

#include <QUdpSocket>
#include <QMutex>

#include "DeviceValues.h"

class Device : public QObject
{
		Q_OBJECT
			
		QString	id;					// идетификатор удаленного устройства
		QString	address;			// адрес
		unsigned int port;			// порт
			
		QUdpSocket *socket;			// сокет
		bool enable;				// есть ли смысл вообще работать

		QMutex	inq;				// мы будем спрашивать и отвечать и нет необходимости, чтоб этот интим кто-то нарушал
		DeviceValues current; 		// текущее состояние устройства

		void write(QByteArray);						// передача пакетов на устройство 
		void process(QByteArray, QHostAddress);		// обработка пришедших пакетов

	signals:
		void stateChanged(QString, DeviceValues);

	private slots:
		void socketError(QAbstractSocket::SocketError);  
		void read(); 
		
	public:
		Device(QString, QString, unsigned int);
		virtual ~Device() { socket->close(); };

		void sendCommand(int, float, float);
};

#endif /*DEVICE_H_*/
