#ifndef SCENEVIEWCONTROL_H_
#define SCENEVIEWCONTROL_H_

#include <QtCore>
#include <QtNetwork>

#include "../../Interaction/DeviceControl.h"
#include "Widgets/Scene.h"

#include "../Variables.h"


class SceneViewControl: public QObject
{
		Q_OBJECT
	
	private:
		static SceneViewControl *instance;
		
		Scene *s;
		DeviceControl *dc;	
		QUdpSocket *socket;

		SceneViewControl() {};
			
	signals:
		void isNewCommand(QString, int, float);
		
	public slots:
		void deviceStateChanged(QString, DeviceValues);

	private slots:
		void gotSignal();

	public:		
		static SceneViewControl * getInstance();
		
		void init(QWidget *);
};

#endif /*SCENEVIEWCONTROL_H_*/
