#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QWidget>

#include "WidgetControl.h"

class MainWindow : public QWidget
{
	Q_OBJECT
	
	private:
		WidgetControl *wc;
		
		QAction *onHalt;
		QAction *onGo;
		
	public:
		MainWindow();
		
		WidgetControl*	getWidgetControl() { return wc; };
};

#endif /*MAINWINDOW_H_*/
