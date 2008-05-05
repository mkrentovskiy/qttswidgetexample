#include <QtGui>
#include <QFile>

#include "WidgetFabric.h"
#include "WidgetControl.h"

#include "Widgets/PicButton.h"
#include "Widgets/ValueButton.h"
#include "Widgets/Slider.h"
#include "Widgets/Keyboard.h"
#include "Widgets/ControlLine.h"
#include "Widgets/View.h"
#include "Widgets/FrameSet.h"
#include "Widgets/Frame.h"

#include "../Variables.h"

WidgetFabric::WidgetFabric()
{
	QFile file(FABRIC);
	QDomDocument description;
	
	QString errorStr;
    int errorLine;
    int errorColumn;
		
	if (file.open(QFile::ReadOnly | QFile::Text)) {
    	if (description.setContent(&file, true, &errorStr, &errorLine, &errorColumn)) {
    		QDomElement root = description.documentElement();    
    		QDomElement child = root.firstChildElement("widget");
    		
    		while (!child.isNull()) {    			
    			prototypes[(child.attribute("style", NULLVALUE))] = child;
        		child = child.nextSiblingElement("widget");
    		}    
    	}        
    } // TODO: Сделать сообщения об ошибках
}

/*
 *  Создаем все подряд. Так как у нас каскад элементов - будем пичкать в конструкторы все, что только можно.
 */
void WidgetFabric::create(QWidget *p, WidgetControl *wc)
{
	QFile file(INTERFACE);
	QDomDocument description;
	
	QString errorStr;
    int errorLine;
    int errorColumn;
		
	if (file.open(QFile::ReadOnly | QFile::Text)) {
    	if (description.setContent(&file, true, &errorStr, &errorLine, &errorColumn)) {
    		QDomElement root = description.documentElement();    
			createItems(p, wc, root);
    	}        
    }
}

/*
 *  Теперь представим элемент, которому впадлу разбирать, что у него там в потомках тусуется
 */
void WidgetFabric::createItems(QWidget *i, WidgetControl *wc, QDomElement &n)
{
	QDomElement child = n.firstChildElement();
    		
    while (!child.isNull()) {    			
    	QWidget *res = createItem(i, wc, child);
    	child = child.nextSiblingElement();
    }        	
}

/*
 *  Создаем собственно элементы управления. На базе прототипов, разумеется.
 */
QWidget * WidgetFabric::createItem(QWidget *p, WidgetControl *wc, QDomElement &n)
{
	QWidget *res = NULL;
	
	try {
		QString className = n.tagName();
		
		// Картинная кнопка
		if(className == "PicButton") {
			res = new PicButton(p, wc, n, prototypes[(n.attribute("style", NULLVALUE))], this);
		}

		// Кнопка со значением
		if(className == "ValueButton") {
			res = new ValueButton(p, wc, n, prototypes[(n.attribute("style", NULLVALUE))], this);
		}
		
		// Уровень
		if(className == "Slider") {
			res = new Slider(p, wc, n, prototypes[(n.attribute("style", NULLVALUE))], this);
		}
				
		// Клавиатура
		if(className == "Keyboard") {	
			res = new Keyboard(p, wc, n, prototypes[(n.attribute("style", NULLVALUE))], this);
		}

		// Линия контроля устройства
		if(className == "ControlLine") {	
			res = new ControlLine(p, wc, n, prototypes[(n.attribute("style", NULLVALUE))], this);
		}

		// Общий вид
		if(className == "View") {	
			res = new View(p, wc, n, prototypes[(n.attribute("style", NULLVALUE))], this);
		}

		// Куча страница
		if(className == "FrameSet") {	
			res = new FrameSet(p, wc, n, prototypes[(n.attribute("style", NULLVALUE))], this);
		}

		// Страница
		if(className == "Frame") {	
			res = new Frame(p, wc, n, prototypes[(n.attribute("style", NULLVALUE))], this);
		}
	} catch (...) {
		// TODO: Работаем над ошибками, работаем!
	};	
	return res;
}

