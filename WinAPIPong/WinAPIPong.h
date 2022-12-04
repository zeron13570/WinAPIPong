#pragma once

#include "resource.h"


//너비
#define wWidth 1280
//높이
#define wHeight  960

// 공의 크기
int ballSize = 15;

// 1p 패들 높이
int p1Height = 60;
// 1p 패들 폭
int p1Width = 8;

// 2p 패들 높이
int p2Height = 60;
// 2p 패들 폭
int p2Width = 8;

HDC hdc, MemDC;

//공, 패들
RECT ball, p1, p2;

// 무효화를 위해 이전 위치 메모를 위한 유령 공, 패들
RECT ballTemp, p1Temp, p2Temp;

// 점수판 영역 갱신을 위한 사각형 영역
RECT p1area, p2area;

// 텍스트 공간
RECT guideArea;

// 선
RECT Line;

int speed = 17; // 막대의 속도

int ballx = 11; // 공의 x축 방향 및 속도
int bally = 11; // 공의 y축 방향 및 속도
int p1score = 0; // 1p 점수
int p2score = 0; // 2p 점수

//키 눌림 
bool aPress, zPress, upPress, downPress = false;

//벽 감지
bool p1UpWall, p1DownWall, p2UpWall, p2DownWall = false;

//게임 시작 플래그
bool startGame = false;

//타이머들
int g_timer, gametime;

//시작 시 표시되는 메세지
char title[] = "PONG";
char startmessage[] = "- PRESS [ENTER] TO START -";
LPCWSTR guidemessage = TEXT("- HOW TO PLAY -\n\n")
                       TEXT("You need to obtain 10 points when your opponent misses the ball to win.\n\n\n")
                       TEXT("- KEYS -\n\n")
                       TEXT("Left Side Player :   Press Key [A] And [Z] To Move\n")
                       TEXT("Right Side Player :   Press Key [UP] And [DOWN] To Move\n\n")
                       TEXT("Exit Game :  Press Key [ESC]\n");


// 점수 표시를 위한 함수
void DisplayScore(HDC hdc, int p1score, int p2score)
{
    HFONT hFont, OldFont;
    TCHAR buffer[256];

    hFont = CreateFont(150, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("FORCED SQUARE"));
    OldFont = (HFONT)SelectObject(hdc, hFont);

    SetTextColor(hdc, RGB(255, 255, 255));
    SetBkMode(hdc, TRANSPARENT);
    swprintf_s(buffer, 80, L"%d", p1score);
    TextOut(hdc, 280, 100, buffer, wcslen(buffer));

    swprintf_s(buffer, 80, L"%d", p2score);
    TextOut(hdc, 900, 100, buffer, wcslen(buffer));

    SelectObject(hdc, OldFont);
    DeleteObject(hFont);
}


// 처음 화면에서 호출되는 함수
void TitleScreen(HDC hdc, RECT rt, char* title, char* startmessage, LPCWSTR guidemessage)
{
    HFONT hFont, OldFont;
    TCHAR buffer[256];
    SetTextColor(hdc, RGB(255, 255, 255));
    SetBkMode(hdc, TRANSPARENT);

    // 타이틀 로고
    hFont = CreateFont(150, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("FORCED SQUARE"));
    OldFont = (HFONT)SelectObject(hdc, hFont);

    swprintf_s(buffer, 256, TEXT("%hs"), title);
    TextOut(hdc, 445, 60, buffer, wcslen(buffer));

    // 룰, 키 설명
    hFont = CreateFont(30, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("FORCED SQUARE"));
    OldFont = (HFONT)SelectObject(hdc, hFont);

    DrawText(hdc, guidemessage, -1, &rt, DT_CENTER | DT_WORDBREAK);

    // 시작 안내 메세지
    hFont = CreateFont(50, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("FORCED SQUARE"));
    OldFont = (HFONT)SelectObject(hdc, hFont);

    swprintf_s(buffer, 256, TEXT("%hs"), startmessage);
    TextOut(hdc, 280, 720, buffer, wcslen(buffer));

    
    SelectObject(hdc, OldFont);
    DeleteObject(hFont);
}

// 경기장의 선을 그리는 함수
void DrawLine(HDC hdc) 
{
    HPEN NewPen = CreatePen(PS_DASH, 1, RGB(255, 255, 255));
    HPEN OldPen = (HPEN)SelectObject(hdc, NewPen);

    MoveToEx(hdc, (wWidth / 2), 0, nullptr);
    LineTo(hdc, wWidth / 2, wHeight);

    SelectObject(hdc, OldPen);
    DeleteObject(NewPen);
}