#ifndef CONTROLLINE_H_
#define CONTROLLINE_H_

#include <QWidget>
#include <QAbstractButton>
#include <QDomDocument>
#include <QPixmap>
#include <QLabel>

#include "../WidgetFabric.h"

#include "PicButton.h"
#include "ValueButton.h"
#include "Slider.h"

#include "../../Variables.h"

class WidgetControl;

class ControlLine : public QWidget
{
		Q_OBJECT
		
	public slots:
		void isSpeedChange(float);
		void isSpeedChanged(float);
		
		void isSelectorPressed();
		void isStartStopPressed();
		void isUpPressed();
		void isDownPressed();
	
	protected:
    	virtual void paintEvent(QPaintEvent *event);

	private:
		QString	id;
		QPixmap	*background;
		
		ValueButton	*dev; 	// Кнопка соотнесения с усройством
		PicButton *ss;		// Персональный включатель-выключатель	
		
		// Высотная секция
		QLabel *hlt;	 	// Высота назначения
		QLabel *hlc;		// Текущая высота
		PicButton *up;		// Направление вверх/открыто
		PicButton *down;	// Направление вниз/закрыто

		// Скоростная секция
		QLabel *vl;			// Текущая скорость
		Slider *vs;			// Манипулятор изменения скорости
		
		// Секция устройства
		DeviceState	ds;		// Состояние устройства
		DeviceLimits dl;	// Ограничения устройства
		
		WidgetControl *wc;
	
	public:
		ControlLine(QWidget *, WidgetControl *, QDomElement &, QDomElement &, WidgetFabric *);		
	
		void setState(DeviceState);
		QString getId() { return id; };
		
		void setTitle(QString);
		void setLimits(DeviceLimits);
		void setSpeedDirectly(Speed);
		void setTargetHeight(Height h) { hlt->setText(QString("%1").arg(range(h), 0, 'f', 2));};
		void setCurrentHeight(Height h) { hlc->setText(QString("%1").arg(h, 0, 'f', 2));};

		float range(float f) {
			float r = f;
			if(f > dl.maxh) r = dl.maxh;
			if(f < dl.minh) r = dl.minh;	
			return r; 
		};	
};

#endif /*CONTROLLINE_H_*/
