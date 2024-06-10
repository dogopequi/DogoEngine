#include "dgpch.h"
#if DG_PLATFORM_WINDOWS
#include "DX11Context.h"
#include "Dogo/Core.h"
#include "Dogo/Logger.h"
#include "Graphics/WindowsWindow.h"

namespace Dogo
{
	DX11Context::DX11Context(HWND* handle)
	{
		windowHandle = handle;
	}
	DX11Context::~DX11Context()
	{
		delete windowHandle;
	}
	bool DX11Context::Init()
	{
		bool Enable4xMSAA = false;
		m_CreationFlags = 0;

#ifdef DG_DEBUG
		m_CreationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		std::vector<D3D_FEATURE_LEVEL> m_FeatureLevels;
		m_FeatureLevels.push_back(D3D_FEATURE_LEVEL_11_1);
		m_FeatureLevels.push_back(D3D_FEATURE_LEVEL_11_0);

		hr = (D3D11CreateDevice
		(
			nullptr,                            // specify nullptr to use the default adapter
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			m_CreationFlags,
			m_FeatureLevels.data(),
			static_cast<UINT>(m_FeatureLevels.size()),
			D3D11_SDK_VERSION,
			m_Device.ReleaseAndGetAddressOf(),    // returns the Direct3D device created
			&m_featureLevel,                    // returns feature level of device created
			m_DeviceContext.ReleaseAndGetAddressOf()
		));
		if (FAILED(hr))
		{
			MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
			DG_FATAL("D3D11CreateDevice Failed.");
		}

		m_Device.Get()->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &MSAAQuality);
		DG_ASSERT(MSAAQuality > 0);


		// First, retrieve the underlying DXGI Device from the D3D Device.
		ComPtr<IDXGIDevice1> pDXGIDevice;
		hr = (m_Device.As(&pDXGIDevice));

		ComPtr<IDXGIAdapter> pDXGIAdapter;
		hr = pDXGIDevice->GetAdapter(&pDXGIAdapter);
		if (FAILED(hr))
		{
			MessageBox(0, L"Failed to get adapter", 0, 0);
			DG_FATAL("Failed to get adapter");
		}

		ComPtr<IDXGIFactory2> pIDXGIFactory;
		pDXGIAdapter->GetParent(IID_PPV_ARGS(pIDXGIFactory.GetAddressOf()));

		// Create a descriptor for the swap chain.
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.Width = 1280;
		swapChainDesc.Height = 720;
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		if (Enable4xMSAA)
		{
			swapChainDesc.SampleDesc.Count = 4;
			swapChainDesc.SampleDesc.Quality = MSAAQuality - 1;
		}
		else
		{
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
		}
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
		fsSwapChainDesc.Windowed = TRUE;

		// Create a SwapChain from a Win32 window.
		hr = (pIDXGIFactory->CreateSwapChainForHwnd
		(
			m_Device.Get(),
			*windowHandle,
			&swapChainDesc,
			&fsSwapChainDesc,
			nullptr,
			m_Swapchain.ReleaseAndGetAddressOf()
		));
		if (FAILED(hr))
		{
			MessageBox(0, L"Failed to create swapchain", 0, 0);
			DG_FATAL("Failed to create swapchain");
		}

		m_Swapchain.Get()->GetBuffer(0, IID_PPV_ARGS(m_BackBuffer.GetAddressOf()));
		m_Device.Get()->CreateRenderTargetView(m_BackBuffer.Get(), nullptr, m_RenderTargetView.GetAddressOf());

		D3D11_TEXTURE2D_DESC depthStencilDesc;
		depthStencilDesc.Width = 1280;
		depthStencilDesc.Height = 720;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
		if (Enable4xMSAA)
		{
			depthStencilDesc.SampleDesc.Count = 4;
			depthStencilDesc.SampleDesc.Quality = MSAAQuality - 1;
		}
		else
		{
			depthStencilDesc.SampleDesc.Count = 1;
			depthStencilDesc.SampleDesc.Quality = 0;
		}
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = NULL;
		depthStencilDesc.MiscFlags = NULL;


		hr = (m_Device.Get()->CreateTexture2D(&depthStencilDesc, NULL, m_DepthStenctilBuffer.GetAddressOf()));
		if (FAILED(hr))
		{
			MessageBox(0, L"Failed to create texture to draw to", 0, 0);
			DG_FATAL("Failed to create texture to draw to");
		}
		hr = (m_Device.Get()->CreateDepthStencilView(m_DepthStenctilBuffer.Get(), NULL, m_DepthStencilView.GetAddressOf()));
		if (FAILED(hr))
		{
			MessageBox(0, L"Failed to create depth stencil view", 0, 0);
			DG_FATAL("Failed to create depth stencil view");
		}

		// Define the depth stencil state
		D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
		ZeroMemory(&depthStencilStateDesc, sizeof(depthStencilStateDesc));
		depthStencilStateDesc.DepthEnable = TRUE;
		depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
		depthStencilStateDesc.StencilEnable = FALSE;
		// Create the depth stencil state object
		m_Device.Get()->CreateDepthStencilState(&depthStencilStateDesc, m_DepthStencilState.GetAddressOf());

		// Set the depth stencil state
		m_DeviceContext.Get()->OMSetDepthStencilState(m_DepthStencilState.Get(), 1);

		m_DeviceContext.Get()->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());

		m_ViewPort.TopLeftX = 0.0f;
		m_ViewPort.TopLeftY = 0.0f;
		m_ViewPort.Width = 1280;
		m_ViewPort.Height = 720;
		m_ViewPort.MinDepth = 0.0f;
		m_ViewPort.MaxDepth = 1.0f;

		m_DeviceContext.Get()->RSSetViewports(1, &m_ViewPort);

		D3D11_RASTERIZER_DESC rsDesc{};
		rsDesc.AntialiasedLineEnable = false;
		rsDesc.CullMode = D3D11_CULL_NONE;
		rsDesc.DepthBias = 0;
		rsDesc.DepthBiasClamp = 0.0f;
		rsDesc.DepthClipEnable = true;
		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.FrontCounterClockwise = true;
		rsDesc.MultisampleEnable = false;
		rsDesc.ScissorEnable = false;
		rsDesc.SlopeScaledDepthBias = 0.0f;
		m_Device.Get()->CreateRasterizerState(&rsDesc, RasterState.GetAddressOf());
		m_DeviceContext.Get()->RSSetState(RasterState.Get());


		return true;
	}
	void DX11Context::SwapBuffer()
	{
		HRESULT hr = m_Swapchain.Get()->Present(1, 0);
		if (FAILED(hr))
		{
			DG_ERROR("Failed to present");
		}
	}
	void DX11Context::Shutdown()
	{
		if (m_Device)
		{
			m_Device->Release();
			m_Device = nullptr;
		}
		if (m_DeviceContext)
		{
			m_DeviceContext->Release();
			m_DeviceContext = nullptr;
		}
		if (m_Swapchain)
		{
			m_Swapchain->Release();
			m_Swapchain = nullptr;
		}
		if (m_RenderTargetView)
		{
			m_RenderTargetView->Release();
			m_RenderTargetView = nullptr;
		}
		if (m_BackBuffer)
		{
			m_BackBuffer->Release();
			m_BackBuffer = nullptr;
		}
		if (m_DepthStenctilBuffer)
		{
			m_DepthStenctilBuffer->Release();
			m_DepthStenctilBuffer = nullptr;
		}
		if (m_DepthStencilView)
		{
			m_DepthStencilView->Release();
			m_DepthStencilView = nullptr;
		}
	}

	void DX11Context::ClearColor(float x, float y, float z, float a)
	{
		float clearDepth = 1.0f;
		UINT8 clearStencil = 0;
		m_DeviceContext.Get()->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, clearDepth, clearStencil);
		float clearColor[4] = {x, y, z, a };
		m_DeviceContext.Get()->ClearRenderTargetView(m_RenderTargetView.Get(), clearColor);
	}

}
#endif