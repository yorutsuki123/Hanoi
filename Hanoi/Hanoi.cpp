// Hanoi.cpp : 定義應用程式的進入點。
//
#include <string>
#include "framework.h"
#include "Hanoi.h"
#include "RunHanoi.h"

#define MAX_LOADSTRING 100

// 全域變數:
HINSTANCE hInst;                                // 目前執行個體
WCHAR szTitle[MAX_LOADSTRING];                  // 標題列文字
WCHAR szWindowClass[MAX_LOADSTRING];            // 主視窗類別名稱
HWND mainWnd, labelWnd, inputboxWnd, btnWnd;
RECT rect;

bool isRunning;
hanoi::Stacks hanoiStacks;

// 這個程式碼模組所包含之函式的向前宣告:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    // 將全域字串初始化
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HANOI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    rect = RECT{ 0, 0, 350, 300 };

    // 執行應用程式初始化:
    if (!InitInstance (hInstance, nCmdShow))
        return FALSE;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HANOI));
    MSG msg;

    // 主訊息迴圈:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HANOI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HANOI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 將執行個體控制代碼儲存在全域變數中

   mainWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, CW_USEDEFAULT, rect.right, rect.bottom, nullptr, nullptr, hInstance, nullptr);
   if (!mainWnd)
      return FALSE;
   labelWnd = CreateWindowW(L"static", L"輸入層數（1～8）", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 11, 135, 18, mainWnd, nullptr, nullptr, nullptr);
   inputboxWnd = CreateWindowW(L"Edit", L"3", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 150, 10, 50, 20, mainWnd, nullptr, nullptr, nullptr);
   btnWnd = CreateWindowW(L"Button", L"開始！", WS_VISIBLE | WS_CHILD | SS_CENTER, 240, 10, 50, 20, mainWnd, (HMENU)START, nullptr, nullptr);

   ShowWindow(mainWnd, nCmdShow);
   UpdateWindow(mainWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::wstring ws;
    std::string str;
    int la;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 剖析功能表選取項目:
            switch (wmId)
            {
            case START:
                if (!isRunning)
                {
                    wchar_t text[105];
                    GetWindowTextW(inputboxWnd, text, 100);
                    ws = std::wstring(text);
                    str = std::string(ws.begin(), ws.end());
                    la = std::stoi("0" + str);
                    if (la < 1 || la > MAX_LAYER)
                    {
                        MessageBoxW(NULL,
                            _T("層數超出範圍了QQ"),
                            _T("ERROR"),
                            MB_OK);
                    }
                    else
                    {
                        hanoi::initHanoi(la);
                        hanoiStacks = hanoi::getStacks();
                        InvalidateRect(mainWnd, &rect, true);
                    }
                    isRunning = true;
                    SetWindowTextW(btnWnd, L"下一步");
                }
                else
                {

                    hanoiStacks = hanoi::nextStacks();
                    InvalidateRect(mainWnd, &rect, true);
                    if (hanoiStacks.isDone) 
                    {
                        isRunning = false;
                        SetWindowTextW(btnWnd, L"開始！");
                    }
                }
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此新增任何使用 hdc 的繪圖程式碼...
            RECT r = { 21, 210, 313, 230 };
            RECT sr[3] = {
                { 163 - 100, 100, 171 - 100, 230 },
                { 163, 100, 171, 230 },
                { 163 + 100, 100, 171 + 100, 230 },
            };
            FillRect(hdc, &r, CreateSolidBrush(RGB(100, 100, 100)));
            for (int i = 0; i < 3; i++)
            {
                FillRect(hdc, &sr[i], CreateSolidBrush(RGB(100, 100, 100)));
                for (int j = 0; j < hanoiStacks.length[i]; j++)
                {
                    int val = hanoiStacks.stack[i][j];
                    RECT rr = { sr[i].left - val * 5, 208 - j * 12, sr[i].right + val * 5, 198 - j * 12 };
                    FillRect(hdc, &rr, CreateSolidBrush(RGB(100, 200, 255)));
                }
            }
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
