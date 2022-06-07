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
     * @brief �f�o�C�X (D3D11�֘A�̐F�X�����)
    */
    ComPtr<ID3D11Device> pDevice;

    /**
     * @brief �R���e�N�X�g (�`��֘A���i��)
    */
    ComPtr<ID3D11DeviceContext> pImContext;

    /**
     * @brief �X���b�v�`�F�C�� (�`����i��)
    */
    ComPtr<IDXGISwapChain> pSwapChain;

    /**
     * @brief �����_�[�^�[�Q�b�g�^�[�Q�b�g�r���[ (�`���)
    */
    ComPtr<ID3D11RenderTargetView> pRTView;

    /**
     * @brief �f�v�X�E�X�e���V���r���[ (Z�o�b�t�@)
    */
    ComPtr<ID3D11DepthStencilView> pDSView;

    /**
     * @brief �r���[�|�[�g (�E�B���h�E�̂ǂ��ɕ`�悷�邩�͈̔�)
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
 * @brief 3D���f���f�[�^
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
 * @brief DX11�}�l�[�W���[
*/
class D3DManager 
{
private:
    /**
     * @brief 
    */
    HWND hWnd;

    /**
     * @brief �e��C���^�[�t�F�[�X
    */
    D3DInf inf;

public:
    /**
     * @brief �R���X�g���N�^
    */
    D3DManager();

    /**
     * @brief 
     * @param hInst 
    */
    void quit(HINSTANCE hInst);

    // General
    /**
     * @brief DX11������
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
     * @brief �C���^�[�t�F�[�X�擾
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