#include "Vector2.h"
#include <stdlib.h>
#include <iostream>

Vector2::Vector2(double xValue = 0, double yValue  = 0)
{
	x = xValue;
	y = yValue;
}
Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::~Vector2()
{
}

Vector2 Vector2::Clamp(Vector2 pos, Vector2 min, Vector2 max)
{
	if (pos.x > max.x)
	{
		pos.x = max.x;
	}
	else if(pos.x < min.x)
	{
		pos.x = min.x;
	}

	if (pos.y > max.y)
	{
		pos.y = max.y;
	}
	else if(pos.y < min.y)
	{
		pos.y = min.y;
	}
	return pos;
}

double Vector2::AngleFromDirection(Vector2 direction)
{
	return atan2(direction.y, direction.x);
}

Vector2 Vector2::DirectionFromAngle(double angle)
{
	Vector2 dir = Vector2(0,0);

	dir.x = cos(angle);
	dir.y = sin(angle);

	return dir;
}

Vector2 Vector2::GetRotatedVector(Vector2 direction, double angle)
{
	double angleRad = angle * GameMath::degToRad();

	double cs = cos(angleRad);
	double sn = sin(angleRad);

	double px = direction.x * cs - direction.y * sn;
	double py = direction.x * sn + direction.y * cs;

	return Vector2(px, py);
}

Vector2 Vector2::RotateTowards(Vector2 from, Vector2 to, double speed)
{
	double angledifference = Vector2::AngleFromDirection(to) - Vector2::AngleFromDirection(to);
	if (angledifference > 0) angledifference = 1;
	else if (angledifference < 0) angledifference = -1;

	return Vector2::GetRotatedVector(from, angledifference * speed);
}

Vector2 Vector2::Normalized()
{
	double magn = Magnitude();
	return Vector2(x / magn, y / magn);
}

double Vector2::Distance(Vector2 distanceFrom, Vector2 distanceTo)
{
	return Distance(distanceFrom.x, distanceFrom.y, distanceTo.x, distanceTo.y);
}

double Vector2::Distance(double distanceFromX, double distanceFromY, double distanceToX, double distanceToY)
{
	double power = pow(distanceFromX - distanceToX, 2) + pow(distanceFromY - distanceToY, 2) * 1.0;

	return sqrt(power);
}

double Vector2::Dot(Vector2 a, Vector2 b)
{
	return a.x * b.x + a.y * b.y;
}

Vector2 Vector2::Perpendicular(Vector2 vector, bool isClockwise)
{
	if (isClockwise) 
	{
		return Vector2(vector.y, -vector.x);

	}
	else 
	{
		return Vector2(-vector.y, vector.x);
	}
}

Vector2 Vector2::GetDirection(Vector2 from, Vector2 to)
{
	return to - from;
}

Vector2 Vector2::GetNormalizedDirection(Vector2 from, Vector2 to)
{
	return (to - from).Normalized();
}

Vector2 Vector2::Lerp(Vector2 from, Vector2 to, double f)
{
	return Vector2(GameMath::lerp(from.x, to.x, f), GameMath::lerp(from.y, to.y, f));
}

void Vector2::Normalize()
{
	Vector2 normalizedVector = Normalized();
	x = normalizedVector.x;
	y = normalizedVector.y;
}

Vector2 Vector2::operator+(const Vector2 v)
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2 v)
{
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator-()
{
	return Vector2(0 - x, 0 - y);
}

Vector2 Vector2::operator*(const double d)
{
	return Vector2(x * d, y * d);
}

Vector2 Vector2::operator/(const double d)
{
	return Vector2(x / d, y / d);
}

void Vector2::operator+=(const Vector2 & v)
{
	this->x += v.x;
	this->y += v.y;
}



