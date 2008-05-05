#ifndef PICBUTTON_H_
#define PICBUTTON_H_

#include <QWidget>
#include <QAbstractButton>
#include <QDomDocument>
#include <QPixmap>
#include <QHash>

#include "../WidgetFabric.h"

#include "../../Variables.h"

class PicButton : public QAbstractButton
{
	Q_OBJECT
	
	public:
		PicButton(QWidget *, WidgetControl *, QDomElement &, QDomElement &, WidgetFabric *);		
		void setState(QString);
		
		void setStatePrefix(QString p) { statePrefix = p; repaint(); };
	signals:
		void idClicked(QString);
		
	protected slots:
		void isClicked() { emit idClicked(id); };
	
	protected:
		QString						id;
    	virtual void paintEvent(QPaintEvent *event);

	private:
		QHash<QString, QPixmap> 	states;
		QString						state;			// состояние кнопки
		QString						statePrefix;	// префикс состояния
};

#endif /*PICBUTTON_H_*/
