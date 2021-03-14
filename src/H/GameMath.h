#pragma once
class GameMath
{
public:
	static double lerp(double a, double b, double f){return a + f * (b - a);}
	static double radToDeg() { return 57.2957795128961; }
	static double degToRad() { return 0.01745329252; }
}; 

