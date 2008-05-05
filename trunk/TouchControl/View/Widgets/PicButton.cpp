#include <QtGui>

#include "../WidgetControl.h"

#include "PicButton.h"
#include "View.h"

PicButton::PicButton(QWidget *p, WidgetControl *wc, QDomElement &n, QDomElement &s, WidgetFabric *wf) 
	: QAbstractButton(p)
{	
	bool ok = false; 
	
	id = n.attribute("id", NULLVALUE);
	state = s.attribute("defaultState", PB_NORMAL);
	statePrefix = "";
	
	move(n.attribute("x", 0).toInt(&ok, 10), n.attribute("y", 0).toInt(&ok, 10));
    resize(s.firstChildElement("w").text().toInt(&ok, 10), s.firstChildElement("h").text().toInt(&ok, 10));
 	 	
 	if("1" == s.firstChildElement("checked").text()) 
 		setCheckable(true);
	else 
		setCheckable(false);
	
	QDomElement child = s.firstChildElement("action");
    while (!child.isNull()) {
		QPixmap pm;
		
 		pm.load(child.text(), 0, Qt::DiffuseAlphaDither | Qt::AutoColor); 		
 		states[(child.attribute("type", PB_NULL))] = pm;
		
		child = child.nextSiblingElement("action");
    }    	
    
  	connect(this, SIGNAL(clicked()), this, SLOT(isClicked()));    
 
    wc->registerButton(id, this);
   
    show();
   
}

/*
 *  Функция отрисовки - как и что будем выводить
 */
void PicButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

	if(!isEnabled()) {
		if(states.contains(statePrefix + PB_DISABLED))
			painter.drawPixmap(0, 0, states[statePrefix + PB_DISABLED]);
		else
			painter.drawPixmap(0, 0, states[statePrefix + state]);
	} else {
		if(isDown()) {
			painter.drawPixmap(0, 0, states[statePrefix + PB_PRESSED]);		
		} else if(isChecked() && !isDown()) {
			if(state != PB_NORMAL)
    			painter.drawPixmap(0, 0, states[statePrefix + state]);		
			else
    			painter.drawPixmap(0, 0, states[statePrefix + PB_SELECTED]);						
		} else { 
    		painter.drawPixmap(0, 0, states[statePrefix + state]);
		}		
	}		
}

void PicButton::setState(QString s)
{
	state = s;
	repaint();
}
