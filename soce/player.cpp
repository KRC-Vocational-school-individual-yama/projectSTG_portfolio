#include "player.h"
#include <DxLib.h>
#include <assert.h>
#include "common.h"
#include "stones.h"
#include "config.h"
#include"enemies.h"
#include "score.h"
#include<vector>
#include"app.h"

namespace {
	int hImage = -1;
	int hImageDead = -1;
	int hSound = -1;
	POSITION pos;
	bool spacePushed = true;
	int throwCounter = 0;

	bool playerdeadflag = false;

	int mousex=0,
		  mousey=0;
	int mousezenkaix=0, 
		  mousezenkaiy=0;
	float mousekekkax=0.0f,
		  mousekekkay=0.0f;
};

void PlayerInit()
{
	//hImage = LoadGraph("data\\texture\\aoi.png");
	//assert(hImage>0);
	hImage = LoadGraph("data\\texture\\new_sozai–¢’è\\‹@‘Ì1.png");
	assert(hImage > 0);
	hImageDead=LoadGraph("data\\texture\\Fireball Explosion.png");
	assert(hImageDead>0);
	hSound = LoadSoundMem("data\\sound\\throw.wav");
	assert(hSound > 0);
	ChangeVolumeSoundMem(255 * 30 / 100, hSound);
	pos.x = 0.0;
	pos.y = 400.0;
	spacePushed = true;
	throwCounter = 0;
	playerdeadflag = false;
	mousex		 = 0;
	mousey		 = 0;
	mousezenkaix = 0/*SCREEN_WIDTH/2 */;
	mousezenkaiy = 0/*SCREEN_HEIGHT/2*/;
	mousekekkax	 = 0.0f;
	mousekekkay	 = 0.0f;
	SetMousePoint(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
}

void PlayerRelease()
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
void PlayerKeyControl() {
	pos.x = (double)mousex-32;
	pos.y = (double)mousey-32;
	if (CheckHitKey(KEY_INPUT_W)) {
		pos.y -= 3.0;
		if (pos.y < 0)
			pos.y = 0;
		SetMousePoint(mousex,mousey);
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		pos.y += 3.0;
		if (pos.y > SCREEN_HEIGHT - 64)
			pos.y = SCREEN_HEIGHT - 64;
		SetMousePoint(mousex, mousey);
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		pos.x -= 3.0;
		if (pos.x < 0)
			pos.x = 0;
		SetMousePoint(mousex, mousey);
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		pos.x += 3.0;
		if (pos.x > SCREEN_WIDTH - 64)
			pos.x = SCREEN_WIDTH - 64;
		SetMousePoint(mousex, mousey);
	}
}
void PlayerUpdate()
{
	GetMousePoint(&mousex,&mousey);
	if (!playerdeadflag) {
		PlayerKeyControl();

		bool push = CheckHitKey(KEY_INPUT_SPACE);
		bool pushMouse = GetMouseInput()&MOUSE_INPUT_LEFT;
		if ((push||pushMouse) /*&& !spacePushed*/) {
			
			if (throwCounter == 0) {
				POSITION p = { pos.x + 28 ,pos.y + 12 };
				if (ScoreAdd() >= 200) {
					int num = 6;
					POSITION vect;
					for (int i = 0; i < num; i++) {
						vect.x = cos(3.14 / 180 * (i * 360 / num)) * 10.0f;
						vect.y = sin(3.14 / 180 * (i * 360 / num)) * 10.0f;
						CreateStone(p, vect);
					}
				}
				POSITION vec = {0,-5};
				CreateStone(p,vec);
				/*if (ScoreAdd()>= 100) {
					POSITION vec[2] = { 2,-5 ,-2,-5};
					CreateStone(p, vec[0]);
					CreateStone(p, vec[1]);
				}*/
					int scoad = ScoreAdd() / 100+1;
					//if (scoad >= 3)scoad = 3;
					std::vector<POSITION> r(scoad);
					std::vector<POSITION> l(scoad);
				for (int i = 0; i < scoad; i++) {
					if (i == 0)continue;
					POSITION rvc = { 0+ (i * 2),-5 };
					r[i] = rvc;
					POSITION lvc = { 0 - (i * 2),-5 };
					l[i] = lvc;
					CreateStone(p,r[i]);
					CreateStone(p,l[i]);
				}
				
				PlaySoundMem(hSound, DX_PLAYTYPE_BACK);
				throwCounter = 10;
			}
		}
		if (throwCounter > 0)
			throwCounter--;
		spacePushed = push;
	}

	//printfDx("%d\n",throwCounter);

	CIRCLE c;
	c.x = pos.x+32;
	c.y = pos.y+32;
	c.r = 32;
	if (EnemyCollidePlayer(c)) {
		playerdeadflag = true;
	}
	if (playerdeadflag&&GetMouseInput()&MOUSE_INPUT_RIGHT) {
		ChangeScene(TITLE_SCENE);
	}
}

void PlayerDraw()
{
	int cellX = 0;
	int cellY = 0;
	if (throwCounter>0) {
		cellY = 1*64;
		cellX = 2*64;
	}
	
	int imgssize = 64;
	if (playerdeadflag) {
		DrawExtendGraph((int)pos.x, (int)pos.y, (int)pos.x + imgssize, (int)pos.y + imgssize,
			hImageDead, TRUE);
	}
	else {
		DrawExtendGraph((int)pos.x, (int)pos.y, (int)pos.x+ imgssize, (int)pos.y+ imgssize, hImage, TRUE);
	}

	//DrawRectGraph((int)pos.x, (int)pos.y,
	//		cellX, cellY, 64, 64, hImage, TRUE);
}
