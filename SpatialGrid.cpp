#include <iostream>
#include <cmath>
#include <algorithm>
#include <set>
#include <SFML/Graphics.hpp>
#include "rigidBody.h"
using namespace std;


class SpatialGrid {
	vector<int> head;
	vector<int> next;
	float cellSize;
	int cols;
	int rows;

public:

	float getCellSize() {
		return cellSize;
	}

	SpatialGrid(int windowWidth, int windowHeight, size_t& maxBodies, float cellSize = 64.0f) : cellSize(cellSize) {
		cols = static_cast<int>(windowWidth / cellSize);
		rows = static_cast<int>(windowHeight / cellSize);

		head.resize(rows * cols, -1);
		next.resize(maxBodies, -1);
	}

	void mapBodiesToCell(sf::RenderWindow& window, sf::Color color = sf::Color::White) { // ??????
		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				if (head[r * cols + c] != -1) {
					drawCell(window, r, c, color);
				}
			}
		}
	}

	void resize(size_t count) {
		head.resize(count);
		next.resize(count);
	}

	void clear() {
		fill(head.begin(), head.end(), -1);
	}

	void insert(int bodyInd, sf::Vector2f& pos) {
		int c = clamp(static_cast<int>(pos.x / cellSize), 0, cols - 1);
		int r = clamp(static_cast<int>(pos.y / cellSize), 0, rows - 1);

		int cell = r * cols + c;
		next[bodyInd] = head[cell];
		head[cell] = bodyInd;
	}

	void resolveCollision(vector<RigidBody*>& bodies) {
		const int neighborOffset[4][2] = {
			{0, 1},
			{1, -1},
			{1, 0},
			{1, 1}
		};
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				int cell = r * cols + c;
				int i = head[cell];
				while (i != -1) {
					int j = next[i];
					while (j != -1) {
						bodies[i]->resolveCollision(bodies[j]);
						j = next[j];
					}			
					i = next[i];
				}
				for (auto& offset : neighborOffset) {
					int nr = r + offset[0];
					int nc = c + offset[1];

					if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
						int neighborCell = nr * cols + nc;

						int curr = head[cell];
						while (curr != -1) {
							int k = head[neighborCell];
							while (k != -1) {
								bodies[curr]->resolveCollision(bodies[k]);
								k = next[k];
							}
							curr = next[curr];
						}
					}
				}
			}
		}
	}

	void refresh(vector<RigidBody*>& bodies) {
		clear();
		for (int i = 0; i < bodies.size(); i++) {
	
			sf::Vector2f p = bodies[i]->getPosition();
			insert(i, p);
		}
	}
	void refresh(RigidBody* body) {
		clear();
		sf::Vector2f p = body->getPosition();
		insert(0, p);
	}

	void drawGrid(sf::RenderWindow& window,sf::Color color = sf::Color(100, 100, 100, 200)) { // ????
		//size_t lineCount = (cols + 1) + (rows + 1);
		//sf::VertexArray lines(sf::PrimitiveType::Lines, lineCount * 2);

		//size_t idx = 0;
		//float totalW = cols * cellSize;
		//float totalH = rows * cellSize;

		//// Вертикальные линии
		//for (int c = 0; c <= cols; ++c) {
		//	float x = c * cellSize;
		//	lines[idx++] = sf::Vertex(sf::Vector2f(x, 0.0f), color);
		//	lines[idx++] = sf::Vertex(sf::Vector2f(x, totalH), color);
		//}

		//// Горизонтальные линии
		//for (int r = 0; r <= rows; ++r) {
		//	float y = r * cellSize;
		//	lines[idx++] = sf::Vertex(sf::Vector2f(0.0f, y), color);
		//	lines[idx++] = sf::Vertex(sf::Vector2f(totalW, y), color);
		//}

		//return lines;

		sf::RectangleShape rect;
		rect.setOutlineColor(color);
		rect.setOutlineThickness(-1.0f);
		rect.setFillColor(sf::Color::Transparent);
		rect.setSize({ cellSize - 6, cellSize - 6 });
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				rect.setPosition({ j * cellSize, i * cellSize });
				window.draw(rect);
			}
		}
	}
	void drawCell(sf::RenderWindow& window, int i, int j, sf::Color color = sf::Color(100, 100, 100, 200))
	{
		sf::RectangleShape rect;
		rect.setOutlineColor(color);
		rect.setOutlineThickness(-1.0f);
		rect.setFillColor(sf::Color::Black);
		rect.setSize({ cellSize - 6, cellSize - 6 });
		rect.setPosition({ j * cellSize, i * cellSize }); 
		window.draw(rect);
	}
};
