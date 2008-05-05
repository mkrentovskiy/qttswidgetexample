#include <QtGui>

#include "FrameSet.h"

FrameSet::FrameSet(QWidget *p, WidgetControl *wc, QDomElement &n, QDomElement &s, WidgetFabric *wf)
	: QWidget(p)
{	
	bool ok, f = true, b = true;
	
	move(s.firstChildElement("x").text().toInt(&ok, 10), s.firstChildElement("y").text().toInt(&ok, 10));
	resize(s.firstChildElement("w").text().toInt(&ok, 10), s.firstChildElement("h").text().toInt(&ok, 10));
	
	
	QDomElement child = n.firstChildElement("Frame");
    while (!child.isNull()) {
		QDomElement style = wf->getPrototype(child.attribute("style", NULLVALUE)); 
		frames[(child.attribute("id", NULLVALUE))] = new Frame(this, wc, child, style, wf);		
		if(f) {
			frames[(child.attribute("id", NULLVALUE))]->setVisible(true);
			f = false;
		} else {
			frames[(child.attribute("id", NULLVALUE))]->setVisible(false);			
		}
		child = child.nextSiblingElement("Frame");
    }    		

	child = n.firstChildElement("ValueButton");
    while (!child.isNull()) {
		QDomElement style = wf->getPrototype(child.attribute("style", NULLVALUE)); 
		buttons[(child.attribute("id", NULLVALUE))] = new ValueButton((QWidget *) this, wc, child, style, wf);		
		connect(buttons[(child.attribute("id", NULLVALUE))], SIGNAL(idClicked(QString)), this, SLOT(isFrameSelected(QString)));		
		if(b) {
			buttons[(child.attribute("id", NULLVALUE))]->setState(PB_SELECTED);
			b = false;
		}
		child = child.nextSiblingElement("ValueButton");
    }    	
}

/*
 * 	Если кто-то нажал на кнопку...
 */

void FrameSet::isFrameSelected(QString i)
{
    frames[i]->setVisible(true);
	
	QHashIterator<QString, Frame*> i_f(frames);
 	while (i_f.hasNext()) {
    	i_f.next();
    	if(i_f.key() != i && ((Frame *) i_f.value())->isVisible()) {
    		frames[(i_f.key())]->setVisible(false);
    	}
 	}   
	
	QHashIterator<QString, ValueButton*> i_b(buttons);
 	while (i_b.hasNext()) {
    	i_b.next();
    	if(i_b.key() == i) {
    		buttons[(i_b.key())]->setState(PB_SELECTED);	
    	} else {
    		buttons[(i_b.key())]->setState(PB_NORMAL);
    	}
 	}	
}
