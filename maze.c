/*
* maze.c (1.0)
* �����Թ�С��Ϸ�Ľӿڵ�ʵ��
*
* By Eric-JR Chen
* diamont1001@163.com
* 2011-3-18
*/

#include <stdio.h>
#include "maze.h"
#include "main.h"

static short BARS[ROW][COL];    //�ϰ�������(1:BG, 0:BAR)
static short VALUE[(ROW/2)*(COL/2)];   //ͼ�ĸ����ڵ�(0:δ����, 1:��������, 2:�ѷ���)
static short FLAG[4];           //���ѡ����
static SHOWNODE CurMan;         //��ǰ����
static SHOWNODE CurEdit;        //��ǰ�༭λ��
static int IsEditMap = 0;       //�Ƿ��б༭��ͼ


/** ******************** ��ͼ������������ɵ�ͼ ************************ **/
/** �ο�: http://hi.baidu.com/%B4%F4%BA%CD%B9%D4%B5%C4%D0%A1%CC%EC%B5%D8/blog/item/98af8518e37c05b04aedbca6.html **/

/* ��ʼ��ͼ�ĸ����ڵ� */
void initVALUE(void){
    int i = 0;
    for(i=0; i<(ROW/2)*(COL/2); i++){
        VALUE[i] = 0;
    }
}
/* ��ͨA����B�� */
void linkPath(int a, int b){
    int x1 = (a % (COL/2)) * 2 + 1;
    int x2 = (b % (COL/2)) * 2 + 1;
    int y1 = (a / (COL/2)) * 2 + 1;
    int y2 = (b / (COL/2)) * 2 + 1;
    int x = (x1 + x2) / 2;
    int y = (y1 + y2) / 2;
    BARS[y][x] = 1;
}
/* ���A��ĸ����ھӵ�״�� */
int checkNeighbour(int a, int dir){
    int col = COL / 2;
    int row = ROW / 2;
    int index = 0;

    switch(dir){
     case 0:    //��
        index = a - col;
        if(index > 0 && !VALUE[index]) return (index);
        break;
     case 1:    //��
        index = a - 1;
        if((a % col) != 0 && !VALUE[index]) return (index);
        break;
     case 2:    //��
        index = a + 1;
        if((index % col) != 0 && !VALUE[index]) return (index);
        break;
     case 3:    //��
        index = a + col;
        if(index < (row * col) && !VALUE[index]) return (index);
        break;
    }
    return 0;
}
/* ���ҷ������� */
void getRadom(int time){
    int i =0, j = 0, k = 0;
    int temp = 0;
    for(i=0; i<4; i++)
        FLAG[i] = i;
    for(i=0; i<time; i++){
        for(j=0; j<4; j++){
            k = JR_randomIn(3);
            if(k != j){
                temp = FLAG[j];
                FLAG[j] = FLAG[k];
                FLAG[k] = temp;
            }
        }
    }
}
/* ��A�㿪ʼ���� */
void visitPoint(int a){
    int i = 0, node = 0;
    int x = 0, y = 0;
    if(VALUE[a]) return ;

    x = (a % (COL/2)) * 2 + 1;
    y = (a / (COL/2)) * 2 + 1;
    BARS[y][x] = 1;
    VALUE[a] = 2;

    getRadom(JR_randomRange(1, 10));
    for(i=0; i<4; i++){
        if((node = checkNeighbour(a, FLAG[i])) != 0){
            linkPath(a, node);
            visitPoint(node);
        }
    }
}
/** ******************** ��ͼ������������ɵ�ͼ ************************ **/


/* �༭��ͼ��� */
void EditMaped(void){
    IsEditMap = 1;
}

/* �����ͼ */
int saveMap(int index){
    int i = 0, j = 0;
    char filename[20];
    FILE *tp = NULL;
    sprintf(filename, "batch%d", index);
    if((tp = fopen(filename, "w+")) == NULL){
        return 0;
    }else {
        for(i=0; i<ROW; i++){
            for(j=0; j<COL; j++){
                fprintf(tp, "%d", BARS[i][j]);
            }
        }
        fclose(tp);
    }
    return 1;
}

/* ��ȡ��ͼ */
int loadMap(int index){
    int i = 0, j = 0;
    char filename[20];
    FILE *tp = NULL;
    sprintf(filename, "batch%d", index);
    if((tp = fopen(filename, "r")) == NULL){
        return 0;
    }else {
        for(i=0; i<ROW; i++){
            for(j=0; j<COL; j++){
                fscanf(tp, "%1d", &BARS[i][j]);
            }
        }
        fclose(tp);
    }
    return 1;
}

/* ����ϰ��� */
void clearBar(void){
    int i = 0, j = 0;
    for(i=0; i<ROW; i++){
        for(j=0; j<COL; j++){
            BARS[i][j] = 1;
        }
    }
}

/* ���ɵ�ͼ */
int createMap(int flag){
    switch(flag){
     case 1:
        initVALUE();
        visitPoint(0);
        break;
     default:
        break;
    }
    return 1;
}

/*
 * ��ʼ���ϰ���
 * flag��ѡ���ͼ���ɷ�ʽ
 */
int initBar(int flag){
    int i = 0, j = 0;
    if(IsEditMap){  //�༭��ͼ��������������
        IsEditMap = 0;
        return 1;
    }

    //��ʼ��Ϊ0
    for(i=0; i<ROW; i++){
        for(j=0; j<COL; j++){
            BARS[i][j] = 0;
        }
    }

    return createMap(flag);
}

/* ��ʼ������ */
void initMan(void){
    CurMan.x = 2;
    CurMan.y = 1;
    strcpy(CurMan.text, MAN);
}

/* ������ʾ */
void showMan(void){
    showInBuff(CurMan);
}

/* ��ʼ��EDIT��� */
void initEditCursor(void){
    CurEdit.x = 0;
    CurEdit.y = 0;
    strcpy(CurEdit.text, BG);
}

/* EDIT�����ʾ */
void showEditCursor(void){
    JR_SetCursor(CurEdit.x, CurEdit.y);
}

/* ��Ϸ��ʼʱ����Ⱦ��Ϸ���� */
void drawBars(void){
    int i = 0, j = 0;
    SHOWNODE node;
    for(i=0; i<ROW; i++){
        for(j=0; j<COL; j++){
            node.x = j * 2;
            node.y = i;
            if(BARS[i][j])
                strcpy(node.text, BG);
            else
                strcpy(node.text, BAR);
            showInBuff(node);
        }
    }
    //��ʾ����
    node.x = COL * 2 - 4;
    node.y = ROW - 2;
    strcpy(node.text, EXIT);
    showInBuff(node);
}

/* ��ʼ��maze��Ϸ��Դ */
void initMaze(void){
    initBar(1);
    drawBars();

    initMan();
    showMan();
}

/* ����node�Ƿ�Ϸ� */
int checkMan(SHOWNODE node){
    if(node.x == COL * 2 - 4 && node.y == ROW - 2){   //�Ƿ��߳�
        return 99;
    }else if(node.x < 0 || node.x >= COL*2
       || node.y < 0 || node.y >= ROW
       || !BARS[node.y][node.x/2]
       ) return 0;
    return 1;
}

/* �ƶ����� */
int moveMan(int dir){
    int result = 0;
    SHOWNODE node;
    node.x = CurMan.x;
    node.y = CurMan.y;
    strcpy(node.text, MAN);
    switch(dir){
      case 0:   //UP
        node.y --;
      break;
      case 1:   //LEFT
        node.x -= 2;
      break;
      case 2:   //RIGHT
        node.x += 2;
      break;
      case 3:   //DOWN
        node.y ++;
      break;
    }
    result = checkMan(node);
    if(result){
        strcpy(CurMan.text, BG);
        showInBuff(CurMan);
        CurMan.x = node.x;
        CurMan.y = node.y;
        strcpy(CurMan.text, node.text);
        showInBuff(CurMan);
        return result;
    }
    return 0;
}

/* �ƶ�EDIT��� */
int moveEditCursor(int dir){
    SHOWNODE node;
    node.x = CurEdit.x;
    node.y = CurEdit.y;
    strcpy(node.text, CurEdit.text);
    switch(dir){
      case 0:   //UP
        node.y --;
      break;
      case 1:   //LEFT
        node.x -= 2;
      break;
      case 2:   //RIGHT
        node.x += 2;
      break;
      case 3:   //DOWN
        node.y ++;
      break;
    }
    if(node.x >= 0 && node.x < COL*2 && node.y >= 0 && node.y < ROW){
        CurEdit.x = node.x;
        CurEdit.y = node.y;
        strcpy(CurEdit.text, BG);
        JR_SetCursor(CurEdit.x, CurEdit.y);
        return 1;
    }
    return 0;
}

/* �ı䵱ǰEDIT���TEXT */
void setEditText(void){
    if(!strcmp(CurEdit.text, BG)){
        strcpy(CurEdit.text, BAR);
        BARS[CurEdit.y][CurEdit.x] = 1;
    }else
        strcpy(CurEdit.text, BG);
        BARS[CurEdit.y][CurEdit.x/2] = 0;
    showInBuff(CurEdit);
}

/* EDIT���Զ����ɵ�ͼ */
void radomEdit(void){
    initBar(1);
    drawBars();
}
