#include "Collision2D.h"

Collision2D::Collision2D(Vector2 screenS)
{
	screenSize = screenS;

	gridCountX = ceil(screenSize.x / GridSize);
	gridCountY = ceil(screenSize.y / GridSize);

	int collisionGridSize = gridCountX * gridCountY;

	std::cout << collisionGridSize - 1 << " gridXMAX: " << gridCountX << " gridYMAX: " << gridCountY << std::endl;

	for (int i = 0; i < collisionGridSize; i++)
	{
		collisionGrid.push_back(CollsionGridCell());
		int y = floor(i / gridCountX);
		int x = i - y * gridCountX;

		//Upper Left
		if (x - 1 >= 0 && y - 1 >= 0) collisionGrid[i].neighboorsIndex[0] = (x - 1) + (y - 1) * gridCountX;
		else collisionGrid[i].neighboorsIndex[0] = -1;
		//Upper middle
		if (y - 1 >= 0) collisionGrid[i].neighboorsIndex[1] = (x)+(y - 1) * gridCountX;
		else collisionGrid[i].neighboorsIndex[1] = -1;
		//Upper Right
		if (x + 1 < gridCountX && y - 1 >= 0) collisionGrid[i].neighboorsIndex[2] = (x + 1) + (y - 1) * gridCountX;
		else collisionGrid[i].neighboorsIndex[2] = -1;
		//Right
		if (x + 1 < gridCountX) collisionGrid[i].neighboorsIndex[3] = (x + 1) + (y)* gridCountX;
		else collisionGrid[i].neighboorsIndex[3] = -1;
		//LowerRight
		if (x + 1 < gridCountX && y + 1 < gridCountY) collisionGrid[i].neighboorsIndex[4] = (x + 1) + (y + 1) * gridCountX;
		else collisionGrid[i].neighboorsIndex[4] = -1;
		//Lower Middle
		if (y + 1 < gridCountY) collisionGrid[i].neighboorsIndex[5] = (x)+(y + 1) * gridCountX;
		else collisionGrid[i].neighboorsIndex[5] = -1;
		//Lower Left
		if (x - 1 >= 0 && y + 1 < gridCountY) collisionGrid[i].neighboorsIndex[6] = (x - 1) + (y + 1) * gridCountX;
		else collisionGrid[i].neighboorsIndex[6] = -1;
		//Left
		if (x - 1 >= 0) collisionGrid[i].neighboorsIndex[7] = (x - 1) + (y)* gridCountX;
		else collisionGrid[i].neighboorsIndex[7] = -1;


		//std::cout << "index: " << i << " X: " << x << " Y: " << y << std::endl;
//std::cout << "1: " << collisionGrid[i].neighboorsIndex[0] << " 2: " << collisionGrid[i].neighboorsIndex[1] << std::endl;
//std::cout << "3: " << collisionGrid[i].neighboorsIndex[2] << " 4: " << collisionGrid[i].neighboorsIndex[3] << std::endl;
//std::cout << "5: " << collisionGrid[i].neighboorsIndex[4] << " 6: " << collisionGrid[i].neighboorsIndex[5] << std::endl;
//std::cout << "7: " << collisionGrid[i].neighboorsIndex[6] << " 8: " << collisionGrid[i].neighboorsIndex[7] << std::endl;
//std::cout << std::endl;
	}
	//(x,y)
//(-1,1) index - gridcountx - 1
//(0,1) index - gridcountx
//(1,1) index - gridcountx + 1
//(-1,0) index - 1
//(1,0) index + 1
//(-1,-1) index + gridcountx - 1
//(0,-1) index + gridcountx 
//(-0,-1) index + gridcountx + 1

//clamp x && y

}

void Collision2D::AddCollider(GameObject* gameObjectToAdd)
{
	colliders.push_back(gameObjectToAdd);

	Vector2 pos = gameObjectToAdd->GetRealPosition();

	if (pos.x > 0 && pos.x < screenSize.x && pos.y > 0 && pos.y < screenSize.y)
	{
		int gridX = floor(pos.x / GridSize);
		int gridY = floor(pos.y / GridSize);

		collisionGrid[gridX + gridY * gridCountX].collidersInCell.push_back(gameObjectToAdd);

		gameObjectToAdd->collisionCellX = gridX;
		gameObjectToAdd->collisionCellY = gridY;
		gameObjectToAdd->collisionCellIndex = gridX + gridY * gridCountX;

		//std::cout << "GridX: " << gridX << ", GridY: " << gridY << " Index: " << gridX + gridY * gridCountX << std::endl;

	}
}

void Collision2D::RemoveCollider(GameObject* objectToRemove)
{
}

void Collision2D::Update()
{
	for (int i = 0; i < colliders.size(); i++)
	{
		GameObject* obj = colliders[i];
		Vector2 pos = obj->GetRealPosition();
		double objRadius = obj->radius;


		if (!obj->isActive) continue;

		if (pos.x > 0 && pos.x < screenSize.x - 1 && pos.y > 0 && pos.y <= screenSize.y )
		{


			int gridX = floor(pos.x / GridSize);
			int gridY = floor(pos.y / GridSize);

			if (gridX != obj->collisionCellX || gridY != obj->collisionCellY)
			{
				int index = gridX + gridY * gridCountX;

				collisionGrid[index].collidersInCell.push_back(obj);
				collisionGrid[obj->collisionCellIndex].RemoveObj(obj);

				obj->collisionCellX = gridX;
				obj->collisionCellY = gridY;
				obj->collisionCellIndex = index;
			}


			//In cell collision
			for (int j = 0; j < collisionGrid[obj->collisionCellIndex].collidersInCell.size(); j++)
			{
				GameObject* collider = collisionGrid[obj->collisionCellIndex].collidersInCell[j];

				if (collider != obj)
				{					
					if (!collider->isActive) continue;
					if (!CheckCollisionMatrix(collider->layer, obj->collisionMatrix)) continue;
					//std::cout << "true" << std::endl;

					Vector2 colliderPos = collider->GetRealPosition();
					double colliderRadius = collider->radius;

					//overlap circle
					if (fabs((pos.x - colliderPos.x) * (pos.x - colliderPos.x) 
						+ (pos.y - colliderPos.y) * (pos.y - colliderPos.y)) 
						<= (obj->radius + colliderRadius) * (obj->radius + colliderRadius))
					{
						obj->OnCollision();
						collider->OnCollision();
					}
				}
			}


			for (int j = 0; j < 8; j++)
			{

				int neighboorIndex = collisionGrid[obj->collisionCellIndex].neighboorsIndex[j];

				if (neighboorIndex == -1) continue;

				for (int k = 0; k < collisionGrid[neighboorIndex].collidersInCell.size(); k++)
				{

					GameObject* colliderObj = collisionGrid[neighboorIndex].collidersInCell[k];
					Vector2 colliderPos = colliderObj->GetRealPosition();
					double colliderRadius = colliderObj->radius;

					if (!colliderObj->isActive) continue;
					if (!CheckCollisionMatrix(colliderObj->layer,obj->collisionMatrix)) continue;	
					//std::cout << "true" << std::endl;

					//overlap circle
					if (fabs((pos.x - colliderPos.x) * (pos.x - colliderPos.x)
						+ (pos.y - colliderPos.y) * (pos.y - colliderPos.y))
						<= (obj->radius + colliderRadius) * (obj->radius + colliderRadius))
					{
						obj->OnCollision();
						colliderObj->OnCollision();
					}

				}
			}
		}
	}
}

bool Collision2D::CheckCollisionMatrix(int layer, int collsionMatrix)
{
	//std::cout << collsionMatrix << " " << layer << " " << ((collsionMatrix >> layer) & 1) << std::endl;
	bool check = (collsionMatrix & layer);
	return check;
}
