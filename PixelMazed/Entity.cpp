#include "Entity.h"
#include <math.h>

void Entity::setforwardV(float x, float y) {
	forwardV[0] = x; forwardV[1] = y;
	Xrotation = atan2(y, x);
}