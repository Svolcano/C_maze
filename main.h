/*
* main.h (1.0)
* ��Ϸ��Դ����
*
* By Eric-JR Chen
* diamont1001@163.com
* 2011-3-18
*/

#ifndef MAIN_H
#define MAIN_H

#include "JR_Cursor.h"
#include "JR_KeyBoard.h"
#include "JR_Random.h"
#include "JR_timer.h"
#include "maze.h"

#define ROW 23
#define COL 29


/* ��Ϸ״̬ */
typedef enum _STATUS{
    /* ��ӭ   ��Ϸ   ��ͣ   ʤ�� ֹͣ  �˵�  �༭     LOAD��ͼ   save��ͼ */
    WELCOME, GAMING, PAUSE, WIN, STOP, MENU, EDITMAP, LOADMAP, SAVEMAP
}STATUS;

/* ���� */
typedef enum _DIRECTION{
    UP, LEFT, RIGHT, DOWN
}DIRECTION;

/* ��ĻԪ�� */
typedef struct _SHOWNODE{
    int x;
    int y;
    char text[3];
}SHOWNODE;


#endif
