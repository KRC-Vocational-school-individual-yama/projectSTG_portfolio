#include "score.h"
#include <DxLib.h>



void ScoreInit()
{
	score = 0;
}

void ScoreDraw()
{
	DrawFormatString(10, 10, GetColor(255,255,255), "SCORE: %7d", score);
}

int ScoreAdd(int val)
{
	return
	score += val;
}
