#ifndef FRAMESET_H_
#define FRAMESET_H_

#include <QWidget>
#include <QDomDocument>
#include <QPixmap>
#include <QLabel>

#include "../WidgetControl.h"
#include "../WidgetFabric.h"

#include "Frame.h"
#include "ValueButton.h"

#include "../../Variables.h"

class FrameSet : public QWidget
{
		Q_OBJECT

	public:
		FrameSet(QWidget *, WidgetControl *, QDomElement &, QDomElement &, WidgetFabric *);

	public slots:
		void isFrameSelected(QString);		
				
	private:
		QHash<QString, Frame*> 				frames;
		QHash<QString, ValueButton*> 		buttons;

};

#endif /*FRAMESET_H_*/
