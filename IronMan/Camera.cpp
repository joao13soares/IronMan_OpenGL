#pragma once

#include "Camera.h"

Camera::Camera()
{
	printInfoRate = 100;

	// Initial Field of View
	FoV = 45.0f;
	// position
	position = glm::vec3(0.0f, 3.0f, 10.0f);
	// direction
	direction = glm::vec3(0.0f, -1.0f, -11.0f);
	// right
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	// up
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	// horizontal angle : toward -Z
	yaw = 90.0f;
	// vertical angle : 0, look at the horizon
	pitch = 0.0f;

	speed = 10.0f; // 10 units / second
	mouseSpeed = 0.005f;

	firstMouseMove = true;
	mouseLastX = 1024.0f / 2.0f;
	mouseLastY = 720.0f / 2.0f;

	deltaTime = 0.0f;
}

Camera::~Camera()
{
}

void Camera::cursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
	float xDif;
	float yDif;

	if (firstMouseMove) {
		firstMouseMove = false;
		xDif = 0;
		yDif = 0;
	}
	else {
		xDif = xpos - mouseLastX;
		yDif = mouseLastY - ypos;
	}

	mouseLastX = xpos;
	mouseLastY = ypos;

	xDif *= 0.05f;
	yDif *= 0.05f;

	yaw += xDif;
	pitch += yDif;

	// limitar movimento vertical
	if (pitch > 85.0f)
		pitch = 85.0f;
	if (pitch < -85.0f)
		pitch = -85.0f;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction = glm::normalize(direction);
}

void Camera::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	float totalSpeed = deltaTime * speed;
	// Move forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += direction * totalSpeed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position -= direction * totalSpeed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += right * totalSpeed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position -= right * totalSpeed;
	}
}

void Camera::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
	if (FoV >= 1.0f &&  FoV <= 45.0f)
		FoV -= yoffset;
	if (FoV <= 1.0f)
		FoV = 1.0f;
	if (FoV >= 45.0f)
		FoV = 45.0f;
}

void Camera::updateCameraDeltaTime(float dt) {
	deltaTime = dt;
}

void Camera::printInfo() {
	if (printInfoRate <= 0) {
		cout << " | FoV " << FoV << endl
			<< " | Pos " << position.x << ", " << position.y << ", " << position.z << endl
			<< " | Dir " << direction.x << ", " << direction.y << ", " << direction.z << endl
			<< " | Up " << up.x << ", " << up.y << ", " << up.z << endl
			<< " | HA " << yaw << endl
			<< " | VA " << pitch << endl
			<< " | DT " << deltaTime << endl << endl;

		printInfoRate = 100;
	}
	else {
		printInfoRate--;
	}
}