#include <QtGui>

#include "Frame.h"

Frame::Frame(QWidget *p, WidgetControl *wc, QDomElement &n, QDomElement &s, WidgetFabric *wf)
	: QWidget(p)
{
	bool ok;
	
	move(s.firstChildElement("x").text().toInt(&ok, 10), s.firstChildElement("y").text().toInt(&ok, 10));
	resize(s.firstChildElement("w").text().toInt(&ok, 10), s.firstChildElement("h").text().toInt(&ok, 10));
	
	wf->createItems(this, wc, n);

	if(s.firstChildElement("background").text().size() > 0) {
		background = new QPixmap();
		background->load(s.firstChildElement("background").text(), 0, Qt::DiffuseAlphaDither | Qt::AutoColor);
	} else background = NULL;
}

/*
 *	Типовая отрисовка 
 */
 
void Frame::paintEvent(QPaintEvent *pe)
{	
    QPainter painter(this);	
	
	if(background != NULL) painter.drawPixmap(0, 0, *background);		
}

