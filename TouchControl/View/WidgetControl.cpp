#include <QtCore>

#include "WidgetFabric.h"
#include "WidgetControl.h"

#ifdef DEBUG
	#include <iostream.h>
#endif

WidgetControl * WidgetControl::instance = NULL;

/*
 *  Паттерн "Одиночка"
 */
	
WidgetControl * WidgetControl::getInstance()
{
	if(instance == NULL) {
		instance = new WidgetControl();
	}
	return instance;
} 

/*
 * 	Инициализация
 */
void WidgetControl::init(QWidget * p)
{
	keys = NULL;
	
	isAlarm = false;
	isBlocked = false;
	isHGo = false;
	
	socket = new QUdpSocket(this);
    socket->bind(CONTROL_PORT);
   	connect(socket, SIGNAL(readyRead()), this, SLOT(gotSignal()));
	
	dss.init(this);
	wf.create(p, this);		
}

/*
 *	Регистрация компонентов
 */
void WidgetControl::registerControlLine(QString i, ControlLine *cli)
{
	cl[i] = cli;
}
	
void WidgetControl::registerButton(QString id, PicButton *b) 
{
	if(id == "PBGO") {
		v->connect(b, SIGNAL(clicked()), v, SLOT(isStartStopPressed()));
		ss = b;	
	}
}

void WidgetControl::registerSlider(QString id, Slider *s) 
{
	if(id == "MASTER") {
		v->connect(s, SIGNAL(valueChange(float)), v, SLOT(isMasterSpeedChange(float)));
		v->connect(s, SIGNAL(valueChanged(float)), v, SLOT(isMasterSpeedChanged(float)));
	}
}

/*
 * Функции отработки элементов управления
 * чтобы различать различные идентификаторы, условимся, что
 * cid - идентификатор элемента управления (например, DEV00)
 * did - идентификатор устройства (например, Ш1)
 * 
 */
void WidgetControl::speedChanged(QString cid, Speed s)
{
	if(mapCL2Dev.contains(cid) && !isAlarm && !isBlocked) {
		dss.setSpeed(mapCL2Dev[cid], s);
	}
}

void WidgetControl::directionChanged(QString cid, Direction d)
{
	if(mapCL2Dev.contains(cid) && !isAlarm && !isBlocked) {
		dss.setDirection(mapCL2Dev[cid], d);
	}
}

void WidgetControl::selectorPressed(QString cid) 
{
	#ifdef DEBUG
		cout << "Clicked: " << cid.toStdString() << endl;
	#endif
	
	if(!isAlarm && !isBlocked) {
		TypeState ts = keys->getType();
		
		if(ts == TS_NONE) {
			// шоколадно, мы не будем назначать устройство
			
			VHState vh = keys->getParam();
			if(vh == VHS_V) {
				// назначается скорость
				float v = keys->getValue();
				
				if(mapCL2Dev.contains(cid)) {
					cl[cid]->setSpeedDirectly((Speed) v);
					// dss.setSpeed(mapCL2Dev[cid], v);
				}
			} else if (vh == VHS_H) {
				// назначается высота
				float h = keys->getValue();
				
				if(mapCL2Dev.contains(cid)) {
					cl[cid]->setTargetHeight(h);
					dss.setHeight(mapCL2Dev[cid], cl[cid]->range(h));
				}
			}
		} else {
			// чорт, мы таки будем ассоциировать файл с устройством 
			QString did;
		
			if(ts == TS_SH) did = "SH";
			if(ts == TS_Z) did = "Z";  
			if(ts == TS_IP) did = "IP";
			if(ts == TS_S) did = "S";
			
			did.append(keys->getString());
	
			#ifdef DEBUG
				cout << "Device: " << did.toStdString() << endl;
			#endif
			
			// проверяем, а есть ли такое устройство
			// а так же то, не проассоциировано ли оно с какой-либо панелью
			if(dss.isInPool(did) && !mapDev2CL.contains(did)) {

				#ifdef DEBUG
					cout << "Device in pool " << endl;
				#endif

				// если есть - радостно сообщаем об этом панельке
				cl[cid]->setTitle(dss.getTitle(did));
				cl[cid]->setLimits(dss.getLimits(did));
				cl[cid]->setState(DS_NONE);
				
				if(mapCL2Dev.contains(cid)) {
					// У нас уже что-то висело на этой линии, надо бы остановить
					dss.setStop(mapCL2Dev[cid]);
				}
				// разумеется, останавливаем и новоприобретенное устройство
				dss.setStop(did);
				
				// ... и добавляем в карты
				mapCL2Dev[cid] = did;
				mapDev2CL[did] = cid;							
			} 
		}	
	}
	keys->clearAll();
}

void WidgetControl::masterSpeedChanged(float s)
{
	if(!isAlarm && !isBlocked) {
		dss.setMasterSpeed(s);
	}
}
		
void WidgetControl::startStopChanged()
{
	if(isAlarm || isBlocked) return;
	
	if(ss->isChecked() && !ss->isDown() && isHGo) {
		// Клавиша нажата - стартуем

		// TODO: Убрать общие команды стопа, заменить их на старт-стоп только нужных устройств 	

		dss.setTotalStart();
	} else if(!ss->isDown()) {
		// Клавиша отжата - стопим
		dss.setTotalStop();
	}	
}

/*
 *  Слоты олова нажатия аппаратной клавиши "Старт-стоп" и ключа "Ща все рубанем"
 *  
 */

void WidgetControl::isHalt()
{
	#ifdef DEBUG
		cout << "I wanna halt you now! " << endl;
	#endif
	
	QByteArray datagram = "HALT";
    socket->writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, CONTROL_PORT);
	
	QProcess::execute("/sbin/halt");
}

void WidgetControl::isGo(bool b)
{
	#ifdef DEBUG
		cout << "I wanna go you now! Value = " << b << endl;
	#endif
	
	isHGo = b;
	startStopChanged();
}


void WidgetControl::gotSignal()
{
	while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
    
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size());

		#ifdef DEBUG
			cout << "Receved : " << datagram.data() << endl; 
		#endif
	          
        if(datagram == "BLOCK") {
        	blockChanged(true);
        }
        if(datagram == "UNBLOCK") {
        	blockChanged(false);
        }
     }
}

			
/*
 *  Функции ловли состояния устройства
 */
 
void WidgetControl::deviceStateChanged(QString did, DeviceState ds, Height h)
{		
	if(mapDev2CL.contains(did)) {
		QString cid = mapDev2CL[did];
		
		if(cl.contains(cid)) {
			cl[cid]->setState(ds);
			cl[cid]->setCurrentHeight(h);
		}
	} 
}

void WidgetControl::alarmChanged(bool as)
{
	if(as != isAlarm) {
		// TODO: Отрубить все элементы управления, заблокировать экран аварийной ошибкой
		isAlarm = as;
	}
}

void WidgetControl::blockChanged(bool bs)
{
	if(bs != isBlocked) {
		
		if(!bs) {
			// ручной режим работы - разрешаем все
		
			dss.setTotalStop();
			ss->setChecked(false);
		
			// scene->setEnabled(false);
			/*
			keys->setEnabled(false);
		
			QHash<QString, ControlLine *>::iterator i = cl.begin();
 			while (i != cl.end()) {
    			((ControlLine *) i.value())->setEnabled(false);
 			}
			*/
		} else {
			// автоматический режим работы - блокируется управление
			
			// scene->setEnabled(true);
			/*
			QHash<QString, ControlLine *>::iterator i = cl.begin();
 			while (i != cl.end()) {
    			((ControlLine *) i.value())->setEnabled(true);
 			}

			keys->setEnabled(true);
			ss->setEnabled(true);
			*/
		}	
		
		isBlocked = bs;
	}
}


