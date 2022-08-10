#include "Tema.h"

#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <Core/Engine.h>

using namespace std;

Tema::Tema()
{
}

Tema::~Tema()
{
}

void Tema::Init()
{
	renderCameraTarget = false;

	camera = new TemaCamera::Camera();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	
	{
		Shader* shader = new Shader("ShaderTema");
		shader->AddShader("Source/Laboratoare/Tema/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		std::vector<VertexFormat> verticesFuel =
		{
			VertexFormat(glm::vec3(0) , glm::vec3(0.14f, 0.83f, 0.44f)),
			VertexFormat(glm::vec3(lengthFuel, 0, 0), glm::vec3(0.14f, 0.83f, 0.44f)),
			VertexFormat(glm::vec3(0, heightFuel, 0), glm::vec3(0.14f, 0.83f, 0.44f)),
			VertexFormat(glm::vec3(lengthFuel, heightFuel, 0), glm::vec3(0.14f, 0.83f, 0.44f))
		};

		std::vector<unsigned short> indicesFuel =
		{
			1, 2, 3,
			2, 1, 3,
			0, 2, 3
		};

		meshes["fuel"] = new Mesh("fuel");
		Mesh* button = CreateMesh("fuel", verticesFuel, indicesFuel);

		button->SetDrawMode(GL_TRIANGLE_FAN);
		AddMeshToList(button);
	}


	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("box2");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("box3");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}


	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}

void Tema::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema::Update(float deltaTimeSeconds)
{

	if (lost == 0) {
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(posFirstOx, posFirstOy, posFirstOz));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleFirstOx, scaleFirstOy, scaleFirstOz));
			RenderMesh(meshes["box"], shaders["ShaderTema"], modelMatrix, colorFirst);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);

			modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 2.2f, 1));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6f, 0.2f, 1));
			RenderMesh(meshes["fuel"], shaders["ShaderTema"], modelMatrix, glm::vec3(0.14, 0.89, 0.43));
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 2.2f, 1.0001f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(fuelLevel, 0.2f, 1));
			RenderMesh(meshes["fuel"], shaders["ShaderTema"], modelMatrix, glm::vec3(1, 1, 1));
		}


		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(posSecondOx, posSecondOy, posSecondOz));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleSecondOx, scaleSecondOy, scaleSecondOz));
			RenderMesh(meshes["box2"], shaders["ShaderTema"], modelMatrix, colorSecond);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(posThirdOx, posThirdOy, posThirdOz));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleThirdOx, scaleThirdOy, scaleThirdOz));
			RenderMesh(meshes["box3"], shaders["ShaderTema"], modelMatrix, colorThird);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(posPlayerOx, posPlayerOy, posPlayerOz));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(scalePlayer));
			RenderMesh(meshes["sphere"], shaders["ShaderTema"], modelMatrix, colorPlayer);
		}
	}
}

void Tema::FrameEnd()
{
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

Mesh* Tema::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// TODO: Create the VBO and bind it
	unsigned int VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	// TODO: Crete the IBO and bind it
	unsigned int IBO = 0;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
	// TODO: Send indices data into the IBO buffer

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data
	// It will be learned later, when GLSL shaders will be introduced
	// For the moment just think that each property value from our vertex format needs to be send to a certain channel
	// in order to know how to receive it in the GLSL vertex shader

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// TODO: Unbind the VAO
	glBindVertexArray(0);
	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	return meshes[name];
}


void Tema::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();

	glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema::OnInputUpdate(float deltaTime, int mods)
{
	if (fall == 0) {
		if (window->KeyHold(GLFW_KEY_D)) {
			posPlayerOx += deltaTime * 2;
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			posPlayerOx -= deltaTime * 2;
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			if (speedPlatforms > 4 && blocked == 0)
				speedPlatforms -= deltaTime * 4;
		}

		if (window->KeyHold(GLFW_KEY_W)) {
			if (speedPlatforms < 10 && blocked == 0)
			speedPlatforms += deltaTime * 4;
		}

		posFirstOz += speedPlatforms * deltaTime;
		posSecondOz += speedPlatforms * deltaTime;
		posThirdOz += speedPlatforms * deltaTime;

		if (firstPerson == 1) 
			camera->position = glm::vec3(posPlayerOx, posPlayerOy, posPlayerOz - scalePlayer);

		if (firstPerson == 0) 
			camera->position = glm::vec3(0, 2, 3.5f);

		if (posFirstOz - scaleFirstOz / 2 > posPlayerOz) {
			scaleFirstOz = spacePlatforms + rand() % 15;
			colorNumberFirst = rand() % 8;
			if (colorNumberFirst < 4)
				colorFirst = blue;
			if (colorNumberFirst == 4)
				colorFirst = red;
			if (colorNumberFirst == 6)
				colorFirst = yellow;
			if (colorNumberFirst == 7)
				colorFirst = orange;
			if (colorNumberFirst == 5)
				colorFirst = green;
			if (platformGen % 2 == 1) {
				posFirstOz = -scaleFirstOz / 2;
				platformGen++;
			}
		}

		if (posSecondOz - scaleSecondOz / 2 > posPlayerOz) {
			scaleSecondOz = spacePlatforms + rand() % 15;
			colorNumberSecond = rand() % 8;
			if (colorNumberSecond < 4)
				colorSecond = blue;
			if (colorNumberSecond == 5)
				colorSecond = blue;
			if (colorNumberSecond == 7)
				colorSecond = yellow;
			if (colorNumberSecond == 6)
				colorSecond = orange;
			if (colorNumberSecond == 4)
				colorSecond = green;
			
			if (platformGen % 2 == 0) {
				posSecondOz = -scaleSecondOz / 2;
				platformGen++;
			}
		}

		if (posThirdOz - scaleThirdOz / 2 > posPlayerOz) {
			jumpedThird = 0;
			scaleThirdOz = spacePlatforms + rand() % 15;
			colorNumberThird = rand() % 8;
			
			if (colorNumberThird < 4) 
				colorThird = blue;
			if (colorNumberThird == 5)
				colorThird = red;
			if (colorNumberThird == 6)
				colorThird = yellow;
			if (colorNumberThird == 7)
				colorThird = orange;
			if (colorNumberThird == 4)
				colorThird = green;

			posThirdOz = -scaleThirdOz / 2;
		}

		fuelLevel += 0.01f * deltaTime;
		if (fuelLevel >= 0.6f) {
			lost = 1;
		}

		if (spacePressed == 1 && posPlayerOy < 1.7f) {
			posPlayerOy += deltaTime * 2;
		}

		if (posPlayerOy >= 1.7f) {
			spacePressed = 0;
		}

		if (spacePressed == 0 && collisionFirst == 0 && collisionSecond == 0 && collisionThird == 0) {
			posPlayerOy -= deltaTime * 1.5f;
		}

		if (posPlayerOy < 1) {
			posPlayerOy -= deltaTime * 1.5f;
		}

		if (posPlayerOy < -5.0f) {
			lost = 1;
		}

		// collission player first platform
		float firstBoxMinX = posFirstOx - scaleFirstOx / 2;
		float firstBoxMaxX = posFirstOx + scaleFirstOx / 2;
		float firstBoxMinY = posFirstOy - scaleFirstOy / 2;
		float firstBoxMaxY = posFirstOy + scaleFirstOy / 2;
		float firstBoxMinZ = posFirstOz - scaleFirstOz / 2;
		float firstBoxMaxZ = posFirstOz + scaleFirstOz / 2;

		float xFirst = max(firstBoxMinX, min(posPlayerOx, firstBoxMaxX));
		float yFirst = max(firstBoxMinY, min(posPlayerOy, firstBoxMaxY));
		float zFirst = max(firstBoxMinZ, min(posPlayerOz, firstBoxMaxZ));

		float distanceFirst = sqrt((xFirst - posPlayerOx) * (xFirst - posPlayerOx) +
			(yFirst - posPlayerOy) * (yFirst - posPlayerOy) +
			(zFirst - posPlayerOz) * (zFirst - posPlayerOz));

		if (distanceFirst < sphereRadius) {
			jumpedFirst = 1;
			collisionFirst = 1;
		}
		else
			collisionFirst = 0;

		if (blocked == 1) {
			if (timeBlocked < 1)
				timeBlocked += 0.1f * deltaTime;
		}
		if (timeBlocked >= 1) {
			blocked = 0;
			speedPlatforms = 7;
			timeBlocked == 0;
		}

		if (blocked == 1) 
			speedPlatforms = 11;

		if (collisionFirst == 1) {
			if (colorFirst == yellow) {
				if (fuelLevel < 0.5f)
					fuelLevel += 0.1f;
				else
					lost = 1;
			}

			if (colorFirst == orange) {
				blocked = 1;
			}

			if (colorFirst == green) {
				if (fuelLevel > 0.1f)
					fuelLevel -= 0.1f;
				else
					fuelLevel = 0;
			}

			if (colorFirst == red) {
				lost = 1;
			}
			colorFirst = purple;
		}
		if (waitSpace < 1.2f)
			waitSpace += 1.6f * deltaTime;

		// collision second Platform
		float secondBoxMinX = posSecondOx - scaleSecondOx / 2;
		float secondBoxMaxX = posSecondOx + scaleSecondOx / 2;
		float secondBoxMinY = posSecondOy - scaleSecondOy / 2;
		float secondBoxMaxY = posSecondOy + scaleSecondOy / 2;
		float secondBoxMinZ = posSecondOz - scaleSecondOz / 2;
		float secondBoxMaxZ = posSecondOz + scaleSecondOz / 2;

		float xSecond = max(secondBoxMinX, min(posPlayerOx, secondBoxMaxX));
		float ySecond = max(secondBoxMinY, min(posPlayerOy, secondBoxMaxY));
		float zSecond = max(secondBoxMinZ, min(posPlayerOz, secondBoxMaxZ));

		float distanceSecond = sqrt((xSecond - posPlayerOx) * (xSecond - posPlayerOx) +
			(ySecond - posPlayerOy) * (ySecond - posPlayerOy) +
			(zSecond - posPlayerOz) * (zSecond - posPlayerOz));

		if (distanceSecond < sphereRadius) {
			collisionSecond = 1;
			jumpedSecond = 1;
		}
		else
			collisionSecond = 0;

		if (collisionSecond == 1) {
			if (colorSecond == yellow) {
				if (fuelLevel < 0.5f)
						fuelLevel += 0.1f;
					else
						lost = 1;
			}

				if (colorSecond == orange) {
					blocked = 1;
				}

				if (colorSecond == green) {
					if (fuelLevel > 0.1f)
						fuelLevel -= 0.1f;
					else
						fuelLevel = 0;
				}

				if (colorSecond == red) {
					lost = 1;
				}
				colorSecond = purple;	
		}
		// collision second Platform
		float thirdBoxMinX = posThirdOx - scaleThirdOx / 2;
		float thirdBoxMaxX = posThirdOx + scaleThirdOx / 2;
		float thirdBoxMinY = posThirdOy - scaleThirdOy / 2;
		float thirdBoxMaxY = posThirdOy + scaleThirdOy / 2;
		float thirdBoxMinZ = posThirdOz - scaleThirdOz / 2;
		float thirdBoxMaxZ = posThirdOz + scaleThirdOz / 2;

		float xThird = max(thirdBoxMinX, min(posPlayerOx, thirdBoxMaxX));
		float yThird = max(thirdBoxMinY, min(posPlayerOy, thirdBoxMaxY));
		float zThird = max(thirdBoxMinZ, min(posPlayerOz, thirdBoxMaxZ));

		float distanceThird = sqrt((xThird - posPlayerOx) * (xThird - posPlayerOx) +
			(yThird - posPlayerOy) * (yThird - posPlayerOy) +
			(zThird - posPlayerOz) * (zThird - posPlayerOz));

		if (distanceThird < sphereRadius) {
			collisionThird = 1;
			jumpedThird = 1;
		}
		else
			collisionThird = 0;

		if (collisionThird == 1) {
			if (colorThird == yellow) {
				if (fuelLevel < 0.5f)
					fuelLevel += 0.1f;
				else
					lost = 1;
			}

			if (colorThird == orange) {
				blocked = 1;
			}

			if (colorThird == green) {
				if (fuelLevel > 0.1f)
					fuelLevel -= 0.1f;
				else
					fuelLevel = 0;
			}

			if (colorThird == red) {
				lost = 1;
			}
			colorThird = purple;
		}
	}
	else {
		if (posPlayerOy > -3.0f) {
			posPlayerOy -= deltaTime * 6;
		}
	}
}

void Tema::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE && waitSpace >= 1 && posPlayerOy > 1)
	{
		spacePressed = 1;
		waitSpace = 0;
	}

	if (key == GLFW_KEY_V) {
		if (firstPerson == 0) {
			firstPerson = 1;
		}
	}

	if (key == GLFW_KEY_B) {
		if (firstPerson == 1) {
			firstPerson = 0;
		}
	}
}

void Tema::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

}

void Tema::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema::OnWindowResize(int width, int height)
{
}
