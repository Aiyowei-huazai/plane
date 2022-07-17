#include<graphics.h>
#include<ctime>

using namespace std;
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")


//1����Ϣ��ʼ��

//����ͼ�������
#define kuan 520
#define gao  800

//���屳��y����
int bg1y, bg2y;
//���屳��x����
int bg1x, bg2x;

//��������
bool isplay = true;


//����ɻ����� 60*62
#define planek 60
#define planeg 62
int planex, planey;

//����л�
#define eplanek 119
#define eplaneg 147
#define enum 4

//����л��ӵ�
#define ebulletk 17
#define ebulletg 73
#define ebnum 4
//�л�������
struct eplane
{
	int ex;
	int ey;
	bool el;//�ɻ��Ƿ����   tureδ����   false ����
	bool es;//�ɻ��Ƿ�����ӵ�   false δ����   true �������

}eplanes[enum];

//�л��ӵ�����
struct ebullet
{
	int ebx;
	int eby;
	bool ebl;//�����ӵ� true����    false������
	bool ebs;//�����ӵ� true����    false δ����
}ebullets[ebnum];


//�����ӵ�
#define bnum 20
#define bulk  9
#define bulg 21
//�����ӵ�������
bool delay(int sec, int id)
{
	static int arr[5];
	int end = clock();
	if (end - arr[id] >= sec)
	{
		arr[id] = end;
		return true;
	}
	return false;
}

//�ӵ��ṹ��
struct bullet
{
	int bx;
	int by;
	bool islive ;
}bullets[bnum];

IMAGE bg;//����
IMAGE plane[2];//�ɻ�
IMAGE b[2];//�ӵ�
IMAGE ep[2];//�л�
IMAGE eb[2];//�л��ӵ�

//2������װ��
void sourez()
{
	//������ֵ
	loadimage(&bg, "bg5.jpg");
	bg1y = 0;
	bg2y = -gao;
	bg1x = 0;
	bg2x = 0;

	//��������
	/*if (isplay == true)
	{
		mciSendString("open level2.mp3", 0, 0, 0);
	}
	else
	{
		mciSendString("close level2.mp3", 0, 0, 0);
	}*/

	//�ɻ���ֵ
	loadimage(&plane[0], "plane0.jpg");
	loadimage(&plane[1], "plane1.jpg");
	
	planex = (kuan - planek) / 2;
	planey = (gao - planeg)-60;


	//�ӵ���ֵ
	for (int i = 0; i < bnum; i++)
	{
		bullets[i].bx = kuan/2;
		bullets[i].by =gao/2;
		bullets[i].islive = true;
	}
	loadimage(&b[0], "bullet0.jpg");
	loadimage(&b[1], "bullet1.jpg");

	//�л���ֵ
	for (int i = 0; i < enum; i++)
	{
		eplanes[i].ex = kuan / 2;
		eplanes[i].ey = gao / 2;
		eplanes[i].el = true;
		eplanes[i].es = false;
	}
	loadimage(&ep[0], "enemy0.jpg");
	loadimage(&ep[1], "enemy1.jpg");

	//�л��ӵ���ֵ
	for (int i = 0; i < ebnum; i++)
	{
		ebullets[i].ebl = true;//���ӵ�����
		ebullets[i].ebs = false;//���ӵ�δ����
	}
	//�л��ӵ�����ͼƬ
	loadimage(&eb[0], "ebullet0.jpg");
	loadimage(&eb[1], "ebullet1.jpg");
}


//3����������
void sourey()
{
	BeginBatchDraw();//��ʼ��������

	//���б�����Դ
	putimage(bg1x, bg1y, &bg);
	putimage(bg2x, bg2y, &bg);

	//���зɻ�
	putimage(planex, planey, &plane[0], SRCPAINT);
	putimage(planex, planey,&plane[1],SRCAND);
	//putimage(0, 0, &plane[1]);

	//�����ӵ�
	for (int i = 0; i < bnum; i++)
	{
		
			
			if (bullets[i].islive == false)
			{
				/*bullets[i].bx = planex + (planek / 2);
				bullets[i].by = planey - bulg;*/
				putimage(bullets[i].bx, bullets[i].by, &b[0],SRCPAINT);
				putimage(bullets[i].bx, bullets[i].by, &b[1],SRCAND);
			}
	}
	//�л��ɻ�����
	for (int i = 0; i < enum; i++)
	{

		if (eplanes[i].el == false)
		{
			
				/*eplanes[i].ex = rand() % kuan + 1;
				eplanes[i].ey = 20;*/
				putimage(eplanes[i].ex, eplanes[i].ey, &ep[0], SRCPAINT);
				putimage(eplanes[i].ex, eplanes[i].ey, &ep[1], SRCAND);
				
			
		}
	}

	//���ӵ��ļ���
	for (int i = 0; i < ebnum; i++)
	{
		if (ebullets[i].ebl == false&&ebullets[i].ebs==true)
		{
			putimage(ebullets[i].ebx, ebullets[i].eby, &eb[0], SRCPAINT);
			putimage(ebullets[i].ebx, ebullets[i].eby, &eb[1], SRCAND);
			//ebullets[i].ebl = true;

		}

	}
	

	EndBatchDraw();//������������
}


//4�����ݸ���
void soureg()
{
	//�����˶�
	bg1y++;
	bg2y++;
	if (bg1y > gao)bg1y = -gao;
	if (bg2y > gao)bg2y = -gao;

	if (GetAsyncKeyState(VK_UP)&&planey>0)planey -= 3;
	if (GetAsyncKeyState(VK_DOWN)&&planey<(gao-70))planey += 3;
	if (GetAsyncKeyState(VK_LEFT)&&planex>(-30))planex -= 3;
	if (GetAsyncKeyState(VK_RIGHT)&&planex<490)planex += 3;

	for (int i = 0; i < bnum; i++)
	{

		if (bullets[i].islive ==true)
		{
			if (GetAsyncKeyState(VK_SPACE)&&delay(150,0))
			{
				bullets[i].bx = planex + (planek / 2);
				bullets[i].by = planey - bulg;
				bullets[i].islive = false;
				break;
			}
		}
		
		//bullets[i].islive = false;
	}

	for (int i = 0; i < bnum; i++)
	{
		if (bullets[i].islive == false)
		{
			
			bullets[i].by-=4;
			if (bullets[i].by < 0)
			{
				bullets[i].islive = true;
			}
		}
	}
	//�л��������

	for (int i = 0; i < enum; i++)
	{
		if (eplanes[i].el == true&&delay(300,1))
		{
			eplanes[i].ex = rand() % 250 +rand()% 200+rand()%70;//��������л���x����
			eplanes[i].ey = -planeg;//��������л���y����
			eplanes[i].el =false;//�ɻ�����
			break;//���ܷɻ�����
		}
	}

	//�л��˶�
	for (int i = 0; i < enum; i++)
	{
		if (eplanes[i].el == false)
		{
			eplanes[i].ey += 3;

			/*if (eplanes[i].ey >= 20)
			{
				for (int j = 0; j < ebnum; j++)
				{
					if (ebullets[j].ebl == true&&ebullets[j].ebs==false&&delay(500,2))
					{
						ebullets[j].ebx = eplanes[i].ex + eplanek / 2;
						ebullets[j].eby = eplanes[i].ey + eplaneg;
						ebullets[j].ebl = false;
						ebullets[j].ebs = true;
						break;
					}
				}
				
			}*/
			if (eplanes[i].ey > gao)
			{
				eplanes[i].el = true;
				eplanes[i].es = false;
			}
		}
	}
	
	//�ж��ӵ���л�����ײ
	for (int i = 0; i < enum; i++)
	{
		for (int j = 0; j < bnum; j++)
		{
			if (eplanes[i].el == false && bullets[j].islive == false)
			{
				if (eplanes[i].ex <= bullets[j].bx && bullets[j].bx <= (eplanes[i].ex + eplanek) &&
					eplanes[i].ey <= bullets[j].by && bullets[j].by <= (eplanes[i].ey + eplaneg))
				{
					eplanes[i].el = true;
					bullets[j].islive = true;
					eplanes[i].es = false;
				}
			}
		}
	}
	//�����л�������л�����λ�ã������ӵ�
	for (int i = 0; i < enum; i++)
	{
		if (eplanes[i].el == false)
		{
			if (eplanes[i].ey >= 15&&eplanes[i].es==false)
			{
				for (int j = 0; j < ebnum; j++)
				{
					if (ebullets[j].ebl == true&&ebullets[j].ebs==false&&delay(700,2))
					{
						ebullets[j].ebx = eplanes[i].ex + eplanek / 2;
						ebullets[j].eby = eplanes[i].ey + eplaneg;
						ebullets[j].ebl = false;
						ebullets[j].ebs = true;
						eplanes[i].es = true;
						break;
					}
				}

			}
		}
	}
	//for (int i = 0; i < ebnum; i++)
	//{
	//	for (int j = 0; j < enum; j++)
	//	{
	//		if (eplanes[j].el == false&&eplanes[j].ey>=20)
	//		{
	//			if (ebullets[i].ebl == true && ebullets[i].ebs == false)
	//			{
	//				ebullets[i].ebx = eplanes[j].ex + eplanek / 2;
	//				ebullets[i].eby = eplanes[j].ey + eplaneg;
	//				ebullets[i].ebl = false;
	//				ebullets[i].ebs = true;
	//				break;
	//			}

	//		}

	//	}
	//}





	//�õл��ӵ�����
	for (int i = 0; i < ebnum; i++)
	{
		if (ebullets[i].ebl == false&&ebullets[i].ebs==true)
		{
			ebullets[i].eby += 7;
		}

		if (ebullets[i].eby >= (gao + ebulletg))
		{
			ebullets[i].ebl = true;
			ebullets[i].ebs = false;
			
		}

	}

}

int main()
{
	srand((unsigned)time (NULL));
	initgraph(kuan, gao);
	sourez();
	
	while (true)
	{

		//Sleep(3);
		int starttime = clock();

		sourey();
		soureg();

		int endtime = clock() - starttime;
		if (1000 / 60 - endtime > 0)
		{
			Sleep(1000 / 60 - endtime);
		}

	}
	




	system("pause");
	return 0;
}