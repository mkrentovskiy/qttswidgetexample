#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <QWidget>
#include <QHash>
#include <QLabel>
#include <QPen>

#include "PicButton.h"

class Keyboard : public QWidget
{
	Q_OBJECT
	
	public:
		Keyboard(QWidget *, WidgetControl *, QDomElement &, QDomElement &, WidgetFabric *);

		float getValue();
		QString getString();	
		TypeState getType();
		VHState getParam();
		
		bool isEmpty() { return (label->text()).size() == 0; };
		void clearAll();	
	
	public slots:
		void digitClicked(QString);	
		void setPoint();	
		void clear();	
		
		void typeClicked(QString);
		void paramClicked(QString);
		
	private: 
		QString id;
		QLabel *label;
		QHash<QString, PicButton *> keys;
};

#endif /*KEYBOARD_H_*/
