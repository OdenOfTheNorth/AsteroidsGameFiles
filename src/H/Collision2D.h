#pragma once
#include "GameObject.h"
#include <map>
#include <math.h>
#include <iostream>
#include <vector>

struct CollsionGridCell
{
	std::vector<GameObject*> collidersInCell;

	int neighboorsIndex[8];

public:
	void RemoveObj(GameObject* objToRemove)
	{
		for (size_t i = 0; i < collidersInCell.size(); i++)
		{
			if (collidersInCell[i] == objToRemove)
			{
				collidersInCell.erase(collidersInCell.begin() + i);
			}
		}
	}
};

class Collision2D
{
public:
	Collision2D(Vector2 screenS);
	void AddCollider(GameObject* objectToAdd);
	void RemoveCollider(GameObject* objectToRemove);
	void Update();
	bool CheckCollisionMatrix(int layer,int collsionMatrix);

private:

	std::vector<GameObject*> colliders;

	std::vector<CollsionGridCell> collisionGrid;
	double GridSize = 60;

	int gridCountX, gridCountY;

	Vector2 screenSize;
};

