///////////////////////////////////////////////////////////////////////////////
// view.h
// ============
// Manages the preparing and rendering for the statuses surrounding the brick, paddle, and circle
// 
// NAME: Leonardo Marulanda
// DATE: 11/09/2026
// Created from CS-330 Computational Graphics and Visualization on 06/23/2026,
// Enhanced for CS-499 Computer Science Capstone
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <GLFW\glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "model.h"

class View {
public:
	View();

	bool initWindow(int width, int height, const char* title);
	void render(Model& model);

private:
	void drawBrick(const Brick& brick);
	void drawPaddle(const Paddle& pad);
	void drawCircle(const Circle& circle);
};