#pragma once
namespace {
	int score;
};
void ScoreInit();
void ScoreDraw();

// スコアに点数を加算します
int ScoreAdd(int val = score);
