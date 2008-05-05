#ifndef SCENEPARAM_H_
#define SCENEPARAM_H_

// Цвета
#define		_C_BG		QColor(0, 0, 0)			// Задний фон 
#define		_C_FG		QColor(255, 255, 255)	// Передий фон 
#define		_C_MG		QColor(128, 128, 128)	// Полоски в таблице 
#define		_C_P_L		QColor(55, 55, 55)		// Обводка стенок
#define		_C_B_L		QColor(33, 33, 33)		// Заливка стенок
#define		_C_B_LF		QColor(44, 44, 44)		// Заливка пола
#define		_C_B_LB		QColor(33, 33, 55)		// Заливка бортика
#define		_C_P_P		QColor(122, 122, 122)		// Обводка невидимых стенок

// Цвета ячеек согласно состоянию
static QColor colorState[] = {
	QColor(0, 0, 0), 		// DS_NONE
	QColor(0, 66, 0),		// DS_PROCESS
	QColor(66, 0, 0), 		// DS_ALARM
	QColor(0, 0, 77), 		// DS_UPEND
	QColor(44, 0, 77), 		// DS_UPALARM
	QColor(0, 33, 77), 		// DS_DOWNEND
	QColor(0, 44, 77) 		// DS_DOWNALARM
};

// Координаты задней стенки и высоты бордюра
#define		_X		200				
#define		_Y		80
#define		_L		320
#define		_W		740
#define		_H		640
#define		_B		300

#define		_MAX	1000	// За эту границу не рисуем!

// Искажение при проекции
#define		_DEL		2	

// Координаты таблицы
#define		_T_X	1020
#define		_T_Y	40
#define		_T_W	320
#define		_T_H	984

// Шрифт таблицы
#define 	_T_FF				"Helvetica"
#define 	_T_FS				16
#define		_T_FT				QFont::Normal

// Насечки
#define 	_NS		10		// количество
#define		_NL		5		// длина

// Шрифт насечек
#define 	_T_NF				"Helvetica"
#define 	_T_NS				10
#define		_T_NT				QFont::Normal

// Отрисовка ИП 
#define		_IP_TW	20		// ширина
#define		_IP_TH	680		// высота					
#define		_IP_L	40		// запас на метку					
#define		_IP_W	4		// ширина блямбы
#define		_IP_H	8		// высота блямбы					

// Отрисовка штанкетов
#define		_SH_C1	QColor(140, 140 ,140)	// цвет торца
#define		_SH_C2	QColor(120, 120, 120)	// цвет боковины
#define		_SH_C3	QColor(160, 160, 160)	// цвет топа

#define		_SH_P	6			// сторона квадрата

// Отрисовка софитов
#define		_S_C1	QColor(140, 140 ,140)	// цвет торца
#define		_S_C2	QColor(120, 120, 120)	// цвет боковины
#define		_S_C3	QColor(160, 160, 160)	// цвет топа

#define		_S_W	20			// сторона квадрата
#define		_S_H	40			// сторона квадрата
#define		_S_D	5			// припуск

#endif /*SCENEPARAM_H_*/
