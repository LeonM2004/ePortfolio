///////////////////////////////////////////////////////////////////////////////
// model.cpp
// ============
// Manages the preparations for establishing the bricks, paddle, circle along with checking collision properties
// 
// NAME: Leonardo Marulanda
// DATE: 11/09/2026
// Created from CS-330 Computational Graphics and Visualization on 06/23/2026,
// Enhanced for CS-499 Computer Science Capstone
///////////////////////////////////////////////////////////////////////////////

#include "model.h"

using namespace std;

Model::Model(){
	initLevel(); // Initializes the gameplay loop
}

void Model::initLevel() {
	bricks.clear(); // Restarts the bricks
	
	// Brick properties/grid are initialized
	float xStart = -0.65f;
	float yStart = 0.1f;
	float brickWidth = 0.2f;

	// For loops created to set up the rows of different bricks for the game to loop
	for (int i = 0; i < 6; i++) {
		bricks.push_back(Brick(NORMAL, xStart + (i * 0.25f), yStart, brickWidth, 0.9f, 0.1f, 0.2f));
	}

	// Special for loop for Durable brick types to add specified stamina
	for (int i = 0; i < 8; i++) {
		Brick d(DURABLE, xStart + (i * 0.25f) - 0.25f, yStart + 0.25f, brickWidth, 0.1f, 0.6f, 0.1f);
		d.stamina = 3;
		bricks.push_back(d);
	}

	for (int i = 0; i < 4; i++) {
		bricks.push_back(Brick(REFLECTIVE, xStart + (i * 0.5f) - 0.1f, yStart + 0.75f, brickWidth, 0.1, 0.35f, 0.9f));
	}


	// Paddle properties are initialized
	paddle.x = 0.0f;
	paddle.y = -0.8f;
	paddle.width = 0.5f;
	paddle.height = 0.15f;
	paddle.speed = 0.025f;

	// Circle properties are initialized
	circle.x = 0.0f;
	circle.y = -0.6f;
	circle.radius = 0.06f;
	circle.vx = 0.005f;
	circle.vy = 0.005f;
}

void Model::UpdatePhysics() {

	// Moving circles within the world vector
	circle.x += circle.vx;
	circle.y += circle.vy;

	// Checks horizontal wall collisions (left/right)
	if (circle.x + circle.radius > 1.0f || circle.x - circle.radius < -1.0f) {
		circle.vx *= -1.0f;
	}
	// Checks vertical wall collision (top)
	if (circle.y + circle.radius > 1.0f) {
		circle.vy *= -1.0f;
	}
	// Checks if circle fell off map (bottom)
	if (circle.y - circle.radius < -1.0f) {
		initLevel(); // Resets the gameplay loop
	}
	// calls method to check circle's collision between bricks or paddle
	checkCollisions();
}

void Model::checkCollisions() {
	// Checks the collisions made between the circle and paddle
	if (circle.y - circle.radius <= paddle.y + (paddle.height / 2) &&
		circle.x - circle.radius >= paddle.x - (paddle.width) / 2 &&
		circle.x + circle.radius <= paddle.x + (paddle.width) / 2) {
		circle.vy = abs(circle.vy);
	} // Bounces upward

	// Checks the collisions made between the circle and bricks
	for (auto& brick : bricks) {
		if (brick.onoff == ON) {
			if (circle.x + circle.radius >= brick.x - (brick.width / 2.0f) &&
				circle.x - circle.radius <= brick.x + (brick.width / 2.0f) &&
				circle.y + circle.radius >= brick.y - (brick.width / 2.0f) &&
				circle.y - circle.radius <= brick.y + (brick.width / 2.0f)) {

				// If-else statments function to prevent the circle from doing multi-frame damage onto bricks
				if (circle.vy > 0) {
					// Circle makes contact with bottom of brick
					circle.y = brick.y - (brick.width / 2.0f) - circle.radius - 0.001f;
				}
				else {
					// Circle makes contact with top of brick
					circle.y = brick.y + (brick.width / 2.0f) + circle.radius + 0.001f;
				}

				// Inverts the ball's vertical velocity
				circle.vy *= -1.0f;

				// Uses switch-case to test the different brick types
				switch (brick.brick_type) {

					// Normal bricks immediately break apart
					case NORMAL:
						brick.stamina -= 1;

						if (brick.stamina <= 0) {
							brick.onoff = OFF;
						}
						break;

					// Durable bricks have the most stamina, but change in colors signify damage
					case DURABLE:
						brick.stamina -= 1;
						brick.green -= 0.3f;
						brick.red += 0.4f;
						brick.blue += 0.05f;

						// Destroys the brick the moment it loses all its stamina
						if (brick.stamina <= 0) {
							brick.onoff = OFF;
						}
						break;

					// Reflective bricks do not take any damage, rather they change the circle's
					// trajectory and gradually increment the speed
					case REFLECTIVE:
						circle.x = circle.x - 0.01f;
						circle.y = circle.y - 0.02f;
						circle.vx *= 1.01f;
						circle.vy *= 1.01f;
						break;

					default:
						break;
				}

				break;
			}
		}
	}
}