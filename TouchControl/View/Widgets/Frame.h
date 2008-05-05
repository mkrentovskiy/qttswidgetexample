#ifndef FRAME_H_
#define FRAME_H_

#include <QWidget>
#include <QDomDocument>

#include "../WidgetControl.h"
#include "../WidgetFabric.h"

#include "../../Variables.h"

class Frame : public QWidget
{
	Q_OBJECT

	QPixmap	*background;	// Задний фон

	protected:
	    void paintEvent(QPaintEvent *event);

	public:
		Frame(QWidget *, WidgetControl *, QDomElement &, QDomElement &, WidgetFabric *);		

};

#endif /*FRAME_H_*/
