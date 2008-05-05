#ifndef VIEW_H_
#define VIEW_H_

#include <QtCore>
#include <QLabel>

#include "../WidgetFabric.h"

#include "../../Variables.h"

class View : public QWidget
{
		Q_OBJECT

		WidgetControl *wc;
		
		QLabel *msl;			// Лебочка для мастер-скорости
		QPixmap	*background;	// Задний фон

	protected:
	    void paintEvent(QPaintEvent *event);

	public slots:
		// Кнопка пуска
		void isStartStopPressed();
	
		// Мастер-скрорость
		void isMasterSpeedChanged(float);
		void isMasterSpeedChange(float);		
		
	public:
		View(QWidget *, WidgetControl *, QDomElement &, QDomElement &, WidgetFabric *);
};

#endif /*VIEW_H_*/
