#include "enemies.h"
#include <DxLib.h>
#include <assert.h>
#include "common.h"
#include "config.h"

#include"score.h"
#include<math.h>
#define PI 3.14159265359

namespace {
	struct ENEMY {
		bool active;
		POSITION pos;
		int animCounter;
		int deadCounter;
		double circleCounter;
		int fastOblique=2;
	};
	static const int ENEMY_NUM = 20;
	ENEMY enemies[ENEMY_NUM];
	int spawnCounter = 60;
	int hImage = -1;
	bool kirikae = false;
};

void EnemiesInit()
{
	hImage = LoadGraph("data\\texture\\uirusu.png");
	assert(hImage > 0);
	//hImage = LoadGraph("data\\texture\\mob.png");
	//assert(hImage>0);

	for (int i = 0; i < ENEMY_NUM; i++) {
		enemies[i].active = false;
		enemies[i].circleCounter = 0;
	}

	spawnCounter = 30;
	kirikae = false;
}

void EnemiesUpdate()
{
	// “G‚ğ¶¬‚·‚é
	if (--spawnCounter<=0) {
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (!enemies[i].active) {
				
				if (ScoreAdd() >= 50) {
					enemies[i].fastOblique= GetRand(850-50)+50;

					enemies[i].pos.x = cos(PI / 180 * 60) * enemies[i].fastOblique	+300;
					enemies[i].pos.y = tan(PI/180*60)*enemies[i].pos.x				+10;
				}
				else {
					enemies[i].pos.x = GetRand(SCREEN_WIDTH - 64);
					enemies[i].pos.y = -64;
				}
				enemies[i].active = true;
				enemies[i].animCounter = 0;
				enemies[i].deadCounter = 0;
				break;
			}
		}
		spawnCounter = 10;
	}

	// “G‚ğs“®‚·‚é
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (!enemies[i].active)
			continue;
		if (enemies[i].deadCounter==0) { // ¶‚«‚Ä‚¢‚é
			if (ScoreAdd() >= 50) {
				enemies[i].circleCounter += 1 - (1 * enemies[i].fastOblique / 850);
				enemies[i].pos.x=(double)(cos(PI/180*enemies[i].circleCounter)*enemies[i].fastOblique+300);
				enemies[i].pos.y=(double)(sin(PI/180*enemies[i].circleCounter)*enemies[i].fastOblique+10 );
			}
			else {
			enemies[i].pos.y += 2.0f;
			}
			/*if (enemies[i].pos.y > SCREEN_HEIGHT+64||
				enemies[i].pos.x<0-64)
				enemies[i].active = false;*/
			bool flag = ScoreAdd() >= 50;
			if (flag!=kirikae) {
				kirikae = flag;
				for (int i = 0; i < ENEMY_NUM; i++) 
					enemies[i].active = false;
			}
			enemies[i].animCounter++;
		} else { // €‚ñ‚Å‚¢‚é
			if (++enemies[i].deadCounter>60)
				enemies[i].active = false;
			enemies[i].circleCounter = 0;
		}
	}
}

void EnemiesDraw()
{
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemies[i].active) {
			int pat = (enemies[i].animCounter/8)%4;
			if (enemies[i].deadCounter>0)
				pat = 4;
			
			DrawRectGraph((int)enemies[i].pos.x, (int)enemies[i].pos.y,
				0, pat*64, 64, 64, hImage, TRUE);
		}
	}
}

void EnemiesRelease()
{
	if (hImage>0) {
		DeleteGraph(hImage);
		hImage = -1;
	}
}

//“G‚ÆÎ‚Ì“–‚½‚è”»’è
bool EnemyCollideStone(CIRCLE stone)
{
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemies[i].active && enemies[i].deadCounter == 0) {
			CIRCLE my;
			my.x = (int)enemies[i].pos.x+32;
			my.y = (int)enemies[i].pos.y+32;
			my.r = 20;
			if (CircleCollision(my, stone)) {
				enemies[i].deadCounter=1;
				return true;
			}
		}
	}
	return false;
}
bool EnemyCollidePlayer(CIRCLE player) {
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemies[i].active&& enemies[i].deadCounter == 0) {
			CIRCLE my;
			my.x=(int)enemies[i].pos.x+32;
			my.y=(int)enemies[i].pos.y+32;
			my.r=20;
			if (CircleCollision(my, player)) {
				
				return true;
			}
		}
	}
	return false;
}
