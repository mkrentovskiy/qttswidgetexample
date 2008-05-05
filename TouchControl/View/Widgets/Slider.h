#ifndef SLIDER_H_
#define SLIDER_H_

#include <QWidget>
#include <QPixmap>
#include <QLabel>

#include "PicButton.h"

#include "../WidgetFabric.h"

#include "../../Variables.h"


class Slider : public QWidget
{
		Q_OBJECT
	
	public:
		Slider(QWidget *, WidgetControl *, QDomElement &, QDomElement &, WidgetFabric *);
								
		void setPosition(float p) { pos = range(p); calculate(); };
		float getPosition() { return pos; };
		
		float range(float f) {
			float r = f;
			if(f > max) r = max;
			if(f < min) r = min;	
			return r; 
		};

		void setMaxValue(float m) { max = m; }
		
	protected:
	    void paintEvent(QPaintEvent *event);
    	void calculate();

	private slots:
	    void stepUp();
    	void stepDown();
    	
    signals:
    	void valueChanged(float);
    	void valueChange(float);
		
	private: 
		QString					id;
	
		// Визуальные аспекты
		PicButton				*up;
		PicButton				*down;				
		QPixmap					*background;
		
		int						xs;
		int						ys;
		int						is;
		int						js;		
		int						yd;
		
		// Формальные аспекты
		float					min;
		float					max;
		float					step;		
		float					pos;						
};	


#endif /*SLIDER_H_*/
