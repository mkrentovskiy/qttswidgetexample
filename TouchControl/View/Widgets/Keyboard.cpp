#include <QtGui>

#include "../WidgetControl.h"
#include "Keyboard.h"

#include "../../Variables.h"

Keyboard::Keyboard(QWidget *p, WidgetControl *wc, QDomElement &n, QDomElement &s, WidgetFabric *wf) 
   : QWidget(p)
{
	bool ok;

	id = n.attribute("id", NULLVALUE);
	
	move(n.attribute("x", 0).toInt(&ok, 10), n.attribute("y", 0).toInt(&ok, 10));
    resize(s.firstChildElement("w").text().toInt(&ok, 10), s.firstChildElement("h").text().toInt(&ok, 10));

	QDomElement font = s.firstChildElement("font");
    QFont f(font.firstChildElement("face").text(), font.firstChildElement("size").text().toInt(&ok, 10));
   	
	label = new QLabel(this);
	label->move(s.firstChildElement("xl").text().toInt(&ok, 10), 
		s.firstChildElement("yl").text().toInt(&ok, 10));
	label->resize(s.firstChildElement("wl").text().toInt(&ok, 10), 
		s.firstChildElement("hl")	// connect(s, SIGNAL(valueChange), this, SLOT(isMasterSpeedChange));
	// connect(s, SIGNAL(valueChanged), this, SLOT(isMasterSpeedChanged));
		.text().toInt(&ok, 10));
	label->setText("");
	label->setAlignment(Qt::AlignRight);
	label->setFont(f);
			
	QDomElement child = s.firstChildElement("picbutton");
    while (!child.isNull()) {		
		QString id = (child.attribute("id", NULLVALUE));
		
    	PicButton *pb = new PicButton(this, wc, child, child, wf);
    	pb->show();

		if(id == "0" || id == "1" || id == "2" || id == "3" || id == "4"
			|| id == "5" || id == "6" || id == "7" || id == "8" || id == "9") {
			connect(pb, SIGNAL(idClicked(QString)), this, SLOT(digitClicked(QString)));
		}

		if(id == "P") connect(pb, SIGNAL(clicked()), this, 
        	SLOT(setPoint()));
		if(id == "C") connect(pb, SIGNAL(clicked()), this, 
        	SLOT(clear()));
        	
        if(id == "SH" || id == "IP" || id == "Z" || id == "S") {
        	connect(pb, SIGNAL(idClicked(QString)), this, SLOT(typeClicked(QString)));
        }

        if(id == "V" || id == "H") {
        	connect(pb, SIGNAL(idClicked(QString)), this, SLOT(paramClicked(QString)));
        }
        	
		keys[id] = pb;        
        child = child.nextSiblingElement("picbutton");        
    }    	   
    
    wc->registerKeyboard(this); 
}

/*
 * 	Параметрические функции
 */
 
float Keyboard::getValue()
{	
	float	res = 0;
	QString s = label->text();
	bool ok;
	
	if(s.size() > 0) {
		res = s.toFloat(&ok);
	}
	return ok ? res : 0;
}

QString Keyboard::getString()
{	
	return label->text();
}


TypeState Keyboard::getType()
{	
	TypeState r = TS_NONE;
	
	if(keys["SH"]->isChecked()) r = TS_SH;
	if(keys["IP"]->isChecked()) r = TS_IP;
	if(keys["Z"]->isChecked()) r = TS_Z;
	if(keys["S"]->isChecked()) r = TS_S;	
	return r;
}

VHState Keyboard::getParam()
{	
	VHState r = VHS_NONE;
	
	if(keys["V"]->isChecked()) r = VHS_V;
	if(keys["H"]->isChecked()) r = VHS_H;
	return r;
}

void Keyboard::clearAll() 
{ 
	label->setText("");
	
	keys["SH"]->setChecked(false); 
	keys["IP"]->setChecked(false);
	keys["S"]->setChecked(false);
	keys["Z"]->setChecked(false);
	
	keys["H"]->setChecked(false);
	keys["V"]->setChecked(false);	
}


/*
 *	Слоты отлова событий
 */
 
void Keyboard::digitClicked(QString id)
{
	QString s = label->text();
	
	if(s.size() > K_MAXKEYBOARDNUM) return;
	s.append(id);
	label->setText(s);
}

void Keyboard::setPoint()
{
	QString s = label->text();
	
	if(s.size() > K_MAXKEYBOARDNUM) return;
	if(s.size() == 0) {
		s = "0,";
	} else 	if(s.indexOf(",", 0) == -1) {
		s.append(",");
	}	
	label->setText(s);;
}

void Keyboard::clear()
{
	label->setText("");
}

void Keyboard::typeClicked(QString id)
{
	if(id != "SH") keys["SH"]->setChecked(false);
	if(id != "IP") keys["IP"]->setChecked(false);
	if(id != "Z") keys["Z"]->setChecked(false);
	if(id != "S") keys["S"]->setChecked(false);	

	if(id != "V") keys["V"]->setChecked(false);
	if(id != "H") keys["H"]->setChecked(false);
}

void Keyboard::paramClicked(QString id)
{
	if(id != "SH") keys["SH"]->setChecked(false);
	if(id != "IP") keys["IP"]->setChecked(false);
	if(id != "Z") keys["Z"]->setChecked(false);
	if(id != "S") keys["S"]->setChecked(false);	

	if(id != "V") keys["V"]->setChecked(false);
	if(id != "H") keys["H"]->setChecked(false);
}
