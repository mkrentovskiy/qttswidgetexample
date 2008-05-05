#include <QtGui>
#include <QTextStream>

#include <math.h>

#include "Slider.h"
#include "PicButton.h"

#include "../WidgetControl.h"

Slider::Slider(QWidget *p, WidgetControl *wc, QDomElement &n, QDomElement &s, WidgetFabric *wf)
    : QWidget(p)
{	
	bool ok;
	QDomElement	de;

	id = n.attribute("id", NULLVALUE);
	
	min = s.firstChildElement("min").text().toFloat(&ok);
	max = s.firstChildElement("max").text().toFloat(&ok);
	step = s.firstChildElement("step").text().toFloat(&ok);
	pos = s.firstChildElement("pos").text().toFloat(&ok);  
	
	move(n.attribute("x", 0).toInt(&ok, 10), n.attribute("y", 0).toInt(&ok, 10));
	resize(s.firstChildElement("w").text().toInt(&ok, 10), s.firstChildElement("h").text().toInt(&ok, 10));
		
	de = s.firstChildElement("PBUp");
	up = new PicButton(this, wc, de, de, wf);
	
	de = s.firstChildElement("PBDown");
	down = new PicButton(this, wc, de, de, wf);

	background = new QPixmap();
	background->load(s.firstChildElement("background").text(), 0, Qt::DiffuseAlphaDither | Qt::AutoColor);
			
	xs = s.firstChildElement("xs").text().toInt(&ok, 10);  
	ys = s.firstChildElement("ys").text().toInt(&ok, 10);  
	is = s.firstChildElement("is").text().toInt(&ok, 10);  
	js = s.firstChildElement("js").text().toInt(&ok, 10);  

	yd = ys;

	calculate();
		
	// qRegisterMetaType<QString>("QString");
	// connect(this, SIGNAL(valueChanged(QString)), vc, SLOT(isValueChanged(QString)));			

	up->setAutoRepeat(true);
	up->setAutoRepeatInterval(S_AR_INTERVAL);
	connect(up, SIGNAL(clicked()), this, SLOT(stepUp()));
	
	down->setAutoRepeat(true);	
	down->setAutoRepeatInterval(S_AR_INTERVAL);
	connect(down, SIGNAL(clicked()), this, SLOT(stepDown()));			

	wc->registerSlider(id, this);	
	
	show();
}

void Slider::paintEvent(QPaintEvent *)
{	
    QPainter painter(this);	
	QBrush brush(S_COLOR);
	QPen pen(S_COLOR);    	
	
	painter.drawPixmap(0, 0, *background);	
	painter.setPen(pen);	
	painter.setBrush(brush);	
	painter.drawRect(xs, yd, is - xs, js - yd);
}

/*
 * 	Шаг вверх
 */
void Slider::stepUp()
{
	float	np = pos + step;
	if(np > max) pos = max;
	else pos = np;

	calculate();
}

/*
 * 	Шаг вниз
 */
void Slider::stepDown()
{
	float	np = pos - step;
	if(np < min) pos = min;
	else pos = np;

	calculate();
}


/*
 * 	Прыжок на месте - попытка улететь
 */
void Slider::calculate()
{
	float ydd;
	
	ydd = round((float)js - ((float)js - (float)ys) * pos / (max - min)); 
	if(ydd > js) ydd = js; 
	if(ydd < ys) ydd = ys; 
	yd = (int) ydd;		
	
	emit valueChange(pos);	
	if(!up->isDown() && !down->isDown()) emit valueChanged(pos);
	
	repaint(xs, ys, is, js);
}
