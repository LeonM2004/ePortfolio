///////////////////////////////////////////////////////////////////////////////
// maincode.cpp
// ============
// Is the program called when application is launched, also doubles as the application's controller
// 
// NAME: Leonardo Marulanda
// DATE: 11/09/2026
// Created from CS-330 Computational Graphics and Visualization on 06/23/2026,
// Enhanced for CS-499 Computer Science Capstone
///////////////////////////////////////////////////////////////////////////////

#include <GLFW\glfw3.h>
#include "model.h"
#include "view.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;
void processInput(GLFWwindow* window, Model& gameModel);

// ProcessInput is responsible for managing the gameplay loop depending on the buttons pressed
void processInput(GLFWwindow* window, Model& gameModel)
{
	Paddle& paddle = gameModel.getPaddle();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		if (paddle.x - (paddle.width / 2.0f) > -1.0f) paddle.x -= paddle.speed;
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		if (paddle.x + (paddle.width / 2.0f) < 1.0f) paddle.x += paddle.speed;
	}

}

// Primary engine's routing loop
int main() {
	srand(time(NULL));

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window = glfwCreateWindow(640, 560, "CS 499 Enhancement One - Software Engineering and Design", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	Model gameModel;
	View gameView;

	while (!glfwWindowShouldClose(window)) {
		//Setup View
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window, gameModel);

		// Calls upon gameModel to update physics and check collision
		gameModel.UpdatePhysics();
		gameModel.checkCollisions();

		// Calls gameView to render models
		gameView.render(gameModel);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}


