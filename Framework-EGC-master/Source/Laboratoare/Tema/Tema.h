#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>
#include "TemaCamera.h"

class Tema : public SimpleScene
{
public:
	Tema();
	~Tema();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);
	void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);

protected:
	TemaCamera::Camera* camera;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget;

	glm::vec3 red = glm::vec3(1, 0, 0);
	glm::vec3 yellow = glm::vec3(1, 1, 0);
	glm::vec3 orange = glm::vec3(1, 0.64f, 0);
	glm::vec3 green = glm::vec3(0, 1, 0);
	glm::vec3 purple = glm::vec3(0.5f, 0, 0.5f);
	glm::vec3 blue = glm::vec3(0, 0, 1);

	glm::vec3 colorFirst = green;
	glm::vec3 colorSecond = yellow;
	glm::vec3 colorThird = orange;
	glm::vec3 colorPlayer = glm::vec3(0.5f, 0.5f, 0.5f);

	int colorGen = 0;

	int thirdPerson = 1;

	int collisionFirst = 0;
	int collisionSecond = 0;
	int collisionThird = 0;

	int jumpedFirst = 0;
	int jumpedSecond = 0;
	int jumpedThird = 0;

	int dPressed = 0;
	int aPressed = 0;

	int fall = 0;

	int lost = 0;
	float spacePressed = 1;

	float lengthFuel = 2;
	float heightFuel = 1;
	float fuelLevel = 0.0f;
	
	int blocked = 0;
	float timeBlocked = 0;

	int firstPerson = 0;
	//player parameters
	float posPlayerOx = 0;
	float posPlayerOy = 1.5f;
	float posPlayerOz = 1.5f;

	float scalePlayer = 0.4f;
	float sphereRadius = 0.5f * scalePlayer;
	// speed
	float speedPlatforms = 4;
	float spacePlatforms = 5;
	
	int platformGen = 0;
	int colorNumberFirst;
	int colorNumberSecond;
	int colorNumberThird;
	// first cube parameters
	float posFirstOx = -1.5f;
	float posFirstOy = 1;
	float posFirstOz = -2.7f;

	float scaleFirstOx = 1;
	float scaleFirstOy = 0.01f;
	float scaleFirstOz = 10;

	float waitSpace = 1.0f;
	// second cube
	float posSecondOx = 0;
	float posSecondOy = 1; 
	float posSecondOz = -2.7f;

	float scaleSecondOx = 1;
	float scaleSecondOy = 0.01f;
	float scaleSecondOz = 10;
	
	// third cube
	float posThirdOx = 1.5f;
	float posThirdOy = 1;
	float posThirdOz = -2.7f;

	float scaleThirdOx = 1;
	float scaleThirdOy = 0.01f;
	float scaleThirdOz = 10;
};
