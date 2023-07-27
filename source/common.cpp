#include "common.h"

bool CircleCollision(CIRCLE c1, CIRCLE c2)
{
	int dx = c1.x - c2.x;//���W�̋���
	int dy = c1.y - c2.y;//Y���W�̋���
	int rs = c1.r + c2.r;//���a�̍��Z�l
	if (dx*dx + dy*dy <= rs*rs)
		return true;//�������Ă�B
	return false;
}
