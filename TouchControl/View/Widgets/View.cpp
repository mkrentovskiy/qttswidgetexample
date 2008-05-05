#include <QtGui>

#include "View.h"

#include "../WidgetControl.h"

View::View(QWidget *p, WidgetControl *wci, QDomElement &n, QDomElement &s, WidgetFabric *wf)
    : QWidget(p)
{	
	QDomElement de;
	bool ok;

	wc = wci;	
					
	move(s.firstChildElement("x").text().toInt(&ok, 10), s.firstChildElement("y").text().toInt(&ok, 10));
	resize(s.firstChildElement("w").text().toInt(&ok, 10), s.firstChildElement("h").text().toInt(&ok, 10));
		
	background = new QPixmap();
	background->load(s.firstChildElement("background").text(), 0, Qt::DiffuseAlphaDither | Qt::AutoColor);

	wc->registerView(this);
	wf->createItems(this, wc, n);		
	
	de = n.firstChildElement("Slider");
	QFont f(de.attribute("lface", FONTFACE), de.attribute("lsize", "16").toInt(&ok, 10));
	
	msl = new QLabel(this);
	msl->move(de.attribute("lx", 0).toInt(&ok, 10), de.attribute("ly", 0).toInt(&ok, 10));
	msl->resize(de.attribute("lw", 0).toInt(&ok, 10), de.attribute("lh", 0).toInt(&ok, 10));
	msl->setFont(f);	
	msl->setAlignment(Qt::AlignLeft);
	msl->setText("0%");
	
	show();
}

/*
 *	Типовая отрисовка - по сути подкладка под корневой элемент 
 */
 
void View::paintEvent(QPaintEvent *pe)
{	
    QPainter painter(this);	
	
	painter.drawPixmap(0, 0, *background);		
}

/*
 * 	Слоты
 */

void View::isStartStopPressed()
{
	wc->startStopChanged();	
}

void View::isMasterSpeedChanged(float v)
{
	wc->masterSpeedChanged(v);
	msl->setText(QString("%1").arg(v, 0, 'f', 0) + "%");
}

void View::isMasterSpeedChange(float v)
{
	msl->setText(QString("%1").arg(v, 0, 'f', 0) + "%");
}

	