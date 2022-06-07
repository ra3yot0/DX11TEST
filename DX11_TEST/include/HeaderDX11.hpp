#pragma once
#ifndef _HEADER_HPP_
#define _HEADER_HPP_

#include <DirectXMath.h>
#include <d3d11.h>
#include <windows.h>
#include <wrl/client.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

using Microsoft::WRL::ComPtr;

#endif

struct D3DInf
{
    /**
     * @brief デバイス (D3D11関連の色々を作る)
    */
    ComPtr<ID3D11Device> pDevice;

    /**
     * @brief コンテクスト (描画関連を司る)
    */
    ComPtr<ID3D11DeviceContext> pImContext;

    /**
     * @brief スワップチェイン (描画を司る)
    */
    ComPtr<IDXGISwapChain> pSwapChain;

    /**
     * @brief レンダーターゲットターゲットビュー (描画先)
    */
    ComPtr<ID3D11RenderTargetView> pRTView;

    /**
     * @brief デプス・ステンシルビュー (Zバッファ)
    */
    ComPtr<ID3D11DepthStencilView> pDSView;

    /**
     * @brief ビューポート (ウィンドウのどこに描画するかの範囲)
    */
    D3D11_VIEWPORT viewport;

    // Shader
    /**
     * @brief vertex shader
    */
    ComPtr<ID3D11VertexShader> pVShader;

    /**
     * @brief pixel shader
    */
    ComPtr<ID3D11PixelShader> pPShader;

    // Polygon
    /**
     * @brief 
    */
    ComPtr<ID3D11InputLayout> pILayout;
};

/**
 * @brief vertex
*/
struct Vertex
{
    float pcnu[7];
};

/**
 * @brief 3Dモデルデータ
*/
struct ModelInf 
{
    unsigned int numIdx;
    float posX, posY, posZ;
    float degX, degY, degZ;
    float sclX, sclY, sclZ;
    float colR, colG, colB, colA;
    ComPtr<ID3D11Buffer> pVBuffer;
    ComPtr<ID3D11Buffer> pIBuffer;
};

/**
 * @brief DX11マネージャー
*/
class D3DManager 
{
private:
    /**
     * @brief 
    */
    HWND hWnd;

    /**
     * @brief 各種インターフェース
    */
    D3DInf inf;

public:
    /**
     * @brief コンストラクタ
    */
    D3DManager();

    /**
     * @brief 
     * @param hInst 
    */
    void quit(HINSTANCE hInst);

    // General
    /**
     * @brief DX11初期化
     * @param hInst 
     * @param cmdShow 
     * @param wndName 
     * @param width 
     * @param height 
     * @param windowed 
     * @return 
    */
    bool init(HINSTANCE hInst, int cmdShow, LPCWSTR wndName, unsigned int width, unsigned int height, bool windowed);

    /**
     * @brief 
     * @return 
    */
    HWND* getWindowHandle();

    /**
     * @brief インターフェース取得
     * @return
    */
    D3DInf* getD3DInformation();

    // Drawing
    /**
     * @brief 
    */
    void drawBegin();

    /**
     * @brief 
    */
    void drawEnd();

    // Model
    /**
     * @brief 
     * @param
     * @param
     * @param
     * @param
    */
    bool createModelBuffers(unsigned int numVtx, Vertex* dataPCU, unsigned int* dataIdx, ModelInf* minf);

    /**
     * @brief 
    */
    void drawModel(ModelInf* minf);

    /**
     * @brief 
     * @param i 
    */
    void DebugBox(int i);

    
    void DebugBox(const char* str);
};