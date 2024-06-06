#pragma once

namespace Dogo
{
	enum class RenderAPI
	{
		None = 0, OpenGL, D3D11, D3D12, VULKAN
	};
	class GraphicsContext
	{
	public:
		GraphicsContext(const GraphicsContext&) = delete;
		GraphicsContext& operator=(const GraphicsContext&) = delete;

		virtual bool Init() = 0;
		virtual void SwapBuffer() = 0;
		virtual void Shutdown() = 0;
		virtual void ClearColor(float x, float y, float z, float a) = 0;

		static void Create(HWND* handle, RenderAPI api);

		static GraphicsContext* Get() { return s_Context; }
		static RenderAPI GetAPI() { return s_RenderAPI; }

	protected:
		GraphicsContext() = default;
		static GraphicsContext* s_Context;
		static RenderAPI s_RenderAPI;
	};
}