#include <iostream>
#include <cmath>
#include <algorithm>
#include <set>
#include <SFML/Graphics.hpp>
#include "rigidBody.h"
using namespace std;

class SpatialGrid {
	struct Cell {
		vector<RigidBody*> bodies;
	};

	vector<vector<Cell>> grid;
	float cellSize;
	int cols;
	int rows;

public:

	SpatialGrid(int windowWidth, int windowHeight, int cellSize = 64.0f) : cellSize(cellSize) {
		cols = windowWidth / cellSize;
		rows = windowHeight / cellSize;

		grid.resize(rows, vector<Cell>(cols));

	}

	void clear() {
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				grid[i][j].bodies.clear();
			}
		}
	}

	void insert(RigidBody* body) {
		float minX = body->getPosition().x - body->getRadius();
		float maxX = body->getPosition().x + body->getRadius();
		float minY = body->getPosition().y - body->getRadius();
		float maxY = body->getPosition().y + body->getRadius();

		int startCol = max(0, (int)(minX / cellSize));
		int endCol = min(cols - 1, (int)(maxX / cellSize));
		int startRow = max(0, (int)(minY / cellSize));
		int endRow = min(rows - 1, (int)(maxY / cellSize));
		for (int r = startRow; r <= endRow; r++)
		{
			for (int c = startCol; c <= endCol; c++)
			{
				grid[r][c].bodies.push_back(body);
			}
		}
	}

	set<pair<RigidBody*, RigidBody*>> getUniquePairs() {

	}

	void debugRender(sf::RenderWindow* window) {

	}
};
