#ifndef SCENEELEMENT_H_
#define SCENEELEMENT_H_

#include <QtCore>
#include <QtGui>

#include "../../Variables.h"

class Scene;

class SceneElement : public QWidget
{
		Q_OBJECT
	
		// Реальные позиции в абсолютных величинах
		float xr;
		float yr; 
		float hr;
		
		// Позиции при отрисовке
		int x;
		int y;
		int h;

		int type;			// Тип устройства
		bool paintMe;		// А надо ли вообще меня рисовать
		
		QString title;		// Заголовок
		QColor color;		// Цвет линии
	
		Scene *s;
		
		void calculate();

	protected:
		void paintEvent(QPaintEvent *);
		
	public:
		SceneElement(QWidget *);
	
		void init(QString, float, float, QColor, int);
		void reinit(float, float);
		void setHeight(float);
};

#endif /*SCENEELEMENT_H_*/
