#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QWidget>

#include "SceneViewControl.h"

class MainWindow : public QWidget
{
	Q_OBJECT
	
	private:
		SceneViewControl *svc;
		
	public:
		MainWindow();
		
		SceneViewControl*	getSceneViewControl() { return svc; };
};

#endif /*MAINWINDOW_H_*/
