#ifndef WIDGETCONTROL_H_
#define WIDGETCONTROL_H_

#include <QtCore>
#include <QtGui>
#include <QtNetwork>

#include "../Model/DevicesSubSystem.h"
#include "../Variables.h"

#include "WidgetFabric.h"

#include "Widgets/ControlLine.h"
#include "Widgets/Keyboard.h"
#include "Widgets/View.h"
#include "Widgets/Slider.h"
#include "Widgets/PicButton.h"

class WidgetControl : public QObject
{
		Q_OBJECT
	
	private:
		static WidgetControl *instance;
	
		WidgetFabric wf;					// используем для создания дерева элементов управления
		DevicesSubSystem dss;				// сюда будем передавать управляющую информацию
		
		QHash<QString, ControlLine *> cl;	// панели управления устройствами 
		QHash<QString, QString> mapDev2CL;	// карта соответствий устройств панелям управления
		QHash<QString, QString> mapCL2Dev;  // карта соответствий панелей правлениями устройствам 
		
		Keyboard *keys;						// ссылка на клавиатуру
		PicButton *ss;						// кнопка пуска 
		View *v;							// сцена
		
		bool isAlarm;						// признак аварийности
		bool isBlocked;						// признак блокировки
		bool isHGo;							// признак аппаратного старта
		
		QUdpSocket *socket;					// сокет межсобойного взаимодействия

		WidgetControl() {};
	
	public slots:
		void isHalt();
		void isGo(bool);		

	private slots:
		void gotSignal();		
		
	public:		
		static WidgetControl * getInstance();
		
		void init(QWidget *);
		void registerControlLine(QString, ControlLine *);
		void registerKeyboard(Keyboard *k) { keys = k; };
		void registerButton(QString, PicButton *);
		void registerSlider(QString, Slider *);
		void registerView(View *vi) { v = vi; };
		
		// От подсистемы управления устройствами
		void deviceStateChanged(QString, DeviceState, Height);
		void alarmChanged(bool);
		void blockChanged(bool);
		
		// От интерфейса
		void speedChanged(QString, Speed);
		void directionChanged(QString, Direction);
		void selectorPressed(QString);
		void startStopChanged();
		void masterSpeedChanged(float);
};

#endif /*WIDGETCONTROL_H_*/
