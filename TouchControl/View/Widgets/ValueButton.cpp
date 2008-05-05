#include <QtGui>

#include "ValueButton.h"

#include "../../Variables.h"

ValueButton::ValueButton(QWidget *p, WidgetControl *wc, QDomElement &n, QDomElement &s, WidgetFabric *wf) 
	: QAbstractButton(p)
{	
	bool ok = false; 
	
	id = n.attribute("id", NULLVALUE);
	state = s.attribute("defaultState", PB_NORMAL);
	
	x = n.attribute("x", 0).toInt(&ok, 10);
	y = n.attribute("y", 0).toInt(&ok, 10);
	w = s.firstChildElement("w").text().toInt(&ok, 10);
	h = s.firstChildElement("h").text().toInt(&ok, 10);
	
	move(x, y);
    resize(w, h);

	setCheckable(false);
	
	QDomElement child = s.firstChildElement("action");
    while (!child.isNull()) {
		QPixmap pm;
		
 		pm.load(child.text(), 0, Qt::DiffuseAlphaDither | Qt::AutoColor); 		
 		states[(child.attribute("type", PB_NULL))] = pm;
		
		child = child.nextSiblingElement("action");
    }    	
    
    QDomElement font = s.firstChildElement("font");
    QFont f(font.firstChildElement("face").text(), font.firstChildElement("size").text().toInt(&ok, 10));
   	setFont(f);	
 
 	QDomElement color = s.firstChildElement("color");    
 	pen.setColor(QColor(color.attribute("r", "128").toInt(&ok, 10), 
 		color.attribute("g", "0").toInt(&ok, 10), 
 		color.attribute("b", "0").toInt(&ok, 10)));
 	
    label = n.attribute("label", s.firstChildElement("label").text());
    connect(this, SIGNAL(clicked()), this, SLOT(isClicked()));    
}

/*
 *  Функция отрисовки - как и что будем выводить
 */
void ValueButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
	painter.setRenderHint(QPainter::TextAntialiasing);
	
	if(!isEnabled()) {
		if(states.contains(PB_DISABLED))
			painter.drawPixmap(0, 0, states[PB_DISABLED]);
		else
			painter.drawPixmap(0, 0, states[state]);
	} else {
		if(isDown()) {
			painter.drawPixmap(0, 0, states[PB_PRESSED]);		
		} else 
    		painter.drawPixmap(0, 0, states[state]);		
	}	
	
	painter.setPen(pen);
	painter.drawText(0, 0, w, h, Qt::AlignVCenter | Qt::AlignHCenter, label); 
}

