#ifndef 	VARIABLES_H_
#define 	VARIABLES_H_

#define		DEBUG				1
//#define		RELEASE				1

#define		NULLVALUE			""


/*
 * Параметры взаимодействия систем
 */
#define		CONTROL_PORT		7777
#define 	DEVICES_PORT		8888

/*
 *	Визуальные параметры экрана
 */

#define		MAXWIDTH			1280
#define		MAXHEIGHT			1024

/*
 *	Шрифт 
 */

#define 	FONTFACE				"Helvetica"
#define 	FONTSIZE				16
#define		FONTTYPE				QFont::Bold

/* 
 * 	Служебные ресурсы для описания интерфейса
 */

#define 	INTERFACE			":/interface.xml"
#define 	FABRIC				":/fabric.xml"
#define 	DATABASE			":/database.xml"

/*
 *	Жестко прописанные состояния PicButton  
 */
 
#define		PB_NORMAL				"normal"
#define		PB_SELECTED				"selected"
#define		PB_DISABLED				"disabled"
#define		PB_PRESSED				"pressed"
#define		PB_NULL					"null" 
#define		PB_FIN					"fin"
#define		PB_ALARM				"alarm"

/*
 * 	Параметры слайдера
 */

#define		S_AR_INTERVAL			30
#define		S_COLOR					QColor(0, 204, 102)
			
/*
 * 	Параметры клавиатуры
 */			
			
#define		K_MAXKEYBOARDNUM		5			

typedef unsigned char TypeState;	// Тип выбранной серии устройств

#define		TS_NONE					0
#define		TS_SH					1				
#define		TS_IP					2
#define		TS_Z					3
#define		TS_S					4

typedef	unsigned char VHState;		// Значение параметра "Скорость/Высота" 

#define		VHS_NONE				0
#define		VHS_V					1
#define		VHS_H					2
			
/*
 * 	Параметры контрольной линии устройства
 */		

typedef	unsigned char DeviceState;

#define		DS_NONE					0
#define		DS_PROCESS				1
#define		DS_ALARM				2
#define		DS_UPEND				3
#define		DS_UPALARM				4
#define		DS_DOWNEND				5
#define		DS_DOWNALARM			6
	
/*
 * 	Параметры, кодирующие физические величины
 */	
 
typedef float Height;
typedef float Speed;			
typedef unsigned char Direction;

#define		D_NONE					0
#define		D_UP					1
#define		D_DOWN					2
#define		D_OPEN					1
#define		D_CLOSE					2

/*
 * Структура ограничений параметров устройства
 */
 
typedef	struct DEVICELIMITS {
 	float	maxv;	
 	float	minh;
 	float	maxh;
 	bool	h;
} DeviceLimits;

/*
 * Команды управления
 */

#define		C_SPEED				10
#define		C_MASTERSPEED		11
#define		C_DIRECTION			12
#define		C_HEIGHT			13
#define		C_START				14
#define		C_STOP				15
#define		C_TOTALSTART		16
#define		C_TOTALSTOP			17

/*
 * 	Шоткаты 
 */

#define		SHOTCUT_HALT		Qt::SHIFT
#define		SHOTCUT_GO			Qt::CTRL

/*
 *  Задержки, мс
 */
			
#define		TO_BTWCHECKS			30	// между проверками состояния

/*
 * 	Определим здесь параметры таблицы devices дабы потом не переделывать
 */

#define		_D_id					0
#define 	_D_title				1
#define		_D_ip					2
#define		_D_port					3
#define 	_D_x					4
#define 	_D_y					5
#define 	_D_color				6
#define 	_D_comment				7
#define		_D_maxv					8
#define		_D_minh					9
#define		_D_maxh					10
#define		_D_is_h					11
#define		_D_type					12

// Варианты типов
#define		T_IP					1
#define		T_SH					2
#define		T_S						3
#define		T_Z						4
						
/*
 *  ПАРАМЕТРЫ ПРОСМОТРА
 *  для ViewControl
 */

			// Физические размеры
#define		PH_WIDTH				40.1	// ширина сцены
#define		PH_HEIGTH				20.2	// высота от сцены до колосников
#define		PH_LENGTH				30.2	// глубина сцены
						
		
#endif 		/*VARIABLES_H_*/
