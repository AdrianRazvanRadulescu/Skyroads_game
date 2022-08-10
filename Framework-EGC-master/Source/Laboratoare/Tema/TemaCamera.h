#pragma once

#include <include/glm.h>
#include <include/math_utils.h>

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

namespace TemaCamera
{
	class Camera
	{
	public:
		Camera()
		{
			position = glm::vec3(0, 2, 5);
			forward = glm::vec3(0, 0, -1);
			up = glm::vec3(0, 1, 0);
			right = glm::vec3(1, 0, 0);
			distanceToTarget = 2;
		}

		Camera(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
		{
			Set(position, center, up);
		}

		~Camera()
		{ }

		// Update camera
		void Set(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
		{
			this->position = position;
			forward = glm::normalize(center - position);
			right = glm::cross(forward, up);
			this->up = glm::cross(right, forward);
		}

		void MoveForward(float distance)
		{
			glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
			// movement will keep the camera at the same height always
			// Example: If you rotate up/down your head and walk forward you will still keep the same relative distance (height) to the ground!
			// Translate the camera using the DIR vector computed from forward
		}

		void TranslateForward(float distance)
		{
			// TODO : Translate the camera using the "forward" vector
			position += forward * distance;
		}

		void TranslateUpword(float distance)
		{
			// TODO : Translate the camera using the up vector
			position += up * distance;
		}

		void TranslateRight(float distance)
		{
			position += right * distance;
		}

		void RotateFirstPerson_OX(float angle)
		{
			forward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), angle, right) * glm::vec4(forward, 1)));
			up = glm::normalize(glm::cross(right, forward));
		}

		void RotateFirstPerson_OY(float angle)
		{
			glm::vec4 newVector = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1);
			forward = glm::normalize(glm::vec3(newVector));

			glm::vec4 newVector_right = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1);
			right = glm::normalize(glm::vec3(newVector_right));

			up = glm::normalize(glm::cross(right, forward));
		}

		void RotateFirstPerson_OZ(float angle)
		{
			glm::vec4 newVector = glm::rotate(glm::mat4(1.0f), angle, forward) * glm::vec4(right, 1);
			right = glm::normalize(glm::vec3(newVector));

			up = glm::normalize(glm::cross(right, forward));
		}

		void RotateThirdPerson_OX(float angle)
		{
			position += distanceToTarget * forward;
			forward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), angle, right) * glm::vec4(forward, 1)));
			up = glm::normalize(glm::cross(right, forward));
			position -= distanceToTarget * forward;
		}

		void RotateThirdPerson_OY(float angle)
		{
			position += distanceToTarget * up;

			glm::vec4 newVector = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1);
			forward = glm::normalize(glm::vec3(newVector));

			glm::vec4 newVector_right = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1);
			right = glm::normalize(glm::vec3(newVector_right));

			up = glm::normalize(glm::cross(right, forward));

			position -= distanceToTarget * up;
		}

		void RotateThirdPerson_OZ(float angle)
		{
			position += distanceToTarget * right;
			glm::vec4 newVector = glm::rotate(glm::mat4(1.0f), angle, forward) * glm::vec4(right, 1);
			right = glm::normalize(glm::vec3(newVector));

			up = glm::normalize(glm::cross(right, forward));
			position -= distanceToTarget * right;
		}

		glm::mat4 GetViewMatrix()
		{
			return glm::lookAt(position, position + forward, up);
		}

		glm::vec3 GetTargetPosition()
		{
			return position + forward * distanceToTarget;
		}

	public:
		float distanceToTarget;
		glm::vec3 position;
		glm::vec3 forward;
		glm::vec3 right;
		glm::vec3 up;
	};
}