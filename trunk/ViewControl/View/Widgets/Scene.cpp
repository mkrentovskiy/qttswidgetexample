#include <QtCore>
#include <QtSql>

#include "../../../Interaction/Database.h"

#include "Scene.h"
#include "SceneParam.h"

Scene::Scene(QWidget *parent) : QWidget(parent)
{
	move(0, 0);
	resize(MAXWIDTH, MAXHEIGHT);
		
	// Устанавливаем бэкграунд в чорний
	QPalette p;
	p.setColor(QPalette::Window, _C_BG);
	p.setColor(QPalette::Base, _C_BG);
	p.setColor(QPalette::AlternateBase, _C_BG);
	p.setColor(QPalette::Button, _C_BG);
	
	p.setColor(QPalette::WindowText, _C_FG);
	p.setColor(QPalette::Text, _C_FG);
	p.setColor(QPalette::ButtonText, _C_FG);
	p.setColor(QPalette::BrightText, _C_FG);
	
	p.setColor(QPalette::Light, _C_BG);
	p.setColor(QPalette::Midlight, _C_BG);
	p.setColor(QPalette::Dark, _C_BG);
	p.setColor(QPalette::Mid, _C_MG);
	p.setColor(QPalette::Shadow, _C_BG);
	
	
	setPalette(p);
	setAutoFillBackground(true); 
	
	Database db;
	QSqlQuery q = db.query("SELECT * FROM devices WHERE is_h='0' ORDER BY y");

	// Делаем таблицу
	table = new QTableWidget(q.size(), 3, this);
	table->move(_T_X, _T_Y);
	table->resize(_T_W, _T_H);
	
	// Говорим ей шрифт
	QFont f(_T_FF, _T_FS, _T_FT);
    table->setFont(f);
	
	// Говорим ей заголовки
	QStringList sl;
	sl << "Подъем" << "H, м  " << "V, м/c";
	table->setHorizontalHeaderLabels(sl);
	table->resizeColumnsToContents();
	
	table->setPalette(p);
	
	// Наполняем
	int i = 0;
	while(q.next()) {
		QTableWidgetItem *title = new QTableWidgetItem(q.value(_D_title).toString());
		QTableWidgetItem *height = new QTableWidgetItem("0.00");
		QTableWidgetItem *speed = new QTableWidgetItem("0.00");
			
		table->setItem(i, 0, title);
		table->setItem(i, 1, height);
		table->setItem(i, 2, speed);
		
		et[q.value(_D_id).toString()] = i;
		
		bool ok;
		SceneElement *se = new SceneElement(this);
		se->init(q.value(_D_title).toString(), 
			(float) q.value(_D_x).toDouble(&ok), 
			(float) q.value(_D_y).toDouble(&ok), 
			QColor(q.value(_D_color).toString()), 
			q.value(_D_type).toInt()); 
		el[q.value(_D_id).toString()] = se;
		
		i++;
	}
	
	table->clearFocus();
	
	show();
}


void Scene::paintEvent(QPaintEvent *)
{
	QPainter painter(this);	
	
	// Рисуем задний фон
	QBrush brush(_C_B_L);
	QPen pen(_C_P_L);
	// pen.setWidth(2);    	
	
	// дальняя стена
	QPoint pL[4] = {
     	QPoint(_X, _Y),
     	QPoint(_X + _W, _Y),
     	QPoint(_X + _W, _Y + _H),
     	QPoint(_X, _Y + _H)
 	};
 	// Пол
 	QPoint pB[4] = {
     	QPoint(_X , _Y + _H),
     	QPoint(_X + _W, _Y + _H),
     	QPoint(_X - (_L / _DEL) + _W, _Y + (_L / _DEL) + _H),
     	QPoint(_X - (_L / _DEL), _Y + (_L / _DEL) + _H)
 	};
 	// Бортик
 	QPoint pD[4] = {
     	QPoint(_X, _Y),
     	QPoint(_X, _Y + _B),
     	QPoint(_X - (_L / _DEL), _Y + (_L / _DEL) + _B),
     	QPoint(_X - (_L / _DEL), _Y + (_L / _DEL))
 	};
 	
	painter.setPen(pen);	
	painter.setBrush(brush);	
	painter.drawPolygon(pL, 4);
	painter.setBrush(_C_B_LF);	
	painter.drawPolygon(pB, 4);
	painter.setBrush(_C_B_LB);	
	painter.drawPolygon(pD, 4);
	
	// Насечки
	QPen wPen(_C_P_P);
	painter.setPen(wPen);	
	painter.setBrush(Qt::NoBrush);	

	// Говорим себе шрифт
	QFont fn(_T_NF, _T_NS, _T_NT);
    setFont(fn);
	
	for(int i = 0; i < _NS + 1; i++) {
		QString label = QString("%1").arg((PH_HEIGTH - (PH_HEIGTH * i / _NS )), 0, 'f', 1);
		painter.drawLine(_X + _W + _NL, _Y + (_H * i / _NS), _X + _W + 2 * _NL, _Y + (_H * i / _NS));
		painter.drawText(_X + _W + 3 * _NL, _Y + (_H * i / _NS) + (_T_NS / 2), label);
	}
	
	afterPainting();	
}

void Scene::afterPainting()
{
	QPainter painter(this);	

	QPen wPen(_C_P_P);
	painter.setPen(wPen);	
	painter.setBrush(Qt::NoBrush);	

	// Потолок	
	painter.drawLine(_X - (_L / _DEL), _Y + (_L / _DEL), _X - (_L / _DEL) + _W, _Y + (_L / _DEL));
	painter.drawLine(_X - (_L / _DEL) + _W, _Y + (_L / _DEL), _X + _W, _Y);
	painter.drawLine(_X - (_L / _DEL) + _W, _Y + (_L / _DEL), _X - (_L / _DEL) + _W, _Y + _H + (_L / _DEL));	
}

/*
 *  Реакция на изменения состояния устройства
 */
void Scene::stateChanged(QString did, Speed sp, Height h, DeviceState ds)
{
	if(el.contains(did)) {
		el[did]->setHeight(h);
		el[did]->repaint();

		QTableWidgetItem *i;
		
		table->setCurrentCell(et[did], 0);
		i = table->currentItem();
		i->setBackgroundColor(colorState[ds]);
		
		table->setCurrentCell(et[did], 1);
		i = table->currentItem();
		i->setBackgroundColor(colorState[ds]);
		i->setText(QString("%1").arg(sp, 0, 'f', 2));
		
		table->setCurrentCell(et[did], 2);
		i = table->currentItem();
		i->setBackgroundColor(colorState[ds]);
		i->setText(QString("%1").arg(h, 0, 'f', 2));
	}
}


/*
 * 	Реакция на требование об обновлении параметров отображения
 */
void Scene::paramsChanged()
{
}

