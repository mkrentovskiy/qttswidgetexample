#include <QtGui>
#include <QCursor>

#include "MainWindow.h"
#include "WidgetControl.h"

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
	
	QPixmapCache::setCacheLimit(32768);
					
	wc = WidgetControl::getInstance();
	wc->init(this);
	
	// действие для выключения
	onHalt = new QAction(this);
    onHalt->setShortcut(SHOTCUT_HALT);
    connect(onHalt, SIGNAL(triggered()), wc, SLOT(isHalt()));
	addAction(onHalt);

	// действие для старта/стопа
	onGo = new QAction(this);
	onGo->setCheckable(true);
    onGo->setShortcut(SHOTCUT_GO);
    connect(onGo, SIGNAL(triggered(bool)), wc, SLOT(isGo(bool)));
	addAction(onGo);		
}
