///////////////////////////////////////////////////////////////////////////////
// view.cpp
// ============
// Manages the preparing and rendering for the statuses surrounding the brick, paddle, and circle
// 
// NAME: Leonardo Marulanda
// DATE: 11/09/2026
// Created from CS-330 Computational Graphics and Visualization on 06/23/2026,
// Enhanced for CS-499 Computer Science Capstone
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <GLFW\glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "linmath.h"
#include "view.h"

using namespace std;

const float DEG2RAD = 3.14159 / 180;

View::View() {
}

void View::drawBrick(const Brick& brick) {
	if (brick.onoff == OFF) return;

	// Establishes the half of a brick's side
	float halfside = brick.width / 2.0f;

	// Method checks the brick's condition via color change signifying its status, plus rendering the bricks dimensions and colors
	float brickStatus = brick.stamina / 3.0f;
	glColor3f(brick.red * brickStatus, brick.green * brickStatus, brick.blue * brickStatus);

	glBegin(GL_POLYGON);

	glVertex2d(brick.x + halfside, brick.y + halfside);
	glVertex2d(brick.x + halfside, brick.y - halfside);
	glVertex2d(brick.x - halfside, brick.y - halfside);
	glVertex2d(brick.x - halfside, brick.y + halfside);

	glEnd();
}

void View::drawPaddle(const Paddle& pad) {
	// Process for rendering the paddle's color and dimensions
	glColor3f(0.5f, 0.5f, 0.5f); // Paddle is now grey

	glBegin(GL_POLYGON);

	glVertex2d(pad.x + (pad.width / 2.0f), pad.y + (pad.height / 2.0f));
	glVertex2d(pad.x + (pad.width / 2.0f), pad.y - (pad.height / 2.0f));
	glVertex2d(pad.x - (pad.width / 2.0f), pad.y + (pad.height / 2.0f));
	glVertex2d(pad.x - (pad.width / 2.0f), pad.y - (pad.height / 2.0f));

	glEnd();
}

void View::drawCircle(const Circle& circle) {
	// Process for rendering the circle's color
	glColor3f(1.0f, 1.0f, 1.0f); // Circle is now white

	glBegin(GL_POLYGON);

	// For loop for creating the circle's dimensions
	for (int i = 0; i < 360; i++) {
		float degInRad = i * DEG2RAD;
		glVertex2f((cos(degInRad) * circle.radius) + circle.x, (sin(degInRad) * circle.radius) + circle.y);
	}
	glEnd();
}

void View::render(Model& model) {
	glClear(GL_COLOR_BUFFER_BIT);

	// For loop to draw up a series of bricks
	for (const auto& brick : model.getBricks()) {
		drawBrick(brick);
	}

	// Draws the paddle and circle
	const auto& paddle = model.getPaddle();
	drawPaddle(paddle);
	const auto& circle = model.getCircle();
	drawCircle(circle);
}