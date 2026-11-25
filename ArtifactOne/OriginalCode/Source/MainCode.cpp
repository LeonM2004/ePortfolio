#include <GLFW\glfw3.h>
#include "linmath.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include <time.h>

using namespace std;

const float DEG2RAD = 3.14159 / 180;

void processInput(GLFWwindow* window);

enum BRICKTYPE { REFLECTIVE, DESTRUCTABLE, PADDLE };
enum ONOFF { ON, OFF };

class Brick
{
public:
	float red, green, blue;
	float x, y, width;
	int stamina; // Checks how much energy each bricks have
	BRICKTYPE brick_type;
	ONOFF onoff;

	Brick(BRICKTYPE bt, float xx, float yy, float ww, float rr, float gg, float bb)
	{
		brick_type = bt; x = xx; y = yy, width = ww; red = rr, green = gg, blue = bb;
		onoff = ON;
		stamina = 3;

	};

	void drawBrick()
	{
		if (onoff == ON)
		{
			double halfside = width / 2;

			glColor3d(red, green, blue);
			glBegin(GL_POLYGON);

			glVertex2d(x + halfside, y + halfside);
			glVertex2d(x + halfside, y - halfside);
			glVertex2d(x - halfside, y - halfside);
			glVertex2d(x - halfside, y + halfside);

			glEnd();
		}
	}
};

Brick paddle(PADDLE, -0.0, -1.1, 0.3, 1, 0, 1);

class Circle
{
public:
	float red, green, blue;
	float radius;
	float x;
	float y;
	float speed = 0.03;
	int direction; // 1=up 2=right 3=down 4=left 5 = up right   6 = up left  7 = down right  8= down left
	ONOFF onoff;
	int strength;

	Circle(double xx, double yy, double rr, int dir, float rad, float r, float g, float b)
	{
		x = xx;
		y = yy;
		radius = rr;
		red = r;
		green = g;
		blue = b;
		radius = rad;
		direction = dir;
		onoff = ON;
		strength = 1;
	}

	void CheckCollision(Brick* brk)
	{
		if (brk->brick_type == REFLECTIVE && onoff == ON) // Reflective blocks serve to bounce the circles off and increase speed
		{
			if ((x > brk->x - brk->width && x <= brk->x + brk->width) && (y > brk->y - brk->width && y <= brk->y + brk->width))
			{
				direction = GetRandomDirection();
				x = x + 0.03;
				y = y + 0.04;

				speed += 0.01;
			}
		}
		else if (brk->brick_type == PADDLE && onoff == ON) // Paddle serves to increase the circles speed and is controllable
		{
			if ((x > brk->x - brk->width && x <= brk->x + brk->width) && (y > brk->y - brk->width && y <= brk->y + brk->width))
			{
				direction = GetRandomDirection();
				x = x + 0.03;
				y = y + 0.04;

				speed += 0.01;
			}
		}

		else if (brk->brick_type == DESTRUCTABLE && brk->onoff == ON
			&& brk->stamina > 0 && onoff == ON)
		{

			if ((x > brk->x - brk->width && x <= brk->x + brk->width) && (y > brk->y - brk->width && y <= brk->y + brk->width))
			{

				// Stamina decreases after colliding with the circles
				brk->stamina--;
				if (brk->stamina <= 0)
				{
					brk->onoff = OFF;
					speed -= 0.01;
				} // if statement erases the blocks after being hit enough times and decreases the ball's speed
				brk->green = 1;

				direction = GetRandomDirection();
				x = x + 0.03;
				y = y + 0.04;
			}

		}
	}

	void CheckCircleCollision(Circle &circles) // Checks whether the circles have actually made contact
	{
		float xDist = this->x *= -1;
		float yDist = this->y *= -1;
		float distance = sqrt((xDist * xDist) + (yDist * yDist));

		if (this->radius + circles.x)
		{
			this->radius = this->radius / 2.0f;
			circles.radius = circles.radius / 2.0f;
		}
	}

	int GetRandomDirection()
	{
		return (rand() % 8) + 1;
	}

	void MoveOneStep()
	{
		if (direction == 1 || direction == 5 || direction == 6)  // up
		{
			if (y > -1 + radius)
			{
				y -= speed;
			}
			else
			{
				direction = GetRandomDirection();
			}
		}

		if (direction == 2 || direction == 5 || direction == 7)  // right
		{
			if (x < 1 - radius)
			{
				x += speed;
			}
			else
			{
				direction = GetRandomDirection();
			}
		}

		if (direction == 3 || direction == 7 || direction == 8)  // down
		{
			if (y < 1 - radius) {
				y += speed;
			}
			else
			{
				direction = GetRandomDirection();
			}
		}

		if (direction == 4 || direction == 6 || direction == 8)  // left
		{
			if (x > -1 + radius) {
				x -= speed;
			}
			else
			{
				direction = GetRandomDirection();
			}
		}
	}

	void DrawCircle()
	{
		glColor3f(red, green, blue);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++) {
			float degInRad = i * DEG2RAD;
			glVertex2f((cos(degInRad) * radius) + x, (sin(degInRad) * radius) + y);
		}
		glEnd();
	}
};


vector<Circle> world;


int main(void) {
	srand(time(NULL));

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window = glfwCreateWindow(480, 480, "8-2 Assignment", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	Brick brick(DESTRUCTABLE, -0.8, 0.67, 0.2, 0, 1, 0);
	Brick brick1(DESTRUCTABLE, -0.6, 0.33, 0.2, 1, 0, 0);
	Brick brick2(REFLECTIVE, -0.4, 0.0, 0.2, 0, 0, 1);
	Brick brick3(DESTRUCTABLE, -0.2, 0.33, 0.2, 1, 0, 0);
	Brick brick4(DESTRUCTABLE, 0.0, 0.67, 0.2, 0, 1, 0);
	Brick brick5(DESTRUCTABLE, 0.2, 0.33, 0.2, 1, 0, 0);
	Brick brick6(REFLECTIVE, 0.4, 0.0, 0.2, 0, 0, 1);
	Brick brick7(DESTRUCTABLE, 0.6, 0.33, 0.2, 1, 0, 0);
	Brick brick8(DESTRUCTABLE, 0.8, 0.67, 0.2, 0, 1, 0);

	while (!glfwWindowShouldClose(window)) {
		//Setup View
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window);

		for (int i = 0; i < world.size(); i++)
		{
			world[i].CheckCollision(&paddle);
			world[i].CheckCollision(&brick);
			world[i].CheckCollision(&brick2);
			world[i].CheckCollision(&brick3);
			world[i].CheckCollision(&brick4);
			world[i].CheckCollision(&brick5);
			world[i].CheckCollision(&brick6);
			world[i].CheckCollision(&brick7);
			world[i].CheckCollision(&brick8);
			world[i].MoveOneStep();
			world[i].DrawCircle();
		}

		paddle.drawBrick();
		brick.drawBrick();
		brick1.drawBrick();
		brick2.drawBrick();
		brick3.drawBrick();
		brick4.drawBrick();
		brick5.drawBrick();
		brick6.drawBrick();
		brick7.drawBrick();
		brick8.drawBrick();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate;
	exit(EXIT_SUCCESS);
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		double r, g, b;
		r = rand() / 10000;
		g = rand() / 10000;
		b = rand() / 10000;
		Circle B(0, 0, 02, 2, 0.05, r, g, b);
		B.direction = B.GetRandomDirection();
		world.push_back(B);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && paddle.x > -1.0f)
	{
		paddle.x -= 0.05;
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && paddle.x < 1.0f)
	{
		paddle.x += 0.05;
	}
}