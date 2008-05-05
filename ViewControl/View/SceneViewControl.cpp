#include "SceneViewControl.h"

#ifdef	DEBUG
	#include <iostream.h>
#endif

SceneViewControl * SceneViewControl::instance = NULL;

/*
 *  Паттерн "Одиночка"
 */
	
SceneViewControl * SceneViewControl::getInstance()
{
	if(instance == NULL) {
		instance = new SceneViewControl();
	}
	return instance;
} 

void SceneViewControl::init(QWidget *p)
{
	s = new Scene(p);
	
	socket = new QUdpSocket(this);
    socket->bind(CONTROL_PORT);
   	connect(socket, SIGNAL(readyRead()), this, SLOT(gotSignal()));
	
	dc = new DeviceControl(this);
	dc->run();
}

/*
 * 	Слоты 	
 */

void SceneViewControl::deviceStateChanged(QString did, DeviceValues dv)
{
	s->stateChanged(did, dv.sp, dv.h, dv.s);
}

void SceneViewControl::gotSignal()
{
	while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
    
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size());

		#ifdef DEBUG
			cout << "Receved : " << datagram.data() << endl; 
		#endif
	          
        if(datagram == "HALT") {
        	// Получен сигнал отключения, дергаем за перегородку
        	QProcess::execute("/sbin/halt");
        }
     }
}
