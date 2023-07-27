#include "stones.h"
#include <DxLib.h>
#include <assert.h>
#include "common.h"
#include "config.h"
#include "enemies.h"
#include "score.h"

namespace {
	struct STONE {
		bool active;
		POSITION pos;
		POSITION vector;
	};
	static const int STONE_NUM = 50;
	STONE stones[STONE_NUM];
	int hImage = -1;
	int hSound = -1;
};

void StonesInit()
{
	hImage = LoadGraph("data\\texture\\beam.png");
	assert(hImage>0);
	hSound = LoadSoundMem("data\\sound\\hit.wav");
	assert(hSound>0);
	ChangeVolumeSoundMem(255 * 50 / 100, hSound);
	for (int i=0; i<STONE_NUM; i++) {
		stones[i].active = false;
	}
}

void StonesRelease()
{
	if (hImage > 0) {
		DeleteGraph(hImage);
		hImage = -1;
	}
	if (hSound > 0) {
		DeleteSoundMem(hSound);
		hSound = -1;
	}
}

void StonesUpdate()
{
	for (int i = 0; i < STONE_NUM; i++) {
		if (stones[i].active) {
			stones[i].pos.x += stones[i].vector.x;
			stones[i].pos.y += stones[i].vector.y;
			if (stones[i].pos.y < 0-20||
				stones[i].pos.y>SCREEN_HEIGHT-20||
				stones[i].pos.x<0-20||
				stones[i].pos.x>SCREEN_WIDTH-20
				) {
				stones[i].active = false;
			}
			CIRCLE c;
			c.x = (int)stones[i].pos.x+10;
			c.y = (int)stones[i].pos.y+10;
			c.r = 10;
			if (EnemyCollideStone(c)) {
				stones[i].active = false;
				PlaySoundMem(hSound, DX_PLAYTYPE_BACK);
				ScoreAdd(10);
			}
		}
	}
}

void StonesDraw()
{
	for (int i = 0; i < STONE_NUM; i++) {
		0==i%2 ? 
			SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255)
		:
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255)
			;
		for(int j=0;j<5;j++)
		if (stones[i].active) {
			DrawGraph((int)stones[i].pos.x, (int)stones[i].pos.y,
				hImage, TRUE);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void CreateStone(POSITION _pos,POSITION _vector)
{
	for (int i=0; i<STONE_NUM; i++) {
		if (stones[i].active)
			continue;
		stones[i].pos = _pos;
		stones[i].vector =_vector;
		stones[i].active = true;
		return;
	}
}
