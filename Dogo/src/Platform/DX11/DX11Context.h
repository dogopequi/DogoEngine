#pragma once
#if DG_PLATFORM_WINDOWS
#include "Graphics/GraphicsContext.h"
	class Window;

	namespace Dogo
	{
		 
		 
		using Microsoft::WRL::ComPtr;
		class DX11Context : public GraphicsContext
		{
		public:
			DX11Context(HWND* handle);
			DX11Context(const DX11Context&) = delete;
			DX11Context& operator=(const DX11Context&) = delete;
			~DX11Context();

			bool Init() override;
			void SwapBuffer() override;
			void Shutdown() override;
			void ClearColor(float x, float y, float z, float a) override;
			inline ComPtr<ID3D11Device> GetDevice() const{ return m_Device; }
			inline ComPtr<ID3D11DeviceContext> GetDeviceContext() const { return m_DeviceContext; }
			inline ComPtr<IDXGISwapChain1> GetSwapChain() const { return m_Swapchain; }
			inline ComPtr<ID3D11RenderTargetView> GetRenderTargetView() const { return m_RenderTargetView; }
			inline ComPtr<ID3D11DepthStencilView> GetDepthStencilView() const { return m_DepthStencilView; }
			inline D3D11_VIEWPORT GetViewport() const { return m_ViewPort; }

			inline static DX11Context* GetContext() { return (DX11Context*)s_Context; }

		protected:
			DX11Context() = default;

		private:
			HWND* windowHandle;
			UINT m_CreationFlags;
			D3D_FEATURE_LEVEL m_featureLevel;
			static std::vector<D3D_FEATURE_LEVEL> m_FeatureLevels;
			ComPtr<ID3D11Device> m_Device;
			ComPtr<ID3D11DeviceContext> m_DeviceContext;
			HRESULT hr;
			uint32_t MSAAQuality;
			ComPtr<IDXGISwapChain1> m_Swapchain;
			ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
			ComPtr<ID3D11Texture2D> m_BackBuffer;
			ComPtr<ID3D11Texture2D> m_DepthStenctilBuffer;
			ComPtr<ID3D11DepthStencilView> m_DepthStencilView;
			ComPtr<ID3D11RasterizerState> RasterState;
			ComPtr<ID3D11DepthStencilState> m_DepthStencilState;
			D3D11_VIEWPORT m_ViewPort;
		};
	}

#endif