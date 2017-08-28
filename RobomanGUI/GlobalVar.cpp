#include "stdafx.h"
#include "../RoboMan/ARDU.hpp"
#define MAX_LOADSTRING 100

ARDU *gArdu = nullptr;
NUM angle1 = -1;
NUM angle2 = -1;
HINSTANCE hInst = nullptr;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
WCHAR CONWIN_NAME[] = L"ConWin";
WNDPROC origBtnProc = nullptr;
WNDPROC origEditProc = nullptr;
HWND globHwnd = nullptr;
HWND conWin = nullptr;
HWND angleGroup = nullptr;
HWND cmdGroup = nullptr;
HWND controlGroup = nullptr;
NUM ARDU::comPort = NULL;