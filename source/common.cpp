#include "common.h"

bool CircleCollision(CIRCLE c1, CIRCLE c2)
{
	int dx = c1.x - c2.x;//座標の距離
	int dy = c1.y - c2.y;//Y座標の距離
	int rs = c1.r + c2.r;//半径の合算値
	if (dx*dx + dy*dy <= rs*rs)
		return true;//当たってる。
	return false;
}
