#include "../../include/HeaderDX11.hpp"
#include "../../include/shader/vshader.h"
#include "../../include/shader/pshader.h"

LRESULT WINAPI WndProc(HWND hWnd, unsigned int msg, WPARAM wParam, LPARAM lParam) 
{
    switch (msg) 
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

bool D3DManager::init(HINSTANCE hInst, int cmdShow, LPCWSTR nameWnd, unsigned int width, unsigned int height, bool windowed)
{
    try 
    {
        // Create Window
        {
            // �萔
            const DWORD kDwStyle = windowed ? WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX : WS_POPUP;
            const DWORD kDwExStyle = windowed ? 0 : WS_EX_TOPMOST;
            const int kCmdShow = windowed ? SW_SHOW : SW_SHOWMAXIMIZED;

            // �E�B���h�E�N���X�o�^
            WNDCLASSEXW wcex = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, hInst, nullptr, nullptr, nullptr,
                nullptr, L"DX11_CLASS", nullptr };
            if (!RegisterClassExW(&wcex))
            {
                throw "Error: Failed to register window class.";
            }

            // �E�B���h�E�̃��T�C�Y
            RECT rect;
            rect = { 0, 0, (long)width, (long)height };
            AdjustWindowRectEx(&rect, kDwStyle, false, kDwExStyle);

            // �E�B���h�E�̍쐬
            hWnd = CreateWindowExW(kDwExStyle, L"DX11_CLASS", nameWnd, kDwStyle, CW_USEDEFAULT, CW_USEDEFAULT,
                rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInst, nullptr);
            if (!hWnd)
            {
                throw "Error: Failed to create window handle.";
            }

            // �E�B���h�E�̕\��
            ShowWindow(hWnd, kCmdShow);
            UpdateWindow(hWnd);
            ShowCursor(windowed);
        }

        //Create Factory
        ComPtr<IDXGIFactory> pFactory = nullptr;
        if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf())))
        {
            throw "Error: Failed to create factory.";
        }

        //Create Device
        {
            D3D_FEATURE_LEVEL featureLevels[] = {
                D3D_FEATURE_LEVEL_11_1,
                D3D_FEATURE_LEVEL_11_0,
            };

            if (FAILED(D3D11CreateDevice(
                nullptr,
                D3D_DRIVER_TYPE_HARDWARE,
                nullptr,
                D3D11_CREATE_DEVICE_BGRA_SUPPORT,
                featureLevels,
                ARRAYSIZE(featureLevels),
                D3D11_SDK_VERSION,
                inf.pDevice.GetAddressOf(),
                nullptr,
                inf.pImContext.GetAddressOf())))
            {
                throw "Error: Failed to create Direct3D11 device.";
            }
        }

        //Create SwapChain
        DXGI_SWAP_CHAIN_DESC descSwapChain = {
            {width, height, {60U,1U}, DXGI_FORMAT_R8G8B8A8_UNORM,DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,DXGI_MODE_SCALING_UNSPECIFIED},
            {1,0},
            DXGI_USAGE_RENDER_TARGET_OUTPUT,
            1U,
            hWnd,
            true,
            DXGI_SWAP_EFFECT_DISCARD,
            DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
        };

        if (FAILED(pFactory->CreateSwapChain(inf.pDevice.Get(), &descSwapChain, inf.pSwapChain.GetAddressOf())))
        {
            throw "Error: Failed to create swapchain.";
        }

        // Create Render Target
        {
            ComPtr<ID3D11Texture2D> pBackBuffer = nullptr;
            if (FAILED(inf.pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)pBackBuffer.GetAddressOf())))
            {
                throw "Error: Failed to get back buffer.";
            }

            if (FAILED(inf.pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, inf.pRTView.GetAddressOf())))
            {
                throw "Error: Failed to create render target view.";
            }
        }

        // Create Depth Stencil Buffer
        {
            D3D11_DEPTH_STENCIL_DESC descDS = { 
                true,
                D3D11_DEPTH_WRITE_MASK_ALL, 
                D3D11_COMPARISON_LESS,
                false,
                D3D11_DEFAULT_STENCIL_READ_MASK, D3D11_DEFAULT_STENCIL_WRITE_MASK,
                D3D11_STENCIL_OP_KEEP,
                D3D11_STENCIL_OP_KEEP 
            };

            ComPtr<ID3D11DepthStencilState> pStateDS = nullptr;
            if (FAILED(inf.pDevice->CreateDepthStencilState(&descDS, pStateDS.GetAddressOf())))
            {
                throw "Error: Failed to create depth stancil stencil.";
            }

            inf.pImContext->OMSetDepthStencilState(pStateDS.Get(), 0U);

            D3D11_TEXTURE2D_DESC descDSTex = { 
                width,
                height,
                1U, 
                1U, 
                DXGI_FORMAT_R24G8_TYPELESS,
                {1, 0},
                D3D11_USAGE_DEFAULT,
                D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE,
                0U,
                0U 
            };

            ComPtr<ID3D11Texture2D> pDSTex = nullptr;
            if (FAILED(inf.pDevice->CreateTexture2D(&descDSTex, nullptr, pDSTex.GetAddressOf())))
            {
                throw "Error: Failed to create depth stencil buffer texture.";
            }

            D3D11_DEPTH_STENCIL_VIEW_DESC descView = {
                DXGI_FORMAT_D24_UNORM_S8_UINT,
                D3D11_DSV_DIMENSION_TEXTURE2D,
                0U, 
                {0U}
            };

            if (FAILED(inf.pDevice->CreateDepthStencilView(pDSTex.Get(), &descView, inf.pDSView.GetAddressOf())))
            {
                throw "Error: Failed to create depth stencil buffer view.";
            }
        }

        // Create Viewport
        inf.viewport = { 0.0f, 0.0f, (float)width, (float)height, 0.0f, 1.0f };

        // Create Shader
        if (FAILED(inf.pDevice->CreateVertexShader(g_vs_main, sizeof(g_vs_main), nullptr, inf.pVShader.GetAddressOf())))
        {
            throw "Error: Failed to create vertex shader.";
        }
            
        if (FAILED(inf.pDevice->CreatePixelShader(g_ps_main, sizeof(g_ps_main), nullptr, inf.pPShader.GetAddressOf())))
        {
            throw "Error: Failed to create pixel shader.";
        }

        // Create input element desc
        {
            D3D11_INPUT_ELEMENT_DESC descElem[] = {
                {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
            };

            if (FAILED(inf.pDevice->CreateInputLayout(descElem, ARRAYSIZE(descElem), g_vs_main, sizeof(g_vs_main), inf.pILayout.GetAddressOf())))
            {
                return false;
            }
        }
    }

    //Error�Ή�
    catch (const char* error) 
    {
        DebugBox(error);
        return false;
    }

    return true;
}