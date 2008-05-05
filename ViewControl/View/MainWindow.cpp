#include <QtGui>
#include <QCursor>

#include "MainWindow.h"
#include "SceneViewControl.h"

#include "../Variables.h"

MainWindow::MainWindow()
{
	QLocale::setDefault(QLocale(QLocale::Russian, QLocale::RussianFederation));
	
	QFont f(FONTFACE, FONTSIZE, FONTTYPE);
    setFont(f);
	
	resize(MAXWIDTH, MAXHEIGHT);		
	setFocusPolicy(Qt::NoFocus);
	
	#ifdef RELEASE
		setCursor(Qt::BlankCursor);
	#endif	
	
	#ifdef RELEASE
		setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowMaximizeButtonHint);
	#endif
	#ifdef DEBUG
		setWindowFlags(Qt::Window);
	#endif
			
	svc = SceneViewControl::getInstance();
	svc->init(this);		
}
