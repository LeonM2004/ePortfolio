///////////////////////////////////////////////////////////////////////////////
// model.h
// ============
// Manages the preparations for establishing the bricks, paddle, circle along with checking collision properties
// 
// NAME: Leonardo Marulanda
// DATE: 11/09/2026
// Created from CS-330 Computational Graphics and Visualization on 06/23/2026,
// Enhanced for CS-499 Computer Science Capstone
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>

enum BRICKTYPE { NORMAL, DURABLE, REFLECTIVE };
enum ONOFF { ON, OFF };

struct Brick
{
	float red, green, blue;
	float x, y, width;
	int stamina;
	BRICKTYPE brick_type;
	ONOFF onoff;

	Brick(BRICKTYPE bt, float xx, float yy, float ww, float rr, float gg, float bb) {
		brick_type = bt;
		x = xx; y = yy; width = ww;
		red = rr; green = gg; blue = bb;
		onoff = ON;
		// If-else statement for determining the bricktype's stamina
		if (bt == DURABLE) {
			stamina = 3;
		}
		if (bt == REFLECTIVE) {
			stamina = 2;
		}
		else {
			stamina = 1;
		}
	}
};

struct Paddle
{
	float x, y, width, height;
	float speed;
};

struct Circle
{
	float x, y, radius;
	float vx, vy; // Checks circle's horizontal and vertical velocity
};



///////////////////////////////////////////////////////////////////////////////
// Model
// 
// Class contains the code for preparing and rendering the bricks, paddle, and ball properties
///////////////////////////////////////////////////////////////////////////////
class Model
{
public:
	Model();
	void initLevel();
	void UpdatePhysics();
	void checkCollisions();

	std::vector<Brick>& getBricks() { return bricks; }
	Paddle& getPaddle() { return paddle; }
	Circle& getCircle() { return circle; }

private:
	std::vector<Brick> bricks;
	Paddle paddle;
	Circle circle;
};
