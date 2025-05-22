#include "dgpch.h"
#include "AppLayer.h"
#include "../vendor/DogoECS/include/DG_Component.h"
#include "Dogo/Component/Component.h"
#include "Dogo/Renderer/UI/UI.h"
#include "Dogo/Input/Input.h"
AppLayer::AppLayer()
	: Layer("AppLayer")
{
}

void AppLayer::OnAttach()
{
	DG_INFO("AppLayer Attached");
}
void AppLayer::OnDetach()
{
	DG_INFO("AppLayer Detached");
}
void AppLayer::OnUpdate()
{
	DogoECS::DG_ComponentManager::UpdateComponents<Dogo::TransformComponent>();

	Dogo::Input::Int2 mouse = Dogo::Input::GetMousePosition();
	Dogo::DogoUI::HandleInput(glm::vec2(mouse.x, mouse.y), Dogo::Input::IsMouseButtonPressed(DG_MOUSE_BUTTON_1));
	Dogo::DogoUI::Render(Renderer);
	Renderer->SubmitText("FPS: ", 25.0f, 570.0f, 1.0f, glm::vec3(0.0f, .0f, 1.0f));
	Renderer->SubmitText(std::to_string(60).c_str(), 135.0f, 570.0f, 1.0f, glm::vec3(0.0f, .0f, 1.0f));
	Renderer->Flush();
	Renderer->RenderText();
}