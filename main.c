/*
* main.c (1.0)
* ��Ϸ���ļ�
*
* By Eric-JR Chen
* diamont1001@163.com
* 2011-3-18
*/

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/* *************** ��Ϸ��Դ *************** */
const char *BG = "��";   //����ͼ��"��"
const char *BAR = "��";  //�ϰ���ͼ��"��"
const char *MAN = "�I"; //����ͼ��"�I"
const char *EXIT = "��"; //����ͼ��"��"

/* *************** ��Ϸ״̬ ************** */
static STATUS sys_gs;       //��Ϸ״̬
static int curtime = 0;     //��Ϸʱ��
static int totalSteps = 0;  //�߹��Ĳ���

/* ************ MENU *********** */
static int MenuIndex = 1;
const int MainMenuNum = 4;  //���˵�������
const int SaveMenuNum = 11; //�����ͼ�˵�������

/* ************** ��Ļ���� *************** */
static int JR_isRefresh = 0;            //������Ļˢ��
static SHOWNODE showBuff[ROW*COL*2];    //������
static int BuffIndex = 0;


/* ��Ϸ�������� */
void clear(void){
    int i = 0;
    JR_SetCursorStart();
    for(i=0; i<ROW+3; i++)
        printf("\t\t\t\t\t\t\t\t\t       \n");
    JR_SetCursor(0, ROW+1);
}

/* ��һ��NODE�ŵ��������� */
void showInBuff(SHOWNODE buffer){
    showBuff[BuffIndex].x = buffer.x;
    showBuff[BuffIndex].y = buffer.y;
    strcpy(showBuff[BuffIndex].text, buffer.text);
    BuffIndex ++;
}

/* SHOW WELCOME */
void showWelcome(void){
    printf("\n\n");
    printf("\t\t************ JR_Maze 1.0.1 ***************\n");
    printf("\t\t*       Welcome to Gobang Gameing.       *\n");
    printf("\t\t*        By Eric-JR Chen 2011-3          *\n");
    printf("\t\t*          diamont1001@163.com           *\n");
    printf("\t\t*           ��Enter�� Menu               *\n");
    printf("\t\t*           �� Esc �� Exit               *\n");
    printf("\t\t******************************************\n");
}

/* ��ʾ������ʾ */
void showTips(void){
    int y = 1;
    if(sys_gs != GAMING) return ;
    JR_SetCursor(COL*2+1, y++);
    printf("Time : %d s", curtime);
    JR_SetCursor(COL*2+1, y++);
    printf("Steps: %d\t", totalSteps);
    y ++;
    JR_SetCursor(COL*2, y++);
    printf("��������W��: Up ");
    JR_SetCursor(COL*2, y++);
    printf("��������A��: Left ");
    JR_SetCursor(COL*2, y++);
    printf("��������S��: Down ");
    JR_SetCursor(COL*2, y++);
    printf("��������D��: Right ");
    y ++;
    JR_SetCursor(COL*2, y++);
    printf("�� F10 �� : Save Map");
    JR_SetCursor(COL*2, y++);
    printf("�� Esc �� : Back");
}

/* ��ʾEDIT��ʾ */
void showEditTips(void){
    int y = 1;
    JR_SetCursor(COL*2, y++);
    printf("��������W��: Up ");
    JR_SetCursor(COL*2, y++);
    printf("��������A��: Left ");
    JR_SetCursor(COL*2, y++);
    printf("��������S��: Down ");
    JR_SetCursor(COL*2, y++);
    printf("��������D��: Right ");
    y ++;
    JR_SetCursor(COL*2, y++);
    printf("��Space�� : Change");
    JR_SetCursor(COL*2, y++);
    printf("��Enter�� : StartGame");
    JR_SetCursor(COL*2, y++);
    printf("�� F1  �� : Radom");
    JR_SetCursor(COL*2, y++);
    printf("�� F10 �� : Save Map");
    JR_SetCursor(COL*2, y++);
    printf("�� Esc �� : Back");
}

void setGameSpeed(void){
    stopTimer();
    setTimer(500);
    startTimer();
}

/* ��ʼ�༭��ͼ */
void startEdit(void){
    sys_gs = EDITMAP;
    clear();
    clearBar();
    drawBars();
    showEditTips();
    initEditCursor();
    showEditCursor();
    JR_isRefresh = 1;
}

/* �༭��ͼ��ʾ */
void showEdit(void){
    int i = 0;
    for(i=0; i<BuffIndex; i++){
        JR_SetCursor(showBuff[i].x, showBuff[i].y);
        printf("%s", showBuff[i].text);
    }
    BuffIndex = 0;
    showEditCursor();
}

/* ��ʼ�����ͼ */
void startSaveMap(void){
    sys_gs = SAVEMAP;
    clear();
    MenuIndex = 1;
    JR_isRefresh = 1;
}

/* �����ͼ�˵���ʾ */
void showSaveMap(void){
    int i = 0;
    JR_SetCursorStart();
        printf("\n\n");
    printf("\t\t***************** SAVE MAP ***************\n");
    for(i=0; i<10; i++){
        printf("\t\t*               Batch[%02d]                *\n", i + 1);
    }
    printf("\t\t*               Back                     *\n");
    printf("\t\t******************************************\n");

    JR_SetCursor(29 ,MenuIndex+2);
    printf("=>");
}

/* ��ʼ�����ͼ */
void startLoad(void){
    sys_gs = LOADMAP;
    clear();
    MenuIndex = 1;
    JR_isRefresh = 1;
}

/* ��ȡ��ͼ�˵���ʾ */
void showLoadMap(void){
    int i = 0;
    JR_SetCursorStart();
        printf("\n\n");
    printf("\t\t***************** LOAD MAP ***************\n");
    for(i=0; i<10; i++){
        printf("\t\t*               Batch[%02d]                *\n", i + 1);
    }
    printf("\t\t*               Back                     *\n");
    printf("\t\t******************************************\n");

    JR_SetCursor(29 ,MenuIndex+2);
    printf("=>");
}

/* ��ʼ��ʾ�˵� */
void startMenu(int index){
    sys_gs = MENU;
    MenuIndex = index > MainMenuNum ? 1 : index;
    clear();
    JR_isRefresh = 1;
}

/* �˵���ʾ */
void showMenu(void){
    JR_SetCursorStart();
    printf("\n\n");
    printf("\t\t****************** MENU ******************\n");
    printf("\t\t*               Start Game               *\n");
    printf("\t\t*               Edit Map.                *\n");
    printf("\t\t*               Load Map.                *\n");
    printf("\t\t*               Exit.                    *\n");
    printf("\t\t******************************************\n");

    JR_SetCursor(29 ,MenuIndex+2);
    printf("=>");
}

/* ��Ϸ��������ʾ */
void showGame(void){
    int i = 0;
    for(i=0; i<BuffIndex; i++){
        JR_SetCursor(showBuff[i].x, showBuff[i].y);
        printf("%s", showBuff[i].text);
    }

    BuffIndex = 0;

    if(sys_gs == WIN){
        sys_gs = STOP;
        JR_isRefresh = 1;
    }
}

/* ��Ļ��Ⱦ */
void Render(){
    JR_isRefresh = 0;
    switch(sys_gs){
        case WELCOME:
            showWelcome();
            JR_SetCursor(0, ROW+1);
            break;
        case MENU:
            showMenu();
            JR_SetCursor(0, ROW+1);
            break;
        case EDITMAP:
            showEdit();
            break;
        case SAVEMAP:
            showSaveMap();
            JR_SetCursor(0, ROW+1);
            break;
        case LOADMAP:
            showLoadMap();
            JR_SetCursor(0, ROW+1);
            break;
        case GAMING:
        case WIN:
            showGame();
            JR_SetCursor(0, ROW+1);
            break;
        case PAUSE:
            JR_SetCursor(0, ROW);
            printf("Pause! Press ��Enter�� to Continue.\t\t\t\t");
            JR_SetCursor(0, ROW+1);
            break;
        case STOP:
            JR_SetCursor(0, ROW);
            printf("You Win! Press ��Enter�� to Restart or ��Esc�� to back to Menu.\t\t");
            JR_SetCursor(0, ROW+1);
            break;
    }
}

/* ��ʼ����Ϸ���ݣ���ʼ��Ϸ */
void startGame(void){
    BuffIndex = 0;
    JR_isRefresh = 1;
    sys_gs = GAMING;

    clear();
    initMaze();
    showTips();

    curtime = 0;
    totalSteps = 0;
    setTimer(1000);
    startTimer();

    JR_SetCursor(0, ROW);
    printf("\t\t\t\t\t\t\t");
}

void winGame(void){
    sys_gs = WIN;
    JR_isRefresh = 1;
}

void exitGame(void){
    clear();
    exit(0);
}

void init(void){
    sys_gs = WELCOME;
    JR_isRefresh = 1;
}

void UpdateKeys(int ms){
    static int ticks = 0;
    int t = JR_GetTicks();
    if(t - ticks < ms) return ;

    ticks = t;
    if(JR_AnyKeys()){
        switch(sys_gs){
         case WELCOME:
            if(JR_IsKeyDown(JR_KEY_ESC)){
                exitGame();
            }else if(JR_IsKeyDown(JR_KEY_ENTER)){
                startMenu(1);
            }
            break;
         case MENU:
            if(JR_IsKeyDown(JR_KEY_UP) || JR_IsKeyDown('w') || JR_IsKeyDown('W')){     //��
                MenuIndex --;
                if(MenuIndex <= 0)
                    MenuIndex = MainMenuNum;
                JR_isRefresh = 1;
            }else if(JR_IsKeyDown(JR_KEY_DOWN) || JR_IsKeyDown('s') || JR_IsKeyDown('S')){   //��
                MenuIndex ++;
                if(MenuIndex > MainMenuNum)
                    MenuIndex = 1;
                JR_isRefresh = 1;
            }else if(JR_IsKeyDown(JR_KEY_ENTER)){
                switch(MenuIndex){
                 case 1:    //Start
                    startGame();
                    break;
                 case 2:    //Edit
                    startEdit();
                    break;
                 case 3:    //Load
                    startLoad();
                    break;
                 case 4:    //Exit
                    exitGame();
                    break;
                }
            }
            break;
         case GAMING:
            if(JR_IsKeyDown(JR_KEY_ESC)){
                startMenu(1);
            }else if(JR_IsKeyDown(JR_KEY_ENTER)){
                sys_gs = PAUSE;
                JR_isRefresh = 1;
            }else if(JR_IsKeyDown(JR_KEY_UP) || JR_IsKeyDown('w') || JR_IsKeyDown('W')){     //��
                int result = moveMan(UP);
                if(result == 99){
                    winGame();
                    return ;
                }else if(result){
                    totalSteps ++;
                    JR_isRefresh = 1;
                }
            }else if(JR_IsKeyDown(JR_KEY_DOWN) || JR_IsKeyDown('s') || JR_IsKeyDown('S')){   //��
                int result = moveMan(DOWN);
                if(result == 99){
                    winGame();
                    return ;
                }else if(result){
                    totalSteps ++;
                    JR_isRefresh = 1;
                }
            }else if(JR_IsKeyDown(JR_KEY_LEFT) || JR_IsKeyDown('a') || JR_IsKeyDown('A')){   //��
                int result = moveMan(LEFT);
                if(result == 99){
                    winGame();
                    return ;
                }else if(result){
                    totalSteps ++;
                    JR_isRefresh = 1;
                }
            }else if(JR_IsKeyDown(JR_KEY_RIGHT) || JR_IsKeyDown('d') || JR_IsKeyDown('D')){  //��
                int result = moveMan(RIGHT);
                if(result == 99){
                    winGame();
                    return ;
                }else if(result){
                    totalSteps ++;
                    JR_isRefresh = 1;
                }
            }else if(JR_IsKeyDown(JR_KEY_F10)){ //save��ͼ
                startSaveMap();
            }
            break;
         case PAUSE:
            if(JR_IsKeyDown(JR_KEY_ENTER) || JR_IsKeyDown(JR_KEY_ESC)){   //Resume
                JR_SetCursor(0, ROW);
                printf("\t\t\t\t\t\t\t");
                sys_gs = GAMING;
                JR_isRefresh = 1;
            }
            break;
         case STOP:
            if(JR_IsKeyDown(JR_KEY_ENTER)){ //reStart
                startGame();
            }else if(JR_IsKeyDown(JR_KEY_ESC)){
                startMenu(1);
            }
            break;
         case EDITMAP:
            if(JR_IsKeyDown(JR_KEY_UP) || JR_IsKeyDown('w') || JR_IsKeyDown('W')){     //��
                moveEditCursor(UP);
            }else if(JR_IsKeyDown(JR_KEY_DOWN) || JR_IsKeyDown('s') || JR_IsKeyDown('S')){   //��
                moveEditCursor(DOWN);
            }else if(JR_IsKeyDown(JR_KEY_LEFT) || JR_IsKeyDown('a') || JR_IsKeyDown('A')){   //��
                moveEditCursor(LEFT);
            }else if(JR_IsKeyDown(JR_KEY_RIGHT) || JR_IsKeyDown('d') || JR_IsKeyDown('D')){  //��
                moveEditCursor(RIGHT);
            }else if(JR_IsKeyDown(JR_KEY_SPACE)){   //ȷ���༭��ǰλ��
                setEditText();
                JR_isRefresh = 1;
            }else if(JR_IsKeyDown(JR_KEY_ENTER)){   //����༭�������ʼ��Ϸ
                EditMaped();
                startGame();
            }else if(JR_IsKeyDown(JR_KEY_F1)){ //Radom���ɵ�ͼ
                radomEdit();
                JR_isRefresh = 1;
            }else if(JR_IsKeyDown(JR_KEY_F10)){ //save��ͼ
                startSaveMap();
            }else if(JR_IsKeyDown(JR_KEY_ESC)){
                startMenu(1);
            }
            break;
         case SAVEMAP:
            if(JR_IsKeyDown(JR_KEY_UP) || JR_IsKeyDown('w') || JR_IsKeyDown('W')){     //��
                MenuIndex --;
                if(MenuIndex <= 0)
                    MenuIndex = SaveMenuNum;
                JR_isRefresh = 1;
            }else if(JR_IsKeyDown(JR_KEY_DOWN) || JR_IsKeyDown('s') || JR_IsKeyDown('S')){   //��
                MenuIndex ++;
                if(MenuIndex > SaveMenuNum)
                    MenuIndex = 1;
                JR_isRefresh = 1;
            }else if(JR_IsKeyDown(JR_KEY_ENTER)){
                if(MenuIndex >=1 && MenuIndex <= 10){   //save
                    if((saveMap(MenuIndex)) == 1){
                        JR_SetCursor(0, ROW+1);
                        printf("Save Map is OK. batch[%02d]", MenuIndex);
                    }else{
                        JR_SetCursor(0, ROW+1);
                        printf("Error, please check. batch[%02d]", MenuIndex);
                    }
                }else if(MenuIndex == 11){  //back to Edit
                    sys_gs = MENU;
                    MenuIndex = 1;
                    clear();
                    JR_isRefresh = 1;
                }
            }
            break;
         case LOADMAP:
            if(JR_IsKeyDown(JR_KEY_UP) || JR_IsKeyDown('w') || JR_IsKeyDown('W')){     //��
                MenuIndex --;
                if(MenuIndex <= 0)
                    MenuIndex = SaveMenuNum;
                JR_isRefresh = 1;
            }else if(JR_IsKeyDown(JR_KEY_DOWN) || JR_IsKeyDown('s') || JR_IsKeyDown('S')){   //��
                MenuIndex ++;
                if(MenuIndex > SaveMenuNum)
                    MenuIndex = 1;
                JR_isRefresh = 1;
            }else if(JR_IsKeyDown(JR_KEY_ENTER)){
                if(MenuIndex >=1 && MenuIndex <= 10){   //load
                    if((loadMap(MenuIndex)) == 1){
                        EditMaped();
                        startGame();
                    }else{
                        JR_SetCursor(0, ROW+1);
                        printf("Error, please check. batch[%02d]", MenuIndex);
                    }
                }else if(MenuIndex == 11){
                    startMenu(1);
                }
            }
            break;
        }
        showTips();
    }
}

/* ÿ��interval����һ�� */
void mainTimer(void){
    if(sys_gs == GAMING){
        JR_isRefresh = 1;
        curtime ++;
    }
    showTips();
}

int main()
{
    init();
    while(1){
        UpdateKeys(3);
        if(JR_isRefresh){ //����ˢ����Ļ
            Render();
        }
        ontimer();
    }
    return 0;
}
