#ifndef SCENE_H_
#define SCENE_H_

#include <QtCore>
#include <QtGui>

#include "SceneElement.h"

#include "../../Variables.h"

class Scene : public QWidget
{
		Q_OBJECT
	
		QTableWidget *table;

		QHash<QString, SceneElement *> el;
		QHash<QString, int> et;

	protected:
		void paintEvent(QPaintEvent *);
	
	public:
		Scene(QWidget *);
		
		void afterPainting();
		
		void stateChanged(QString, Speed, Height, DeviceState);
		void paramsChanged();
};

#endif /*SCENE_H_*/
