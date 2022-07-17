#include<graphics.h>
#include<ctime>

using namespace std;
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")


//1、信息初始化

//背景图定义宽、高
#define kuan 520
#define gao  800

//定义背景y坐标
int bg1y, bg2y;
//定义背景x坐标
int bg1x, bg2x;

//定义音乐
bool isplay = true;


//定义飞机宽、高 60*62
#define planek 60
#define planeg 62
int planex, planey;

//定义敌机
#define eplanek 119
#define eplaneg 147
#define enum 4

//定义敌机子弹
#define ebulletk 17
#define ebulletg 73
#define ebnum 4
//敌机的属性
struct eplane
{
	int ex;
	int ey;
	bool el;//飞机是否存在   ture未出场   false 出场
	bool es;//飞机是否发射过子弹   false 未发射   true 发射过了

}eplanes[enum];

//敌机子弹属性
struct ebullet
{
	int ebx;
	int eby;
	bool ebl;//定义子弹 true存在    false不存在
	bool ebs;//定义子弹 true发射    false 未发射
}ebullets[ebnum];


//定义子弹
#define bnum 20
#define bulk  9
#define bulg 21
//减慢子弹出行速
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

//子弹结构体
struct bullet
{
	int bx;
	int by;
	bool islive ;
}bullets[bnum];

IMAGE bg;//背景
IMAGE plane[2];//飞机
IMAGE b[2];//子弹
IMAGE ep[2];//敌机
IMAGE eb[2];//敌机子弹

//2、数据装载
void sourez()
{
	//背景赋值
	loadimage(&bg, "bg5.jpg");
	bg1y = 0;
	bg2y = -gao;
	bg1x = 0;
	bg2x = 0;

	//背景音乐
	/*if (isplay == true)
	{
		mciSendString("open level2.mp3", 0, 0, 0);
	}
	else
	{
		mciSendString("close level2.mp3", 0, 0, 0);
	}*/

	//飞机赋值
	loadimage(&plane[0], "plane0.jpg");
	loadimage(&plane[1], "plane1.jpg");
	
	planex = (kuan - planek) / 2;
	planey = (gao - planeg)-60;


	//子弹赋值
	for (int i = 0; i < bnum; i++)
	{
		bullets[i].bx = kuan/2;
		bullets[i].by =gao/2;
		bullets[i].islive = true;
	}
	loadimage(&b[0], "bullet0.jpg");
	loadimage(&b[1], "bullet1.jpg");

	//敌机赋值
	for (int i = 0; i < enum; i++)
	{
		eplanes[i].ex = kuan / 2;
		eplanes[i].ey = gao / 2;
		eplanes[i].el = true;
		eplanes[i].es = false;
	}
	loadimage(&ep[0], "enemy0.jpg");
	loadimage(&ep[1], "enemy1.jpg");

	//敌机子弹赋值
	for (int i = 0; i < ebnum; i++)
	{
		ebullets[i].ebl = true;//敌子弹存在
		ebullets[i].ebs = false;//敌子弹未发射
	}
	//敌机子弹加载图片
	loadimage(&eb[0], "ebullet0.jpg");
	loadimage(&eb[1], "ebullet1.jpg");
}


//3、运行数据
void sourey()
{
	BeginBatchDraw();//开始批量绘制

	//运行背景资源
	putimage(bg1x, bg1y, &bg);
	putimage(bg2x, bg2y, &bg);

	//运行飞机
	putimage(planex, planey, &plane[0], SRCPAINT);
	putimage(planex, planey,&plane[1],SRCAND);
	//putimage(0, 0, &plane[1]);

	//运行子弹
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
	//敌机飞机加载
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

	//敌子弹的加载
	for (int i = 0; i < ebnum; i++)
	{
		if (ebullets[i].ebl == false&&ebullets[i].ebs==true)
		{
			putimage(ebullets[i].ebx, ebullets[i].eby, &eb[0], SRCPAINT);
			putimage(ebullets[i].ebx, ebullets[i].eby, &eb[1], SRCAND);
			//ebullets[i].ebl = true;

		}

	}
	

	EndBatchDraw();//结束批量绘制
}


//4、数据跟新
void soureg()
{
	//背景运动
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
	//敌机随机产生

	for (int i = 0; i < enum; i++)
	{
		if (eplanes[i].el == true&&delay(300,1))
		{
			eplanes[i].ex = rand() % 250 +rand()% 200+rand()%70;//随机产生敌机的x坐标
			eplanes[i].ey = -planeg;//随机产生敌机的y坐标
			eplanes[i].el =false;//飞机出现
			break;//单架飞机产生
		}
	}

	//敌机运动
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
	
	//判断子弹与敌机的碰撞
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
	//遍历敌机，如果敌机到达位置，发射子弹
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





	//让敌机子弹加速
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