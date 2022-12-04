// WinAPIPong.cpp : 애플리케이션에 대한 진입점을 정의합니다.
// 함수는 헤더에 구현되있음

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
    if (!InitInstance(hInstance, nCmdShow))
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

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIPONG));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPIPONG);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME, //윈도우 기본 스타일에서 창 크기 최대화, 크기 변경을 비활성화
        CW_USEDEFAULT,
        0,
        wWidth,
        wHeight + 40,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

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
            if (false == p1UpWall) {
                aPress = true;
            }
            break;

        case 0x5a:
            if (false == p1DownWall) {
                zPress = true;
            }
            break;

        case VK_UP:
            if (false == p2UpWall) {
                upPress = true;
            }
            break;

        case VK_DOWN:
            if (false == p2DownWall) {
                downPress = true;
            }
            break;

        case VK_RETURN:
            if (false == startGame) {
                InvalidateRect(hWnd, NULL, true);
                startGame = true;
            }
            break;

        case VK_ESCAPE:
            DestroyWindow(hWnd);
            break;
        }
        //InvalidateRect(hWnd, NULL, true);
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
            zPress = false;
            break;
        case VK_UP:
            upPress = false;
            break;
        case VK_DOWN:
            downPress = false;
            break;
        }

    }
    break;

    case WM_TIMER:

        if (1 == wParam && startGame == true)
        {
            // 타이머 재설정
            KillTimer(hWnd, 1);
            SetTimer(hWnd, 1, g_timer, NULL);

            // 게임 시간 설정
            SetTimer(hWnd, 2, gametime, NULL);

            // 키 입력 플래그에 의한 막대의 움직임
                        //A키를 입력하면 p1 막대가 위로 움직임

            p1Temp = p1;

            if (aPress == true && p1UpWall == false) {
                p1.top -= speed;
                p1.bottom -= speed;
                InvalidateRect(hWnd, &p1Temp, true);
            }
            //Z키를 입력하면 p1 막대가 아래로 움직임
            if (zPress == true && p1DownWall == false) {
                p1.top += speed;
                p1.bottom += speed;
                InvalidateRect(hWnd, &p1Temp, true);
            }

            p2Temp = p2;

            //UP키를 입력하면 p2 막대가 위로 움직임
            if (upPress == true && p2UpWall == false) {
                p2.top -= speed;
                p2.bottom -= speed;
                InvalidateRect(hWnd, &p2Temp, true);
            }
            //DOWN키를 입력하면 p2 막대가 아래로 움직임
            if (downPress == true && p2DownWall == false) {
                p2.top += speed;
                p2.bottom += speed;
                InvalidateRect(hWnd, &p2Temp, true);
            }



            //   막대 벽 구현 공간
                        //p1 막대가 윗쪽 벽에 도달했을 때
            if (p1.top <= 0) {
                p1UpWall = true;
            }
            else {
                p1UpWall = false;
            }
            //p1 막대가 아랫쪽 벽에 도달했을 때
            if (p1.bottom >= wHeight) {
                p1DownWall = true;
            }
            else {
                p1DownWall = false;
            }
            //p2 막대가 윗쪽 벽에 도달했을 때
            if (p2.top <= 0) {
                p2UpWall = true;
            }
            else {
                p2UpWall = false;
            }
            //p2 막대가 아랫쪽 벽에 도달했을 때
            if (p2.bottom >= wHeight) {
                p2DownWall = true;
            }
            else {
                p2DownWall = false;
            }

            ballTemp = ball;

            // 공의 움직임
            ball.top -= bally;
            ball.bottom -= bally;
            ball.left -= ballx;
            ball.right -= ballx;

            // 공이 위아래 벽에 부딪힐 때 방향 전환
            if (ball.top <= 0) {
                bally = -bally;
            }
            if (ball.bottom >= wHeight) {
                bally = -bally;
            }

            // 공이 p1 골에 들어갔을 때
            if (ball.left < -40) {

                p2score++;

                // 공 위치 재설정
                ball.left = (wWidth / 2) - ballSize;
                ball.top = (wHeight / 2) - ballSize;
                ball.right = (wWidth / 2) + ballSize;
                ball.bottom = (wHeight / 2) + ballSize;

                // 방향 반전
                ballx = -ballx;
                InvalidateRect(hWnd, &p2area, true);
            }

            // 공이 p2 골에 들어갔을 때
            if (ball.right >= wWidth + 35) {

                p1score++;

                // 공 위치 재설정
                ball.left = (wWidth / 2) - ballSize;
                ball.top = (wHeight / 2) - ballSize;
                ball.right = (wWidth / 2) + ballSize;
                ball.bottom = (wHeight / 2) + ballSize;

                // 방향 반전
                ballx = -ballx;
                InvalidateRect(hWnd, &p1area, true);
            }

            //RECT isr;

            // 공이 p1 막대와 충돌했을 때
            if (ball.left <= p1.right &&
                ball.left > p1.left &&
                ball.bottom > p1.top &&
                ball.top < p1.bottom) //true == IntersectRect(&isr, &ball, &p1)
            {
                ballx = -ballx;
            }


            if (ball.left <= p1.right &&
                ball.left > p1.left &&
                ball.bottom >= p1.top &&
                ball.bottom < p1.top - 2)
            {
                bally = -bally;
            }

            // 공이 p2 막대와 충돌했을 때
            if (ball.right >= p2.left &&
                ball.right < p2.right &&
                ball.bottom > p2.top &&
                ball.top < p2.bottom) //true == IntersectRect(&isr, &ball, &p2)
            {
                ballx = -ballx;
            }


            if (ball.right >= p2.left &&
                ball.right < p2.right &&
                ball.bottom >= p2.top &&
                ball.bottom < p2.top - 2)
            {
                bally = -bally;
            }

            // P1의 승리
            if (p1score == 10)
            {
                // 타이머를 해제
                KillTimer(hWnd, 1);
                
                MessageBox(hWnd, L"GAME OVER", L"PLAYER 1 WIN!", MB_OK);
                startGame = false;

                // 점수 초기화
                p1score = 0;
                p2score = 0;
                SetTimer(hWnd, 1, g_timer, NULL);

                // 위치 초기화
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

                InvalidateRect(hWnd, NULL, true);
            }

            // P2의 승리
            if (p2score == 10)
            {
                // 타이머를 해제
                KillTimer(hWnd, 1);

                MessageBox(hWnd, L"GAME OVER", L"PLAYER 2 WIN!", MB_OK);
                startGame = false;
                
                // 점수 초기화
                p1score = 0;
                p2score = 0;
                SetTimer(hWnd, 1, g_timer, NULL);

                // 위치 초기화
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

                InvalidateRect(hWnd, NULL, true);
            }

            InvalidateRect(hWnd, &ballTemp, true);
        }  
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hWnd, &ps);      

        // 게임 시작 플래그가 켜졌을 때
        if (startGame == true) 
        {
            DisplayScore(hdc, p1score, p2score);
            DrawLine(hdc);

            Rectangle(hdc, ball.left, ball.top, ball.right, ball.bottom);

            Rectangle(hdc, p1.left, p1.top, p1.right, p1.bottom);
            Rectangle(hdc, p2.left, p2.top, p2.right, p2.bottom);
        }

        // 게임 중이 아닐 때
        else
        {    
            TitleScreen(hdc, guideArea, title, startmessage, guidemessage);
        }
    
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_CREATE:
    {
        g_timer = 10;
        gametime = 1000;
        startGame = false;

        SetTimer(hWnd, 1, g_timer, NULL);

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

        p1area.left = 200;
        p1area.top = 120;
        p1area.right = 430;
        p1area.bottom = 240;

        p2area.left = 850;
        p2area.top = 120;
        p2area.right = 1080;
        p2area.bottom = 240;

        guideArea.left = 180;
        guideArea.top = 280;
        guideArea.right = 1100;
        guideArea.bottom = 680;
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


//필요할때 쓰는 개발 참고용 코드 모음


// WM_PAINT 전용
/*
        MemDC = CreateCompatibleDC(hdc);

        Line = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PONG));
        SelectObject(MemDC, Line);
        BitBlt(hdc, 0, 0, 123, 160, MemDC, 0, 0, SRCCOPY); //복사 및 출력

        DeleteObject(Line);
        */

        /* 중앙 수평 확인용
        MoveToEx(hdc, (wWidth / 2), 0, nullptr);
        LineTo(hdc, wWidth / 2, wHeight);
        MoveToEx(hdc, 0, wHeight / 2, nullptr);
        LineTo(hdc, wWidth, wHeight / 2);
        */

        //Rectangle(hdc, guideArea.left, guideArea.top, guideArea.right, guideArea.bottom);
        //Rectangle(hdc, p1area.left, p1area.top, p1area.right, p1area.bottom);
        //Rectangle(hdc, p2area.left, p2area.top, p2area.right, p2area.bottom);
