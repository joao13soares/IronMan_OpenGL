#pragma once

#include "Libraries.h"

class Camera
{
	public:
		Camera();
		~Camera();

		void cursorPosCallback(GLFWwindow *window, double xpos, double ypos);
		void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
		void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

		void updateCameraDeltaTime(float dt);

		void printInfo();

		// Field of View
		float FoV;
		// position
		glm::vec3 position;
		// direction
		glm::vec3 direction;
		// up
		glm::vec3 up;

	private:
		// right
		glm::vec3 right;

		// horizontal angle
		float yaw;
		// vertical angle
		float pitch;

		float speed;
		float mouseSpeed;

		bool firstMouseMove;
		float mouseLastX;
		float mouseLastY;

		float deltaTime;

		int printInfoRate;

};