#include "Camera.h"
#include <iostream>
void Camera::moveUp(float dt, float speed) {
	position.y += speed*dt;
	updateLookAt();
}

void Camera::moveSide(float dt, float speed) {
	Vector3 offset = Vector3(right.x, 0, right.z);
	offset.normalise();
	position.x += offset.x * dt * speed;
	//position.y += forward.y * dt * speed; //debug pp
	position.z += offset.z * dt * speed;
	updateLookAt();
}

void Camera::moveForward(float dt, float speed) {
	Vector3 offset = Vector3(forward.x, 0, forward.z);
	offset.normalise();
	position.x += offset.x * dt * speed;
	//position.y += forward.y * dt * speed; //debug pp
	position.z += offset.z * dt * speed;
	
	updateLookAt();
}

void Camera::updateLookAt() {
	lookat = position + forward;
}

void Camera::updateRotation() {
	cosY = cosf(rotation.y * 3.1415 / 180);
	cosP = cosf(rotation.x * 3.1415 / 180);
	cosR = cosf(rotation.z * 3.1415 / 180);
	sinY = sinf(rotation.y * 3.1415 / 180);
	sinP = sinf(rotation.x * 3.1415 / 180);
	sinR = sinf(rotation.z * 3.1415 / 180);

	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;

	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;

	right = forward.cross(up);
	updateLookAt();
}


//CAMERA AND DEBUG Y-AXIS MOVEMENT
void Camera::InputMovement(Input & input, float dt, int width, int height) {

	if (input.isKeyDown('q')) {
		moveUp(dt, 5);
	}

	// ROTATION
	if (input.getMouseX() != width / 2 || input.getMouseY() != height / 2) {
		rotation.y += dt * 20.0f * (input.getMouseX() - width / 2);
		rotation.x -= dt * 20.0f * (input.getMouseY() - height / 2);
		if (rotation.x > 90) { rotation.x = 90; }
		else if (rotation.x < -90) { rotation.x = -90; }
		updateRotation();
	}
}