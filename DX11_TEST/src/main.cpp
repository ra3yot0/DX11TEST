#include "../include/HeaderDX11.hpp"
#include "../include/Model/HeaderApp.hpp"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPInst, LPSTR pCmd, int cmdShow)
{
    LPCWSTR kNameWnd = L"Test DX11";
    const unsigned int kWidth = 1920U;
    const unsigned int kHeight = 1080U;
    const bool kWindowed = MessageBoxW(nullptr, L"フルスクリーンで起動しますか", L"確認", MB_YESNO) == IDNO;

    // DirectX11の初期化（今回はウィンドウ表示だけ）
    D3DManager dmanager = D3DManager();
    if (!dmanager.init(hInst, cmdShow, kNameWnd, kWidth, kHeight, kWindowed))
    {
        return 1;
    }

    //モデル初期化
    ModelSquare model = ModelSquare();
    model.init(&dmanager);

    // メインループ
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