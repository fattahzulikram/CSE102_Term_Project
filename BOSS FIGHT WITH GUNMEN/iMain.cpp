/*
Project Name : Boss Fight With Gunmen
By - 1705035
	 1705058
	 1705059
	 L-1, T-1
	 CSE, BUET
*/
#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
# include "iGraphics.h"
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
void setuserzero();
void LoadGirl();
void LoadEnemy();
void LoadBullets();
void LoadEB();
void HSchecker();
void SetVarZero();
void SaveGirl();
void SaveEnem();
void SaveBull();
void SaveEnemBull();
void firstenemy();
void enemysliding();
void jump_change();
void EnemyVariables();
void bulletmove();
void EnemyDamage1();
void EnemyDamage2();
void EnemyDamage3();
void scoreupdate();
void HSshow();
struct coordinate
{
	int x;
	int y;
}but[4];
struct enemy
{
	int ex;
	int ey;
	int life;
	int state;
	int shooter;
};
struct bullet
{
	int bx;
	int by;
	int stat;
};
struct ebullet1
{
	int bullx;
	int bully;
	int stats;
};
struct ebullet2
{
	int bullx;
	int bully;
	int stats;
};
struct ebullet3
{
	int bullx;
	int bully;
	int stats;
};
struct highscore
{
	char name[10];
	int score;
};
struct highscore hs[6];
struct ebullet1 eb[2];
struct ebullet2 eb2[2];
struct ebullet3 eb3[2];
struct bullet bu[6];
int bc = 0;
struct enemy enem[4];
char str[11], str2[11];
int len = 0;
int mposx,  mposy;
int mstate = -1;
char button[10][15] = { "Buttons\\B1.bmp", "Buttons\\B2.bmp", "Buttons\\B3.bmp", "Buttons\\B4.bmp" };
int girlindex = 0;
int girlx = 0;
int girly = 0;
int girllife = 25;
char runr[100][100] = { "Characters\\Player\\r1.bmp", "Characters\\Player\\r2.bmp", "Characters\\Player\\r3.bmp", "Characters\\Player\\r4.bmp", "Characters\\Player\\r5.bmp", "Characters\\Player\\r6.bmp", "Characters\\Player\\r7.bmp", "Characters\\Player\\r8.bmp"};
char idler[40] = { "Characters\\Player\\i1.bmp" };
char girljr[50][50] = { "Characters\\Player\\j1.bmp", "Characters\\Player\\j2.bmp",};
char shootr[40] = { "Characters\\Player\\s1.bmp" };
bool stand = true;
int steps = 0;
int jump = 0;
int jumpUp = 0;
int jumpy = 0;
int highest_jump = 205;
int girlface = 1;
char runl[100][100] = { "Characters\\Player\\Left\\lr1.bmp", "Characters\\Player\\Left\\lr2.bmp", "Characters\\Player\\Left\\lr3.bmp", "Characters\\Player\\Left\\lr4.bmp", "Characters\\Player\\Left\\lr5.bmp", "Characters\\Player\\Left\\lr6.bmp", "Characters\\Player\\Left\\lr7.bmp", "Characters\\Player\\Left\\lr8.bmp"};
char idlel[40] = { "Characters\\Player\\Left\\l1.bmp" };
char girljl[50][50] = { "Characters\\Player\\Left\\lj1.bmp", "Characters\\Player\\Left\\lj2.bmp", };
char target[40] = { "Characters\\Player\\t.bmp" };
char sr[40] = { "Characters\\Player\\s1.bmp" };
char el[40] = { "Characters\\Villains\\el.bmp" };
char lifebar[50][50] = { "Life\\0.bmp", "Life\\1.bmp", "Life\\2.bmp", "Life\\3.bmp", "Life\\4.bmp", "Life\\5.bmp", };
char bull[30] = { "Images\\Bullet.bmp" };
char gbull[30] = { "Images\\Gbullet.bmp" };
int score = 0;
int shootstatus = 0;
int estate = 0;
int hstate = 0;
double t = 0;
int e1c = 0, e2c = 0, e3c = 0;
char scor[4];
void iDraw()
{
	iClear();
	if (mstate == -1) //When the game runs
	{
		iShowBMP(0, 0, "Images\\1.bmp");
		iSetColor(0, 0, 0);
	}
	if (mstate == 0) //The Home menu
	{
		iShowBMP(0, 0, "Images\\2.bmp");
		for (int i = 0; i < 4; i++)
		{
			iShowBMP2(but[i].x, but[i].y, button[i], 0);
		}
		iShowBMP2(880, 150, "Images\\In.bmp", 0);
	}
	else if (mstate == 3) //High Score
	{
		iShowBMP(0, 0, "Images\\3.bmp");
		iSetColor(255, 255, 255);
		iText(10, 750, "Press Home To Return", GLUT_BITMAP_TIMES_ROMAN_24);
		HSshow();
	}
	else if (mstate == 4) //The Exit page
	{
		iShowBMP(0, 0, "Images\\4.bmp");
		iShowBMP2(400, 200, "Buttons\\E1.bmp", 0);
		iShowBMP2(740, 200, "Buttons\\E2.bmp", 0);
	}
	else if (mstate == 1) //Main Game World
	{
		iShowBMP(0, 0, "Images\\5.bmp");
		iSetColor(255, 0, 0);
		iText(900, 750, "Press Home To Save Game & Return To Main Menu", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(900, 700, "Press P To Pause", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(10, 700, "SCORE : ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(120,700,scor,GLUT_BITMAP_TIMES_ROMAN_24);
		if (shootstatus == 1) //Shooting Stance
		{
			iShowBMP2(girlx, girly + jumpy, shootr, 0);
		}
		else if (girlface == 1) //Right Looking
		{
			if (jump)
			{
				if (jumpUp)
				{
					iShowBMP2(girlx, girly + jumpy, girljr[0], 0);
				}
				else
					iShowBMP2(girlx, girly + jumpy, girljr[1], 0);
			}
			else
			{
				if (!stand)
				{
					iShowBMP2(girlx, girly + jumpy, runr[girlindex], 0);
					steps++;
					if (steps >= 30)
					{
						steps = 0;
						girlindex = 0;
						stand = true;
					}
				}
				else
				{
					iShowBMP2(girlx, girly+jumpy, idler, 0);
				}
			}
		}
		else if (girlface == 2) //Left Looking
		{
			if (jump)
			{
				if (jumpUp)
				{
					iShowBMP2(girlx, girly + jumpy, girljl[0], 0);
				}
				else
					iShowBMP2(girlx, girly + jumpy, girljl[1], 0);
			}
			else
			{
				if (!stand)
				{
					iShowBMP2(girlx, girly+jumpy, runl[girlindex], 0);
					steps++;
					if (steps >= 30)
					{
						steps = 0;
						girlindex = 0;
						stand = true;
					}
				}
				else
				{
					iShowBMP2(girlx, girly+jumpy, idlel, 0);
				}
			}
		}
		if (girllife == 25)
			iShowBMP2(-0, 750, lifebar[0], 0);
		else if (girllife == 20)
			iShowBMP2(-0, 750, lifebar[1], 0);
		else if (girllife == 15)
			iShowBMP2(0, 750, lifebar[2], 0);
		else if (girllife == 10)
			iShowBMP2(0, 750, lifebar[3], 0);
		else if (girllife == 05)
			iShowBMP2(0, 750, lifebar[4], 0);
		else if (girllife == 00)
			iShowBMP2(0, 750, lifebar[5], 0);

		if (((eb[0].bullx <= girlx + 150) && (eb[0].bullx >= girlx)) && ((eb[0].bully <= girly + jumpy + 150) && (eb[0].bully > jumpy + girly + 20)) && eb[0].stats == 1)
		{
			eb[0].stats = 0;
			girllife -= 5;
		}
		if (((eb[1].bullx <= girlx + 150) && (eb[1].bullx >= girlx)) && ((eb[1].bully <= girly + jumpy + 150) && (eb[1].bully > girly + jumpy + 20)) && eb[1].stats == 1)
		{
			eb[1].stats = 0;
			girllife -= 5;
		}
		if (((eb2[0].bullx <= girlx + 150) && (eb2[0].bullx >= girlx)) && ((eb2[0].bully <= girly + jumpy + 150) && (eb2[0].bully > girly + jumpy + 20)) && eb2[0].stats == 1)
		{
			eb2[0].stats = 0;
			girllife -= 5;
		}
		if (((eb2[1].bullx <= girlx + 150) && (eb2[1].bullx >= girlx)) && ((eb2[1].bully <= girly + jumpy + 150) && (eb2[1].bully > girly + jumpy + 20)) && eb2[1].stats == 1)
		{
			eb2[1].stats = 0;
			girllife -= 5;
		}
		if (((eb3[0].bullx <= girlx + 150) && (eb3[0].bullx >= girlx)) && ((eb3[0].bully <= girly + jumpy + 150) && (eb3[0].bully > girly + jumpy + 20)) && eb3[0].stats == 1)
		{
			eb3[0].stats = 0;
			girllife -= 5;
		}
		if (((eb3[1].bullx <= girlx + 150) && (eb3[1].bullx >= girlx)) && ((eb3[1].bully <= girly + jumpy + 150) && (eb3[1].bully > girly + jumpy + 20)) && eb3[1].stats == 1)
		{
			eb3[1].stats = 0;
			girllife -= 5;
		}
		if (((bu[0].bx >= enem[0].ex) && (bu[0].bx <= enem[0].ex + 150)) && ((bu[0].by <= enem[0].ey + 150) && (bu[0].by >= enem[0].ey)) && bu[0].stat == 1 && enem[0].state == 1)
		{
			bu[0].stat = 0;
			enem[0].life -= 5;
			score++;
		}
		else if (((bu[0].bx >= enem[1].ex) && (bu[0].bx <= enem[1].ex + 150)) && ((bu[0].by <= enem[1].ey + 150) && (bu[0].by >= enem[1].ey)) && bu[0].stat == 1 && enem[1].state == 1)
		{
			bu[0].stat = 0;
			enem[1].life -= 5;
			score++;
		}
		else if (((bu[0].bx >= enem[2].ex) && (bu[0].bx <= enem[2].ex + 150)) && ((bu[0].by <= enem[2].ey + 150) && (bu[0].by >= enem[2].ey)) && bu[0].stat == 1 && enem[2].state == 1)
		{
			bu[0].stat = 0;
			enem[2].life -= 5;
			score++;
		}
		if (((bu[1].bx >= enem[0].ex) && (bu[1].bx <= enem[0].ex + 150)) && ((bu[1].by <= enem[0].ey + 150) && (bu[1].by >= enem[0].ey)) && bu[1].stat == 1 && enem[0].state == 1)
		{
			bu[1].stat = 0;
			enem[0].life -= 5;
			score++;
		}
		else if (((bu[1].bx >= enem[1].ex) && (bu[1].bx <= enem[1].ex + 150)) && ((bu[1].by <= enem[1].ey + 150) && (bu[1].by >= enem[1].ey)) && bu[1].stat == 1 && enem[1].state == 1)
		{
			bu[1].stat = 0;
			enem[1].life -= 5;
			score++;
		}
		else if (((bu[1].bx >= enem[2].ex) && (bu[1].bx <= enem[2].ex + 150)) && ((bu[1].by <= enem[2].ey + 150) && (bu[1].by >= enem[2].ey)) && bu[1].stat == 1 && enem[2].state == 1)
		{
			bu[1].stat = 0;
			enem[2].life -= 5;
			score++;
		}
		if (((bu[2].bx >= enem[0].ex) && (bu[2].bx <= enem[0].ex + 150)) && ((bu[2].by <= enem[0].ey + 150) && (bu[2].by >= enem[0].ey)) && bu[2].stat == 1 && enem[0].state == 1)
		{
			bu[2].stat = 0;
			enem[0].life -= 5;
			score++;
		}
		else if (((bu[2].bx >= enem[1].ex) && (bu[2].bx <= enem[1].ex + 150)) && ((bu[2].by <= enem[1].ey + 150) && (bu[2].by >= enem[1].ey)) && bu[2].stat == 1 && enem[1].state == 1)
		{
			bu[2].stat = 0;
			enem[1].life -= 5;
			score++;
		}
		else if (((bu[2].bx >= enem[2].ex) && (bu[2].bx <= enem[2].ex + 150)) && ((bu[2].by <= enem[2].ey + 150) && (bu[2].by >= enem[2].ey)) && bu[2].stat == 1 && enem[2].state == 1)
		{
			bu[2].stat = 0;
			enem[2].life -= 5;
			score++;
		}
		if (((bu[3].bx >= enem[0].ex) && (bu[3].bx <= enem[0].ex + 150)) && ((bu[3].by <= enem[0].ey + 150) && (bu[3].by >= enem[0].ey)) && bu[3].stat == 1 && enem[0].state == 1)
		{
			bu[3].stat = 0;
			enem[0].life -= 5;
			score++;
		}
		else if (((bu[3].bx >= enem[1].ex) && (bu[3].bx <= enem[1].ex + 150)) && ((bu[3].by <= enem[1].ey + 150) && (bu[3].by >= enem[1].ey)) && bu[3].stat == 1 && enem[1].state == 1)
		{
			bu[3].stat = 0;
			enem[1].life -= 5;
			score++;
		}
		else if (((bu[3].bx >= enem[2].ex) && (bu[3].bx <= enem[2].ex + 150)) && ((bu[3].by <= enem[2].ey + 150) && (bu[3].by >= enem[2].ey)) && bu[3].stat == 1 && enem[2].state == 1)
		{
			bu[3].stat = 0;
			enem[2].life -= 5;
			score++;
		}
		if (((bu[4].bx >= enem[0].ex) && (bu[4].bx <= enem[0].ex + 150)) && ((bu[4].by <= enem[0].ey + 150) && (bu[4].by >= enem[0].ey)) && bu[4].stat == 1 && enem[0].state == 1)
		{
			bu[4].stat = 0;
			enem[0].life -= 5;
			score++;
		}
		else if (((bu[4].bx >= enem[1].ex) && (bu[4].bx <= enem[1].ex + 150)) && ((bu[4].by <= enem[1].ey + 150) && (bu[4].by >= enem[1].ey)) && bu[4].stat == 1 && enem[1].state == 1)
		{
			bu[4].stat = 0;
			enem[1].life -= 5;
			score++;
		}
		else if (((bu[4].bx >= enem[2].ex) && (bu[4].bx <= enem[2].ex + 150)) && ((bu[4].by <= enem[2].ey + 150) && (bu[4].by >= enem[2].ey)) && bu[4].stat == 1 && enem[2].state == 1)
		{
			bu[4].stat = 0;
			enem[2].life -= 5;
			score++;
		}
		if (((bu[5].bx >= enem[0].ex) && (bu[5].bx <= enem[0].ex + 150)) && ((bu[5].by <= enem[0].ey + 150) && (bu[5].by >= enem[0].ey)) && bu[5].stat == 1 && enem[0].state == 1)
		{
			bu[5].stat = 0;
			enem[0].life -= 5;
			score++;
		}
		else if (((bu[5].bx >= enem[1].ex) && (bu[5].bx <= enem[1].ex + 150)) && ((bu[5].by <= enem[1].ey + 150) && (bu[5].by >= enem[1].ey)) && bu[5].stat == 1 && enem[1].state == 1)
		{
			bu[5].stat = 0;
			enem[1].life -= 5;
			score++;
		}
		else if (((bu[5].bx >= enem[2].ex) && (bu[5].bx <= enem[2].ex + 150)) && ((bu[5].by <= enem[2].ey + 150) && (bu[5].by >= enem[2].ey)) && bu[5].stat == 1 && enem[2].state == 1)
		{
			bu[5].stat = 0;
			enem[2].life -= 5;
			score++;
		}

		if (enem[0].shooter == 1)
		{
			PlaySound(0, 0, 0);
			eb[e1c].stats = 1;
			eb[e1c].bullx = enem[0].ex;
			eb[e1c].bully = enem[0].ey+75;
			e1c++;
			if (e1c >= 2)
				e1c = 0;
			PlaySound("Sounds\\Gunshot.wav", NULL, SND_ASYNC);
			enem[0].shooter = 0;
		}
		if (enem[1].shooter == 1)
		{
			PlaySound(0, 0, 0);
			eb2[e2c].stats = 1;
			eb2[e2c].bullx = enem[1].ex;
			eb2[e2c].bully = enem[1].ey + 75;
			e2c++;
			if (e2c >= 2)
				e2c = 0;
			PlaySound("Sounds\\Gunshot.wav", NULL, SND_ASYNC);
			enem[1].shooter = 0;
		}
		if (enem[2].shooter == 1)
		{
			PlaySound(0, 0, 0);
			eb3[e3c].stats = 1;
			eb3[e3c].bullx = enem[2].ex;
			eb3[e3c].bully = enem[2].ey + 75;
			e3c++;
			if (e3c >= 2)
				e3c = 0;
			PlaySound("Sounds\\Gunshot.wav", NULL, SND_ASYNC);
			enem[2].shooter = 0;
		}


		if (eb[0].stats == 1)
			iShowBMP2(eb[0].bullx, eb[0].bully, bull, 0);
		else if (eb[0].stats == 0)
			iShowBMP2(-1, -1, bull, 0);

		if (eb[1].stats == 1)
			iShowBMP2(eb[1].bullx, eb[1].bully, bull, 0);
		else if (eb[1].stats == 0)
			iShowBMP2(-1, -1, bull, 0);

		if (eb2[0].stats == 1)
			iShowBMP2(eb2[0].bullx, eb2[0].bully, bull, 0);
		else if (eb2[0].stats == 0)
			iShowBMP2(-1, -1, bull, 0);

		if (eb2[1].stats == 1)
			iShowBMP2(eb2[1].bullx, eb2[1].bully, bull, 0);
		else if (eb2[1].stats == 0)
			iShowBMP2(-1, -1, bull, 0);

		if (eb3[0].stats == 1)
			iShowBMP2(eb3[0].bullx, eb3[0].bully, bull, 0);
		else if (eb3[0].stats == 0)
			iShowBMP2(-1, -1, bull, 0);

		if (eb3[1].stats == 1)
			iShowBMP2(eb3[1].bullx, eb3[1].bully, bull, 0);
		else if (eb3[1].stats == 0)
			iShowBMP2(-1, -1, bull, 0);

		if (enem[0].state == 1)
			iShowBMP2(enem[0].ex, 0, el, 0);
		else if (enem[0].state == 0)
			iShowBMP2(-1, -1, el, 0);

		if (enem[1].state == 1)
			iShowBMP2(enem[1].ex, 0, el, 0);
		else if (enem[1].state == 0)
			iShowBMP2(-1, -1, el, 0);

		if (enem[2].state == 1)
			iShowBMP2(enem[2].ex, 0, el, 0);
		else if (enem[2].state == 0)
			iShowBMP2(-1, -1, el, 0);

		if (shootstatus == 1)
		{
			PlaySound(0,0,0);
			bu[bc].stat = 1;
			bu[bc].bx = (girlx + 150);
			bu[bc].by = (girly + jumpy + 75);
			bc++;
			if (bc > 5)
				bc = 0;
			PlaySound("Sounds\\Gunshot.wav",NULL, SND_ASYNC);
			shootstatus = 0;
		}
		if (bu[0].stat == 1)
			iShowBMP2(bu[0].bx, bu[0].by, gbull, 0);

		else
			iShowBMP2(-1, -1, gbull, 0);

		if (bu[1].stat == 1)
			iShowBMP2(bu[1].bx, bu[1].by, gbull, 0);

		else
			iShowBMP2(-1, -1, gbull, 0);

		if (bu[2].stat == 1)
			iShowBMP2(bu[2].bx, bu[2].by, gbull, 0);

		else
			iShowBMP2(-1, -1, gbull, 0);

		if (bu[3].stat == 1)
			iShowBMP2(bu[3].bx, bu[3].by, gbull, 0);

		else
			iShowBMP2(-1, -1, gbull, 0);

		if (bu[4].stat == 1)
			iShowBMP2(bu[4].bx, bu[4].by, gbull, 0);

		else
			iShowBMP2(-1, -1, gbull, 0);

		if (bu[5].stat == 1)
			iShowBMP2(bu[5].bx, bu[5].by, gbull, 0);

		else
			iShowBMP2(-1, -1, gbull, 0);

		if (girllife <= 0)
		{
			mstate = 6;
		}
		if (enem[0].life <= 0)
		{
			enem[0].state = 0;
		}
		if (enem[1].life <= 0)
		{
			enem[1].state = 0;
		}
		if (enem[2].life <= 0)
		{
			enem[2].state = 0;
		}

	}
	else if (mstate == 6)
	{
		iShowBMP(0, 0, "Images\\6.bmp");
		iShowBMP2(300, 0, "Images\\Input.bmp", 0);
		iSetColor(250, 0, 0);
		iText(450, 120, str, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (mstate == 2)
	{
		iShowBMP(0, 0, "Images\\Pause.bmp");
	}

}
void enemysliding()
{

	enem[0].ex = enem[0].ex + 30 * sin(20 * t);
	enem[1].ex = enem[1].ex + 40 * sin(10 * t);
	enem[2].ex = enem[2].ex + 20 * sin(50 * t);
	t++;
}
void iMouseMove(int mx, int my)
{

}
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (mstate == 0 && my<686 && my>586 && mx > 100 && mx < 400)
		{
			setuserzero();
			SetVarZero();
			mstate = 1;
			PlaySound(0,0,0);

		}
		if (mstate == 0 && my<524 && my>424 && mx>100 && mx < 400)
		{
			PlaySound(0, 0, 0);
			mstate = 1;
			LoadGirl();
			LoadEnemy();
			LoadBullets();
			LoadEB();
		}
		if (mstate == 0 && my<462 && my>342 && mx>100 && mx<400)
			mstate = 3;
		if (mstate == 0 && my<300 && my>200 && mx>100 && mx < 400)
			mstate = 4;
		if (mstate == 4 && my<430 && my>300 && mx>400 && mx < 700)
			exit(0);
		if (mstate == 4 && my<430 && my>300 && mx>740 && mx < 1040)
			mstate = 0;
		if (mstate == 2 && mx>340 && mx<1080 && my>125 && my < 337)
			exit(0);
		if (mstate == 2 && mx>340 && mx<1080 && my>377 && my < 577)
		{
			mstate = 1;
			LoadGirl();
			LoadEnemy();
			LoadBullets();
			LoadEB();
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (mstate == 1)
			shootstatus = 1;
	}

}
void iPassiveMouseMove(int mx,int my)
{

}
void iKeyboard(unsigned char key)
{
	if(mstate == -1 && key == '\r')
	{
		mstate += 1;
	}
	if (mstate == 1 && key == 'd')
	{
		girlx += 10;
		girlindex++;
		if (girlx >= 450)
			girlx = 450;
		if (girlindex > 7)
			girlindex = 0;
		stand = false;
		girlface = 1;
	}
	else if (mstate == 1 && key == 'a')
	{
		girlx -= 10;
		girlindex--;
		if (girlx < 0)
			girlx = 0;
		if (girlindex < 0)
			girlindex = 7;
		stand = false;
		girlface = 2;
	}
	if (mstate == 1 && key == 'w' && !jump)
	{
		jump = 1;
		jumpUp = 1;
	}
	if (mstate == 1 && key == 'p')
	{
		SaveGirl();
		SaveEnem();
		SaveBull();
		SaveEnemBull();
		mstate = 2;
	}
	if (mstate == 6)
	{
		if (key != '\r')
		{
			if (key != '\b')
			{
				str[len] = key;
				len++;
				str[len] = '\0';
			}
			else
			{
				if (len <= 0)
					len = 0;
				else
					len--;
				str[len] = '\0';
			}
		}
		else
		{
			strcpy(str2, str);
			HSchecker();
			PlaySound("Sounds\\1.wav", NULL, SND_LOOP | SND_ASYNC);
			mstate = 3;
			setuserzero();
			SetVarZero();
		}
	}
}
void iSpecialKeyboard(unsigned char key)
{

	if((mstate ==3) && key == GLUT_KEY_HOME)
	{
		mstate = 0;
	}
	if (mstate == 1 && key == GLUT_KEY_RIGHT)
	{
		girlx += 10;
		girlindex++;
		if (girlx >= 450)
			girlx = 450;
		if (girlindex > 7)
			girlindex = 0;
		stand = false;
		girlface = 1;
	}
	else if (mstate == 1 && key == GLUT_KEY_LEFT)
	{
		girlx -= 10;
		girlindex--;
		if (girlx < 0)
			girlx = 0;
		if (girlindex < 0)
			girlindex = 7;
		stand = false;
		girlface = 2;
	}
	if (mstate == 1 && key == GLUT_KEY_UP && !jump)
	{
		jump = 1;
		jumpUp = 1;
	}
	if (mstate == 1 && key == GLUT_KEY_HOME)
	{
		SaveGirl();
		SaveEnem();
		SaveBull();
		SaveEnemBull();
		PlaySound("Sounds\\1.wav", NULL, SND_LOOP | SND_ASYNC);
		mstate = 0;
	}
}
void jump_change()
{
	if (jump)
	{
		if (jumpUp)
		{
			jumpy += 20;
			if (jumpy >= highest_jump)
			{
				jumpUp = 0;
			}
		}
		else
		{
			jumpy -= 20;
			if (jumpy < 0)
			{
				jump = 0;
				jumpy = 0;
			}
		}
	}
}
void EnemyVariables()
{
	time_t t;
	srand((unsigned)time(&t));
	if (mstate == 1 && enem[0].state == 0)
	{
		enem[0].ex = 1170 + rand() % 50;
		enem[0].ey = 0;
		enem[0].life = 20;
		enem[0].state = 1;
	}
	else if (mstate == 1 && enem[1].state == 0)
	{
		enem[1].ex = 850 + rand() % 50;
		enem[1].ey = 0;
		enem[1].life = 20;
		enem[1].state = 1;
	}
	else if (mstate == 1 && enem[2].state == 0)
	{
		enem[2].ex = 620 + rand() % 50;
		enem[2].ey = 0;
		enem[2].life = 20;
		enem[2].state = 1;
	}
}
void bulletmove()
{

	if (mstate == 1 && bu[0].stat == 1)
			bu[0].bx += 35;
		else
			bu[0].bx = -1;

	if (mstate == 1 && bu[1].stat == 1)
			bu[1].bx += 35;
		else
			bu[1].bx = -1;

	if (mstate == 1 && bu[2].stat == 1)
			bu[2].bx += 35;
		else
			bu[2].bx = -1;

	if (mstate == 1 && bu[3].stat == 1)
			bu[3].bx += 35;
		else
			bu[3].bx = -1;

	if (mstate == 1 && bu[4].stat == 1)
			bu[4].bx += 35;
		else
			bu[4].bx = -1;

	if (mstate == 1 && bu[5].stat == 1)
			bu[5].bx += 35;
		else
			bu[5].bx = -1;

	if (mstate == 1 && eb[0].stats == 1)
			eb[0].bullx -= 30;
		else
			eb[0].bullx = -1;

	if (mstate == 1 && eb[1].stats == 1)
			eb[1].bullx -= 30;
		else
			eb[1].bullx = -1;

	if (mstate == 1 && eb2[0].stats == 1)
			eb2[0].bullx -= 30;
		else
			eb2[0].bullx = -1;

	if (mstate == 1 && eb2[1].stats == 1)
			eb2[1].bullx -= 30;
		else
			eb2[1].bullx = -1;

	if (mstate == 1 && eb3[0].stats == 1)
			eb3[0].bullx -= 30;
		else
			eb3[0].bullx = -1;

	if (mstate == 1 && eb3[1].stats == 1)
			eb3[1].bullx -= 30;
		else
			eb3[1].bullx = -1;


		if (bu[0].bx > 1440)
			bu[0].stat = 0;
		if (bu[1].bx > 1440)
			bu[1].stat = 0;
		if (bu[2].bx > 1440)
			bu[2].stat = 0;
		if (bu[3].bx > 1440)
			bu[3].stat = 0;
		if (bu[4].bx > 1440)
			bu[4].stat = 0;
		if (bu[5].bx > 1440)
			bu[5].stat = 0;
}
void SaveGirl()
{
	FILE *pl;
	pl = fopen("Save\\P.txt", "w");
	fprintf(pl, "%d %d %d %d %d %d %d %d %d", girlx, girly, jumpy, girlface, girlindex, jump, jumpUp, score);
	fclose(pl);
}
void SaveEnem()
{
	FILE *enm;
	int i;
	enm = fopen("Save\\E.txt", "w");
	for (i = 0; i < 3; i++)
		fprintf(enm, "%d %d %d %d %d\n", enem[i].ex, enem[i].ey, enem[i].life, enem[i].shooter, enem[i].state);
	fclose(enm);
}
void SaveBull()
{
	FILE *bulle;
	int i;
	bulle = fopen("Save\\B.txt", "w");
	for (i = 0; i < 6; i++)
		fprintf(bulle, "%d %d %d\n", bu[i].bx, bu[i].by, bu[i].stat);
	fclose(bulle);
}
void SaveEnemBull()
{
	FILE *enembull;
	int i;
	enembull = fopen("Save\\EB.txt", "w");
	for (i = 0; i < 2; i++)
		fprintf(enembull, "%d %d %d\n", eb[i].bullx, eb[i].bully, eb[i].stats);
	for (i = 0; i < 2; i++)
		fprintf(enembull, "%d %d %d\n", eb2[i].bullx, eb2[i].bully, eb2[i].stats);
	for (i = 0; i < 2; i++)
		fprintf(enembull, "%d %d %d\n", eb2[i].bullx, eb2[i].bully, eb2[i].stats);
	fclose(enembull);
}
void LoadGirl()
{
	FILE *py;
	py = fopen("Save\\P.txt", "r");
	fprintf(py, "%d %d %d %d %d %d %d %d %d", &girlx, &girly, &jumpy, &girlface, &girlindex, &jump, &jumpUp, &score);
	fclose(py);
}
void LoadEnemy()
{
	FILE *en;
	int i;
	en = fopen("Save\\E.txt", "r");
	for (i = 0; i < 3; i++)
		fscanf(en, "%d %d %d %d %d", &enem[i].ex, &enem[i].ey, &enem[i].life, &enem[i].shooter, &enem[i].state);
	fclose(en);
}
void LoadBullets()
{
	FILE *bul;
	int i;
	bul = fopen("Save\\B.txt", "r");
	for (i = 0; i < 6; i++)
		fscanf(bul, "%d %d %d\n", &bu[i].bx, &bu[i].by, &bu[i].stat);
	fclose(bul);
}
void LoadEB()
{
	FILE *enembul;
	int i;
	enembul = fopen("Save\\EB.txt", "r");
	for (i = 0; i < 2; i++)
		fscanf(enembul, "%d %d %d\n", &eb[i].bullx, &eb[i].bully, &eb[i].stats);
	for (i = 0; i < 2; i++)
		fscanf(enembul, "%d %d %d\n", &eb2[i].bullx, &eb2[i].bully, &eb2[i].stats);
	for (i = 0; i < 2; i++)
		fscanf(enembul, "%d %d %d\n", &eb2[i].bullx, &eb2[i].bully, &eb2[i].stats);
	fclose(enembul);
}
void firstenemy()
{
	if (mstate == 1 && estate == 0)
	{
		enem[0].life = 20;
		enem[0].state = 1;
		enem[0].ex = 1170 + rand() % 50;
		enem[0].ey = 0;
		estate = 1;
	}
	else
		return;

}
void E1Shoot()
{
	if (mstate == 1 && enem[0].state == 1)
		enem[0].shooter = 1;
}
void E2Shoot()
{
	if (mstate == 1 && enem[1].state == 1)
		enem[1].shooter = 1;
}
void E3Shoot()
{
	if (mstate == 1 && enem[2].state == 1)
		enem[2].shooter = 1;
}
void HSchecker()
{
	int i,j,t,k;
	char st[11];
	FILE *fp;
	fp = fopen("Hall of Fame.txt", "r");
	for (i = 0; i < 5; i++)
		fscanf(fp, "%s %d", &hs[i].name, &hs[i].score);
	fclose(fp);
	for (i = 0; i < 5; i++)
	{
		if (score >= hs[i].score)
		{
			t = hs[i].score;
			hs[i].score = score;
			score = t;
			strcpy(st, hs[i].name);
			strcpy(hs[i].name, str2);
			strcpy(str2, st);
			hs[5].score = score;
			strcpy(hs[5].name, str2);
			break;
		}
	}
	for (j = i; j < 6; j++)
	{
		for (k = j+1; k < 6; k++)
		{
			if (hs[k].score >= hs[j].score)
			{
				t = hs[k].score;
				hs[k].score = hs[j].score;
				hs[j].score = t;
				strcpy(st, hs[k].name);
				strcpy(hs[k].name, hs[j].name);
				strcpy(hs[j].name, st);
			}
		}
	}
	fp = fopen("Hall of Fame.txt", "w");
	for (i = 0; i < 5; i++)
		fprintf(fp, "%s %d\n", hs[i].name, hs[i].score);
	fclose(fp);
}
void HSshow()
{
	FILE *fp;
	fp = fopen("Hall of Fame.txt", "r");
	char sc0[4], sc1[4], sc2[4], sc3[4], sc4[4];
	int i;
	for (i = 0; i < 5; i++)
		fscanf(fp, "%s %d", &hs[i].name, &hs[i].score);
	fclose(fp);
	itoa(hs[0].score, sc0, 10);
	itoa(hs[1].score, sc1, 10);
	itoa(hs[2].score, sc2, 10);
	itoa(hs[3].score, sc3, 10);
	itoa(hs[4].score, sc4, 10);
	iSetColor(255,0,0);
	iText(65, 445, hs[0].name, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(65, 365, hs[1].name, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(65, 285, hs[2].name, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(65, 205, hs[3].name, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(65, 125, hs[4].name, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1020, 445, sc0, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1020, 365, sc1, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1020, 285, sc2, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1020, 205, sc3, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1020, 125, sc4, GLUT_BITMAP_TIMES_ROMAN_24);
}
void scoreupdate()
{
	itoa(score, scor, 10);
}
void SetVarZero()
{
	int i;
	bc = 0;
	stand = true;
	steps = 0;
	jump = false;
	jumpUp = false;
	jumpy = 0;
	girlface = 1;
	score = 0;
	shootstatus = 0;
	estate = 0;
	hstate = 0;
	t = 0;
	e1c = 0, e2c = 0, e3c = 0;
	girlindex = 0;
	girlx = 0;
	girly = 0;
	girllife = 25;
	enem[0].state = 0;
	enem[1].state = 0;
	enem[2].state = 0;
	for (i = 0; i < 6; i++)
	{
		bu[i].stat = 0;
		bu[i].bx = -1;
		bu[i].by = 0;
	}
	for (i = 0; i < 2; i++)
	{
		eb[i].stats = 0;
		eb[i].bullx = -1;
		eb[i].bully = -1;
	}
	for (i = 0; i < 2; i++)
	{
		eb2[i].stats = 0;
		eb2[i].bullx = -1;
		eb2[i].bully = -1;
	}
	for (i = 0; i < 2; i++)
	{
		eb3[i].stats = 0;
		eb3[i].bullx = -1;
		eb3[i].bully = -1;
	}
}
void setuserzero()
{
	str[0] = '\0';
	str2[0] = '\0';
	len = 0;
}
int main()
{	
	int ya = 100;
	for (int i = 3; i >= 0; i--)
	{
		but[i].x = 100;
		but[i].y = ya;
		ya += 162;
	}
	if (mstate == -1 || mstate == 0 || mstate == 3 || mstate == 4)
	{
		PlaySound("Sounds\\1.wav", NULL, SND_LOOP | SND_ASYNC);
	}
	enem[1].state = 0;
	enem[2].state = 0;
	iSetTimer(7000, EnemyVariables);
	iSetTimer(40, jump_change);
	iSetTimer(1, bulletmove);
	iSetTimer(1000, enemysliding);
	iSetTimer(1, firstenemy);
	iSetTimer(2000, E1Shoot);
	iSetTimer(2000, E2Shoot);
	iSetTimer(2000, E3Shoot);
	iSetTimer(1, scoreupdate);
	iInitialize(1440, 810, "Boss Fight With Gunmen");
	return 0;
}
