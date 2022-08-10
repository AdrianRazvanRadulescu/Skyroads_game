#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>

class Laborator7 : public SimpleScene
{
public:
	Laborator7();
	~Laborator7();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1));
	Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);
	
	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	glm::vec3 lightPosition;

	int materialShininess;
	float materialKd;
	float materialKs;


	float radius = 1;
	unsigned int sectorCount = 24;
	unsigned int stackCount = 48;

	float fov = 60;
	float left = -10.0f;
	float right = 10.0f;


	float posPlayerOx;
	float posPlayerOy;
	float posPlayerOz;

	// first cube parameters
	float posFirstOx = -1;
	float posFirstOy = 1;
	float posFirstOz = 0;

	float scaleFirstOx = 1;
	float scaleFirstOy = 1;
	float scaleFirstOz = 1;


	// second cube
	float posSecondOx = 1;
	float posSecondOy = 1;
	float posSecondOz = 0;

	float scaleSecondOx = 1;
	float scaleSecondOy = 1;
	float scaleSecondOz = 1;

	// third cube
	float posThirdOx = 0;
	float posThirdOy = 1;
	float posThirdOz = 0;

	float scaleThirdOx = 1;
	float scaleThirdOy = 1;
	float scaleThirdOz = 1;


};
