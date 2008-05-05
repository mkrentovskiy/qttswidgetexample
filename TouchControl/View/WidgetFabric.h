#ifndef WIDGETFABRIC_H_
#define WIDGETFABRIC_H_

#include <QWidget>
#include <QHash>
#include <QString>
#include <QDomDocument>

class WidgetControl;

class WidgetFabric
{
		QHash<QString, QDomElement> prototypes;
	
	public:
		WidgetFabric();
		
		void create(QWidget *, WidgetControl *);
		void createItems(QWidget *, WidgetControl *, QDomElement &);
		QWidget * createItem(QWidget *, WidgetControl *, QDomElement &);
	
		QDomElement getPrototype(QString cn) { return prototypes[cn]; };
	
};

#endif /*WIDGETFABRIC_H_*/
