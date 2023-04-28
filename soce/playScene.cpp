#include "playScene.h"
#include <DxLib.h>
#include "app.h"
#include "player.h"
#include "stones.h"
#include "enemies.h"
#include "score.h"

#include<assert.h>
#include"config.h"

namespace {
	int h_imgs[2] = {};
	int count = 0;
	int count2 = 255;
}

void PlaySceneInit()
{
	PlayerInit();
	StonesInit();
	EnemiesInit();
	ScoreInit();
	h_imgs[0] = LoadGraph("data/texture/tuika_1107/tainai.png");
	assert(h_imgs[0]>0);
	h_imgs[1] = LoadGraph("data/texture/tuika_1107/kaiten.png");
	assert(h_imgs[1]>0);
	count = 0;
	count2 = 255;
}

void PlaySceneUpdate()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		ChangeScene(TITLE_SCENE);

	}
	PlayerUpdate();
	StonesUpdate();
	EnemiesUpdate();
}

void PlaySceneDraw()
{
	if(count2<=(15*6))count--;
	if (3.14/180*count/3==3.14 / 180 * 0) {
		count = 0;
	}
	int num = 50;
	bool levelflag = ScoreAdd() >= num;
	if(levelflag) {
		DrawRotaGraph2(SCREEN_WIDTH / 2, 10,
			1720 / 2, 1720 / 2, 1.0f, (3.14 / 180 * count / 3),
			h_imgs[1], FALSE)
			, DrawCircle(SCREEN_WIDTH / 2, 10, 10, GetColor(255, 255, 255))//âÒì]ì_ÅiíÜêS
			;
	}
	if (levelflag) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, count2 -= 15);
		if (count2 < 0)count2 = 0;
	}
	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
			h_imgs[0], FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		


	EnemiesDraw();
	PlayerDraw();
	StonesDraw();
	ScoreDraw();
	DrawString(600, 10, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(10, 500, "Push [T] Key To Title", GetColor(255, 255, 255));
}

void PlaySceneRelease()
{
	for(int i=0;i<2;i++)
		if (h_imgs[i] != -1) {
			DeleteGraph(h_imgs[i]);
			h_imgs[i] = -1;
		}
	PlayerRelease();
	StonesRelease();
	EnemiesRelease();
	
}