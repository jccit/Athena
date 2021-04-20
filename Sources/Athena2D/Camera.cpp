#include "Camera.h"

Camera::Camera()
{
}

Vec2 Camera::getPosition()
{
	return position;
}

void Camera::setPosition(Vec2 newPos)
{
	position = newPos;
}

void Camera::setPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}
