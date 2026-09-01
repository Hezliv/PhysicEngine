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

	float getCellSize() {
		return cellSize;
	}

	SpatialGrid(int windowWidth, int windowHeight, int cellSize = 64.0f) : cellSize(cellSize) {
		cols = static_cast<int>(windowWidth / cellSize);
		rows = static_cast<int>(windowHeight / cellSize);

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
		set<pair<RigidBody*, RigidBody*>> uniq;
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				const auto& list = grid[r][c].bodies;
				size_t size = list.size();
				if (size < 2) continue;

				for(int i = 0; i < size; i++)
				{
					for (int j = i + 1; j < size; j++)
					{
						RigidBody* a = list[i];
						RigidBody* b = list[j];
						if (a > b)
						{
							swap(a, b);
						}
						uniq.insert({ a, b });
					}
				}
			}
		}
		return uniq;
	}

	void refresh(vector<RigidBody*>& bodies) {
		clear();
		for (int i = 0; i < bodies.size(); i++) {
			
			insert(bodies[i]);
		}
	}
	void refresh(RigidBody* body) {
		clear();
		insert(body);
	}

	void draw(sf::RenderWindow& window, sf::Vector2f position,  sf::Color color = sf::Color::Green) {
		sf::RectangleShape rect;
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineThickness(-1.0f);
		rect.setOutlineColor(color);
		rect.setSize({ cellSize - 5, cellSize - 5 });
		rect.setPosition(position);
		window.draw(rect);
	}

	void draw(sf::RenderWindow& window,sf::Color color = sf::Color(100, 100, 100, 200)) {
		sf::RectangleShape rect;
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineThickness(-1.0f); 
		rect.setOutlineColor(color);
		rect.setSize({ cellSize - 5, cellSize - 5 });
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				sf::Vector2f pos = { j * cellSize + 5, i * cellSize + 5 };
				rect.setPosition(pos);
				window.draw(rect);
			}
		}
	}
};
