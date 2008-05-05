#include <math.h>

#include "../../Variables.h"

#include "Scene.h"
#include "SceneElement.h"
#include "SceneParam.h"

#ifdef	DEBUG
	#include <iostream.h>
#endif

SceneElement::SceneElement(QWidget *parent) : QWidget(parent) 
{
		s = (Scene *) parent;
		
		xr = 0;
		yr = 0;
		hr = 0;
		
		x = 0;
		y = 0;
		h = 200;
		
		title = "";
		type = 0;
		
		move(0, 0);
		resize(_X + _W, _Y + _H + _L / _DEL);
		
		paintMe = false;
}

/*
 * Инициализация элемента 
 */
void SceneElement::init(QString t, float w, float h, QColor c, int tp)
{
	title = t;
	
	xr = w;
	yr = h;

	type = tp;
	color = c;
	
	paintMe = true;
	
	calculate();
	show();
}

/*
 * Повторная инициализация элемента, если поменялись настройки 
 */
void SceneElement::reinit(float w, float h)
{
	hide();
	xr = w;
	yr = h;
	
	paintMe = true;
	
	calculate();
	show();
}


void SceneElement::setHeight(float nh)
{
	if(nh == hr) return;
	 
	hr = nh;
	h = round(nh * _H / PH_HEIGTH);
	
	// Ограничение на высоту
	switch(type) {
		case(T_IP): {	
			if(h < _IP_H) h = _IP_H;
			break;
		}
	}
	
	repaint();
}

/*
 * 	Калькуляция при смене параметров
 */
void SceneElement::calculate()
{
	// Тут беда - для штанкетов и ИП разные значения X и Y
	switch(type) {
		case(T_IP): {	
			// индивидуальные подвесы
			x = _X + (xr * _W / PH_WIDTH) - (yr * _L / (PH_LENGTH * _DEL));
			y = _Y + (yr * _L / (PH_LENGTH * _DEL));
			break;
		}
		case(T_SH):
		case(T_S): {	
			// штанкеты и софиты
			x = _X + (xr * _W / PH_WIDTH);
			y = _Y;
			break;
		}
	}
		
	#ifdef DEBUG
		cout << "Coordinates : " << x << " " << y << " " << xr << " " << yr << endl; 
	#endif
	
	/*
	TODO: Очень нехорошо ресайзить на всю сцену элемент, с другой стороны - вычислять 
	размеры видимой области забодаешься - надо спросить координаты меток, принять во
	внимаие их размер, пересчитать смещения... короче, гемморой. В дайльнейшем эту 
	псевдотрехмерность поменять на номальный OpenGL и не париться.
	
	switch(type) {
		case(T_IP): {	
			move(x - _IP_TW / 2, y - _IP_L);
			resize( _IP_TW, _IP_TH);
			break;
		}
	}
	*/
	
	if(x > _MAX || x < 0 || y > _MAX || y < 0) paintMe = false; 
}

/*
 * 	Отрисовка
 */
void SceneElement::paintEvent(QPaintEvent *)
{
	if(!paintMe) return;
	
	QPainter painter(this);	
	QPen pen(color);
	
	painter.setPen(pen);	
	painter.setBrush(color);	

	QFont fn(_T_NF, _T_NS, _T_NT);
    setFont(fn);
    QFontMetrics fm(fn);
	
	painter.drawText(x - (fm.width(title) / 2), y - _T_NS, title);
	
	switch(type) {
		case(T_IP): {	
			// Рисуем индивидуальные подвесы
			painter.drawRect(x - _IP_W / 2, y - _IP_W / 2, _IP_W, _IP_W);
			painter.drawLine(x, y, x, y + h);
			painter.drawRect(x - _IP_W / 2, y + h - _IP_H, _IP_W, _IP_H);
			break;
		}
		case(T_SH): {	
			// Рисуем штанкеты
			painter.drawLine(x, y, x, y + h);
		
			// Рисуем собственно штанкет
			// Топ
			painter.setBrush(_SH_C2);
		 	QPoint pT[4] = {
     			QPoint(x - _SH_P / 2, y + h - _SH_P / 2),
     			QPoint(x + _SH_P / 2 , y + h - _SH_P / 2),
     			QPoint(x + _SH_P / 2 - _L / _DEL, y + _L / _DEL + h - _SH_P / 2),
     			QPoint(x - _SH_P / 2 - _L / _DEL, y + _L / _DEL + h - _SH_P / 2)
 			};
 			painter.drawPolygon(pT, 4);

			// Боковина			
			painter.setBrush(_SH_C3);
		 	QPoint pR[4] = {
     			QPoint(x + _SH_P / 2, y + h - _SH_P / 2),
     			QPoint(x + _SH_P / 2 , y + h + _SH_P / 2),
     			QPoint(x + _SH_P / 2 - _L / _DEL, y + _L / _DEL + h + _SH_P / 2),
     			QPoint(x + _SH_P / 2 - _L / _DEL, y + _L / _DEL + h - _SH_P / 2)
 			};
 			painter.drawPolygon(pR, 4);

			// Торец
			painter.setBrush(_SH_C1);
			painter.drawRect(
				x - _L / _DEL - _SH_P / 2, 
				y + h + _L / _DEL - _SH_P / 2, 
				_SH_P, 
				_SH_P);
			
			painter.drawLine(x - _L / _DEL, y + _L / _DEL, x - _L / _DEL, y + h +  + _L / _DEL);
	
			break;
		}
		case(T_S): {	
			// Рисуем софиты
			painter.drawLine(x, y, x, y + h);
		
			// Рисуем собственно софит
			// Топ
			painter.setBrush(_S_C2);
		 	QPoint pT[4] = {
     			QPoint(x - _S_W / 2, y + h - _S_H / 2),
     			QPoint(x + _S_W / 2 , y + h - _S_H / 2),
     			QPoint(x + _S_W / 2 - _L / _DEL, y + _L / _DEL + h - _S_H / 2),
     			QPoint(x - _S_W / 2 - _L / _DEL, y + _L / _DEL + h - _S_H / 2)
 			};
 			painter.drawPolygon(pT, 4);

			// Боковина			
			painter.setBrush(_S_C3);
		 	QPoint pR[4] = {
     			QPoint(x + _S_W / 2, y + h - _S_H / 2),
     			QPoint(x + _S_W / 2 + _S_D, y + h + _S_H / 2),
     			QPoint(x + _S_W / 2 - _L / _DEL + _S_D, y + _L / _DEL + h + _S_H / 2),
     			QPoint(x + _S_W / 2 - _L / _DEL, y + _L / _DEL + h - _S_H / 2)
 			};
 			painter.drawPolygon(pR, 4);

			// Боковина			
			painter.setBrush(_S_C3);
		 	QPoint pB[6] = {
     			QPoint(x - _L / _DEL - _S_W / 2, 			y + h + _L / _DEL - _S_H / 2),
     			QPoint(x - _L / _DEL + _S_W / 2,			y + h + _L / _DEL - _S_H / 2),
     			QPoint(x - _L / _DEL + _S_W / 2 + _S_D, 	y + h + _L / _DEL + _S_H / 2),
     			QPoint(x - _L / _DEL + _S_W / 2, 			y + h + _L / _DEL + _S_H / 2 + _S_D),
     			QPoint(x - _L / _DEL - _S_W / 2,		 	y + h + _L / _DEL + _S_H / 2 + _S_D),
     			QPoint(x - _L / _DEL - _S_W / 2 - _S_D, 	y + h + _L / _DEL + _S_H / 2)
 			};
 			painter.drawPolygon(pB, 6);
			
			
			painter.drawLine(x - _L / _DEL, y + _L / _DEL, x - _L / _DEL, y + h +  + _L / _DEL);
			break;
		}
	}
	
	s->afterPainting();
}


