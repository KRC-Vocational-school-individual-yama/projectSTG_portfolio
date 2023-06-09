#pragma once

struct POSITION {
	double x;
	double y;
};

struct CIRCLE {
	int x, y; // 中心座標
	int r; // 半径
};


// 円と円の当たり判定を行う
// 当たっていればtrueを返す
bool CircleCollision(CIRCLE c1, CIRCLE c2);