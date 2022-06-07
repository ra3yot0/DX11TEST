#include "../include/HeaderDX11.hpp"
#include "../include/Model/HeaderApp.hpp"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPInst, LPSTR pCmd, int cmdShow)
{
    LPCWSTR kNameWnd = L"Test DX11";
    const unsigned int kWidth = 1920U;
    const unsigned int kHeight = 1080U;
    const bool kWindowed = MessageBoxW(nullptr, L"�t���X�N���[���ŋN�����܂���", L"�m�F", MB_YESNO) == IDNO;

    // DirectX11�̏������i����̓E�B���h�E�\�������j
    D3DManager dmanager = D3DManager();
    if (!dmanager.init(hInst, cmdShow, kNameWnd, kWidth, kHeight, kWindowed))
    {
        return 1;
    }

    //���f��������
    ModelSquare model = ModelSquare();
    model.init(&dmanager);

    // ���C�����[�v
    MSG msg;
    while (true)
    {
        if (PeekMessageW(&msg, nullptr, 0U, 0U, PM_REMOVE)) 
        {

            if (msg.message == WM_QUIT)
            {
                break;
            }

            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        else 
        {
            dmanager.drawBegin();
            dmanager.drawModel(&model);
            dmanager.drawEnd();
        }
    }

    //dmanager.quit(hInst);
    UnregisterClassW(kNameWnd, hInst);
	
	return 0;
}