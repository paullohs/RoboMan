#pragma once
#include <Windows.h>
#include "../RoboMan/ARDU.hpp"

extern ARDU *gArdu;
extern NUM angle1;
extern NUM angle2;
extern HINSTANCE hInst;
extern WCHAR szTitle[];
extern WCHAR szWindowClass[];
extern WCHAR CONWIN_NAME[];
extern WNDPROC origBtnProc;
extern WNDPROC origEditProc;
extern HWND globHwnd;
extern HWND conWin;
extern HWND angleGroup;
extern HWND cmdGroup;
extern HWND controlGroup;