// WinAPIPong.cpp : 애플리케이션에 대한 진입점을 정의합니다.
// https://austinmorlan.com/posts/pong_clone/

#include "framework.h"
#include "WinAPIPong.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPIPONG, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIPONG));

    MSG msg;

    // 기본 메시지 루프입니다:
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



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIPONG));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPIPONG);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//

//너비
int wWidth = 1280;
//높이
int wHeight = 900;




BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, wWidth, wHeight+60, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

// 공의 크기
int ballSize = 20;

// 1p 패들 높이
int p1Height = 90;
// 1p 패들 폭
int p1Width = 15;

// 2p 패들 높이
int p2Height = 90;
// 2p 패들 폭
int p2Width = 15;

HDC hdc;

RECT ball, p1, p2;

int speed = 15;

bool aPress, zPress, upPress, downPress = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case 0x41:
            aPress = true;
            break;
        case 0x5a:
            p1.top += speed;
            p1.bottom += speed;
            break;
        case VK_UP:
            p2.top -= speed;
            p2.bottom -= speed;
            break;
        case VK_DOWN:
            p2.top += speed;
            p2.bottom += speed;
            break;
        }
        if(aPress == true) {
            p1.top -= speed;
            p1.bottom -= speed;
        }
        InvalidateRect(hWnd, NULL, true);
    }
    break;

    case WM_KEYUP:
    {
        switch (wParam)
        {
        case 0x41:
            aPress = false;
            break;
        case 0x5a:
            p1.top += speed;
            p1.bottom += speed;
            break;
        case VK_UP:
            p2.top -= speed;
            p2.bottom -= speed;
            break;
        case VK_DOWN:
            p2.top += speed;
            p2.bottom += speed;
            break;
        }
        InvalidateRect(hWnd, NULL, true);
    }
    break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);
            
            /* 중앙 수평 확인용
            MoveToEx(hdc, (wWidth / 2), 0, nullptr);
            LineTo(hdc, wWidth / 2, wHeight);
            MoveToEx(hdc, 0, wHeight / 2, nullptr);
            LineTo(hdc, wWidth, wHeight / 2);
            */

            Ellipse(hdc, ball.left, ball.top, ball.right, ball.bottom);

            Rectangle(hdc, p1.left, p1.top, p1.right, p1.bottom);
            Rectangle(hdc, p2.left, p2.top, p2.right, p2.bottom);

            EndPaint(hWnd, &ps);
        }
        break;

    case WM_CREATE:
    {
        ball.left = (wWidth / 2) - ballSize;
        ball.top = (wHeight / 2) - ballSize;
        ball.right = (wWidth / 2) + ballSize;
        ball.bottom = (wHeight / 2) + ballSize;

        p1.left = 70 - p1Width;
        p1.top = (wHeight / 2) - p1Height;
        p1.right = 70 + p1Width;
        p1.bottom = (wHeight / 2) + p1Height;

        p2.left = (wWidth - 90) - p2Width;
        p2.top = (wHeight / 2) - p2Height;
        p2.right = (wWidth - 90) + p2Width;
        p2.bottom = (wHeight / 2) + p2Height;
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

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
