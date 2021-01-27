#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(400.0f, 300.0f);
	addChild(m_pTarget);

	m_pCar = new Car();
	m_pCar->getTransform()->position = glm::vec2(100.0f, 100.0f);
	m_pCar->setEnabled(false);
	m_pCar->setDestination(m_pTarget->getTransform()->position);
	addChild(m_pCar);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if(ImGui::Button("Start"))
	{
		std::cout << "Start Button Pressed" << std::endl;
		m_pCar->setEnabled(true);
	}

	ImGui::SameLine();

	if (ImGui::Button("Reset Car"))
	{
		std::cout << "Reset Car Button Pressed" << std::endl;
		m_pCar->setEnabled(false);
		m_pCar->getTransform()->position = glm::vec2(100.0f, 100.0f);
	}

	ImGui::SameLine();

	if (ImGui::Button("Reset Target"))
	{
		std::cout << "Reset Target Button Pressed" << std::endl;
		m_pTarget->getTransform()->position = glm::vec2(400.0f, 300.0f);
		m_pCar->setDestination(m_pTarget->getTransform()->position);
	}

	static float shipSpeed = 8.0f;
	if (ImGui::SliderFloat("Speed", &shipSpeed, 0.0f, 15.0f))
	{
		m_pCar->setMaxSpeed(shipSpeed);
	}

	static float angleInRadians = 0.0f;
	if(ImGui::SliderAngle("Orientation Angle", &angleInRadians)) {
		m_pCar->setRotation(angleInRadians * Util::Rad2Deg);
	}

	ImGui::Separator();

	static float float2[2] = {m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y};
	if(ImGui::SliderFloat2("Target", float2, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(float2[0], float2[1]);
		m_pCar->setDestination(m_pTarget->getTransform()->position);
	}

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
