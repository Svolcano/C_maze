/*
* maze.h (1.0)
* �����Թ�С��Ϸ�����ݽṹ��ӿڵ�����
*
* By Eric-JR Chen
* diamont1001@163.com
* 2011-3-18
*/

#ifndef MAZE_H
#define MAZE_H

extern const char *BG;   //����ͼ��
extern const char *BAR;  //�ϰ���ͼ��
extern const char *MAN;  //����ͼ��
extern const char *EXIT; //����ͼ��

/* �༭��ͼ��� */
void EditMaped(void);

/* �����ͼ */
int saveMap(int index);

/* ��ȡ��ͼ */
int loadMap(int index);

/* ����ϰ��� */
void clearBar(void);

/*
 * ��ʼ���ϰ���
 * flag��ѡ���ͼ���ɷ�ʽ
 */
int initBar(int flag);

/* ��ʼ������ */
void initMan(void);

/* ������ʾ */
void showMan(void);

/* ��ʼ��EDIT��� */
void initEditCursor(void);

/* EDIT�����ʾ */
void showEditCursor(void);

/* ��Ϸ��ʼʱ����Ⱦ��Ϸ���� */
void drawBars(void);

/* ��ʼ��maze��Ϸ��Դ */
void initMaze(void);

/* �ƶ����� */
int moveMan(int dir);

/* �ƶ�EDIT��� */
int moveEditCursor(int dir);

/* �ı䵱ǰEDIT���TEXT */
void setEditText(void);

/* EDIT���Զ����ɵ�ͼ */
void radomEdit(void);

#endif  //maze.h
