#ifndef VALUEBUTTON_H_
#define VALUEBUTTON_H_

#include <QWidget>
#include <QAbstractButton>
#include <QDomDocument>
#include <QPixmap>
#include <QHash>
#include <QFont>
#include <QPen>

#include "../WidgetFabric.h"

#include "../../Variables.h"

/*
 * 	- Почему не снаследовано как в предыдущей версии?
 * 	- Мало ли...
 */

class ValueButton : public QAbstractButton
{
		Q_OBJECT
	
	public:
		ValueButton(QWidget *, WidgetControl *, QDomElement &, QDomElement &, WidgetFabric *);		
		
		void setState(QString s) { state = s; repaint(); };
		void setLabel(QString l) { label = l; repaint(); };

	signals:
		void idClicked(QString);
		
	protected slots:
		void isClicked() { emit idClicked(id); };
				
	protected:
		QString						id;

    	virtual void paintEvent(QPaintEvent *event);

	private:
		QHash<QString, QPixmap> 	states;
		QString						state;
				
		QString						label;
		QPen 						pen;
 	
		int							x;
		int							y;
		int							w;
		int							h;
};

#endif /*VALUEBUTTON_H_*/
