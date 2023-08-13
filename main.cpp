/*
* �����ռ�
* 1.��������Ŀ������Ŀģ�壩ʹ��VS������汾
* 2.�����ز�
* 3.ʵ���ʼ����Ϸ����
* 4.ʵ����Ϸ�����Ĺ�����
* 5.ʵ�ֹ������е�ֲ�￪��
*/

#include<stdio.h>
#include<graphics.h> //easyxͼ�ο��ͷ�ļ�����Ҫ��װ
#include"tools.h"

#define WIN_WIDTH 900
#define WIN_HEIGHT 600

enum {WAN_DOU,XIANG_RI_KUI,ZHI_WU_COUNT};

IMAGE imgBg;//��ʾ����ͼƬ
IMAGE imgBar;//������
IMAGE imgCards[ZHI_WU_COUNT];//ֲ�￨��
IMAGE* imgZhiWu[ZHI_WU_COUNT][20];

int curX, curY;//��ǰѡ�е�ֲ����ƶ������е�λ��
int curZhiWu;//0��û��ѡ�У�1��ѡ���˵�һ��ֲ��

bool fileExist(const char* name) {
	FILE* fp = fopen(name, "r");
	if (fp == NULL) {
		return false;
	}
	else {
		fclose(fp);
		return true;
	}
}

void gameInit()
{
	//�����б���ͼƬ
	//���ַ����޸�Ϊ�����ֽ��ַ�����
	loadimage(&imgBg, "res/bg.jpg");
	loadimage(&imgBar, "res/bar5.png");

	memset(imgZhiWu, 0, sizeof(imgZhiWu));
	
	//��ʼ��ֲ�￨��
	/*sprintf_s�����Ĺ�����ʽ������printf�����������������д��ָ�����ַ������У�
	�������������׼����������������ڹ�����̬���ɵ��ַ�����
	���������ļ�������־��Ϣ�ȡ�*/
	char name[64];
	for (int i = 0; i < ZHI_WU_COUNT; i++)
	{
		//����ֲ�￨�Ƶ��ļ���
		sprintf_s(name, sizeof(name), "res/Cards/card_%d.png", i + 1);
		loadimage(&imgCards[i], name);

		for (int j = 0; j < 20; j++) {
			sprintf_s(name, sizeof(name), "res/zhiwu/%d/%d.png", i, j + 1);
			//���ж�����ļ��Ƿ����
			if (fileExist(name)) {
				imgZhiWu[i][j] = new IMAGE;
				loadimage(imgZhiWu[i][j], name);
			}
			else {
				break;
			}
		}
	}
	curZhiWu = 0;
	//������Ϸ��ͼ�δ���
	initgraph(WIN_WIDTH,WIN_HEIGHT,1);
}

void updateWindow()//����ͼƬ
{
	BeginBatchDraw();//��ʼ����

	putimage(0, 0, &imgBg);//��һ��ͼƬ��Ⱦ��ʾ����
	//putimage(250, 0, &imgBar);
	putimagePNG(250, 0, &imgBar);

	for (int i = 0; i < ZHI_WU_COUNT; i++)
	{
		int x = 338 + i * 65;
		int y = 6; 
		putimage(x, y, &imgCards[i]);
	}

	//��Ⱦ���϶������е�ֲ��
	if (curZhiWu > 0) {
		IMAGE* img = imgZhiWu[curZhiWu - 1][0];
		putimagePNG(curX - img->getwidth()/2,curY-img->getheight()/2,img);
	}

	EndBatchDraw();//��������
}

void userClick(){
	ExMessage msg;
	static int status = 0;
	if (peekmessage(&msg)) {
		if (msg.message == WM_LBUTTONDOWN) {
			if (msg.x > 338 && msg.x < 338 + 65 * ZHI_WU_COUNT && msg.y < 96) {
				int index = (msg.x - 338) / 65;
				//printf("%d\n", index);
				status = 1;
				curZhiWu = index + 1;
			}
		}
		else if (msg.message == WM_MOUSEMOVE && status == 1) {
			curX = msg.x;
			curY = msg.y;
			
		}
		else if (msg.message == WM_LBUTTONUP) {

		}
	}
}

int main()
{
	gameInit();
	while (1)
	{
		userClick();

		updateWindow();

	}

	system("pause");
	return 0;
}
