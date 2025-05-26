#include "dgpch.h"
#include "EditorLayer.h"
#include "Dogo/Logger.h"

EditorLayer::EditorLayer()
		: Layer("EditorLayer")
	{
		DG_TRACE("EditorLayer created");
	}
void EditorLayer::OnAttach()
{
	DG_TRACE("EditorLayer attached");
}
void EditorLayer::OnDetach()
{
	DG_TRACE("EditorLayer detached");
}
void EditorLayer::OnUpdate()
{
	DG_TRACE("EditorLayer updated");
}

