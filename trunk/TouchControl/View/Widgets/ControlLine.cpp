#include <QtGui>

#include "../WidgetControl.h"

#include "ControlLine.h"

ControlLine::ControlLine(QWidget *p, WidgetControl *wci, QDomElement &n, QDomElement &s, WidgetFabric *wf) 
	: QWidget(p)
{	
	bool ok = false; 
	QDomElement de, st;
	
	wc = wci;
	
	id = n.attribute("id", NULLVALUE);
	
	move(n.attribute("x", 0).toInt(&ok, 10), n.attribute("y", 0).toInt(&ok, 10));
    resize(s.firstChildElement("w").text().toInt(&ok, 10), s.firstChildElement("h").text().toInt(&ok, 10));
 	
  	QDomElement font = s.firstChildElement("font");
    QFont f(font.firstChildElement("face").text(), font.firstChildElement("size").text().toInt(&ok, 10));
   	 	
 	background = new QPixmap();
	background->load(s.firstChildElement("background").text(), 0, Qt::DiffuseAlphaDither | Qt::AutoColor);
    
    de = s.firstChildElement("VBDevice");
	dev = new ValueButton(this, wc, de, de, wf);
	
	de = s.firstChildElement("PBStartStop");
	ss = new PicButton(this, wc, de, de, wf);

	de = s.firstChildElement("PBUp");
	up = new PicButton(this, wc, de, de, wf);

	de = s.firstChildElement("PBDown");
	down = new PicButton(this, wc, de, de, wf);

	de = s.firstChildElement("SSpeed");
	st = wf->getPrototype("SSpeed");
	vs = new Slider(this, wc, de, st, wf);
	
	// Метки
	de = s.firstChildElement("CHLabel");
	hlc = new QLabel(this);
	hlc->move(de.attribute("x", 0).toInt(&ok, 10), de.attribute("y", 0).toInt(&ok, 10));
	hlc->resize(de.attribute("w", 0).toInt(&ok, 10), de.attribute("h", 0).toInt(&ok, 10));
	hlc->setAlignment(Qt::AlignCenter);
	hlc->setFont(f);	
	hlc->setText("0.00");

	de = s.firstChildElement("THLabel");
	hlt = new QLabel(this);
	hlt->move(de.attribute("x", 0).toInt(&ok, 10), de.attribute("y", 0).toInt(&ok, 10));
	hlt->resize(de.attribute("w", 0).toInt(&ok, 10), de.attribute("h", 0).toInt(&ok, 10));
	hlt->setFont(f);	
	hlt->setAlignment(Qt::AlignCenter);
	hlt->setText("0.00");

	de = s.firstChildElement("SLabel");
	vl = new QLabel(this);
	vl->move(de.attribute("x", 0).toInt(&ok, 10), de.attribute("y", 0).toInt(&ok, 10));
	vl->resize(de.attribute("w", 0).toInt(&ok, 10), de.attribute("h", 0).toInt(&ok, 10));
	vl->setFont(f);
	vl->setAlignment(Qt::AlignCenter);	
	vl->setText("0.00");
	
	connect(vs, SIGNAL(valueChange(float)), this, SLOT(isSpeedChange(float)));		    
	connect(vs, SIGNAL(valueChanged(float)), this, SLOT(isSpeedChanged(float)));		
	    
	connect(dev, SIGNAL(clicked()), this, SLOT(isSelectorPressed()));		    

	connect(up, SIGNAL(clicked()), this, SLOT(isUpPressed()));		    
	connect(down, SIGNAL(clicked()), this, SLOT(isDownPressed()));		    

	connect(ss, SIGNAL(clicked()), this, SLOT(isStartStopPressed()));		    

	setState(DS_NONE);

	wc->registerControlLine(id, this);
}

/*
 *  Функция отрисовки - как и что будем выводить
 */
void ControlLine::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    
	painter.drawPixmap(0, 0, *background);				
}

/*
 * 	Слоты
 */
void ControlLine::isSpeedChange(float v)
{
	vl->setText(QString("%1").arg(v, 0, 'f', 2));
} 

void ControlLine::isSpeedChanged(float v)
{
	vl->setText(QString("%1").arg(v, 0, 'f', 2));
	wc->speedChanged(id, v);
} 

void ControlLine::isSelectorPressed()
{
	wc->selectorPressed(id);
} 

void ControlLine::isStartStopPressed()
{
	if(ss->isChecked()) {
		if(up->isChecked()) {
			wc->directionChanged(id, D_UP);
		} else {
			if(down->isChecked()) {
				wc->directionChanged(id, D_DOWN);
			} else {
				wc->directionChanged(id, D_NONE);
			}
		} 
	} else {
		wc->directionChanged(id, D_NONE);			
	}
}

void ControlLine::isUpPressed()
{
	if(down->isChecked() && down->isEnabled()) {
		down->setChecked(false);
	}
	if(up->isChecked() && !up->isDown()) {
		wc->directionChanged(id, D_UP);
	} else {
		wc->directionChanged(id, D_NONE);
	}
}

void ControlLine::isDownPressed()
{
	if(up->isChecked() && up->isEnabled()) {
		up->setChecked(false);
	}

	if(down->isChecked() && !down->isDown()) {
		wc->directionChanged(id, D_DOWN);
	} else {
		wc->directionChanged(id, D_NONE);
	}
}

/*
 *	Установка состояния элемента	 
 */
void ControlLine::setTitle(QString l)
{
	setState(DS_NONE);
	
	dev->setLabel(l);	
}

void ControlLine::setSpeedDirectly(Speed s) 
{ 
	vs->setPosition(s); 
	wc->speedChanged(id, vs->range(s)); 
}


void ControlLine::setState(DeviceState s)
{
	if(ds == s) return;
	
	switch(ds) {
		case(DS_NONE): {
			dev->setState(PB_NORMAL);
			
			ss->setEnabled(true);
			ss->setChecked(false);
			
			up->setEnabled(true);
			up->setState(PB_NORMAL);
			up->setChecked(false);

			down->setEnabled(true);
			down->setState(PB_NORMAL);
			down->setChecked(false);
			
			vs->setEnabled(true);			
			vs->setPosition(0);
	
			hlc->setText("0.00");
			hlt->setText("0.00");
			
			vl->setText("0.00");
			break;
		}
		case(DS_PROCESS): {
			dev->setState(PB_NORMAL);
			
			ss->setEnabled(true);
			ss->setChecked(false);
			
			up->setEnabled(true);
			up->setState(PB_NORMAL);

			down->setEnabled(true);
			down->setState(PB_NORMAL);
			
			vs->setEnabled(true);			
			break;
		}
		case(DS_ALARM): {
			dev->setState(PB_ALARM);
			
			ss->setChecked(false);
			ss->setEnabled(false);
			
			up->setChecked(false);
			up->setState(PB_ALARM);
			up->setEnabled(false);

			down->setChecked(false);
			down->setState(PB_ALARM);
			down->setEnabled(false);
			
			vs->setEnabled(false);
			break;
		}
		case(DS_UPEND): {
			up->setChecked(false);
			up->setState(PB_FIN);
			up->setEnabled(false);
			break;
		}
		case(DS_UPALARM): {
			up->setChecked(false);
			up->setState(PB_ALARM);
			up->setEnabled(false);
			break;
		}
		case(DS_DOWNEND): {
			down->setChecked(false);
			down->setState(PB_FIN);
			down->setEnabled(false);
			break;
		}
		case(DS_DOWNALARM): {
			down->setChecked(false);
			down->setState(PB_ALARM);
			down->setEnabled(false);
			break;
		}		
	}
	
	ds = s;
}

void ControlLine::setLimits(DeviceLimits lim)
{
	vs->setMaxValue(lim.maxv);
	
	if(lim.h) {
		up->setStatePrefix("h_");
		down->setStatePrefix("h_");
	} else {
		up->setStatePrefix("");
		down->setStatePrefix("");	
	}
	
	dl = lim;
}

