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
RECT p1area, p2area;

//비트맵연습
HBITMAP Line;

int speed = 13; // 막대의 속도

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
char startmessage[] = "-PRESS ENTER TO START-";


// 폰트 및 문자 표시를 위한 함수
void DisplayScore(HDC hdc, int p1score, int p2score, char* message)
{
    HFONT hFont, OldFont;
    TCHAR buffer[80];

    hFont = CreateFont(150, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("FORCED SQUARE"));
    OldFont = (HFONT)SelectObject(hdc, hFont);

    SetTextColor(hdc, RGB(255, 255, 255));
    SetBkMode(hdc, TRANSPARENT);
    swprintf_s(buffer, 80, L"%d", p1score);
    TextOut(hdc, 280, 100, buffer, wcslen(buffer));

    swprintf_s(buffer, 80, L"%d", p2score);
    TextOut(hdc, 900, 100, buffer, wcslen(buffer));


    hFont = CreateFont(50, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("FORCED SQUARE"));
    OldFont = (HFONT)SelectObject(hdc, hFont);

    swprintf_s(buffer, 80, TEXT("%hs"), message);
    TextOut(hdc, 280, 600, buffer, wcslen(buffer));

    SelectObject(hdc, OldFont);
    DeleteObject(hFont);
}
