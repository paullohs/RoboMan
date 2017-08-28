#include "stdafx.h"
#include "RobomanGUI.h"
#include "GlobalVar.h"
#include "Procedures.h"
#include "Status.h"
#include "commctrl.h"
#include "WinUser.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);
  SetDirectoryToExecutable();
  LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadStringW(hInstance, IDC_ROBOMANGUI, szWindowClass, MAX_LOADSTRING);
  RegisterWindowClasses(hInstance);

  if (!InitInstance (hInstance, nCmdShow)) {
    return FALSE;
  }
  HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ROBOMANGUI));
  MSG msg;
  HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, KeyProc, nullptr, NULL);

  while (GetMessage(&msg, nullptr, NULL, NULL)) {
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
  UnhookWindowsHookEx(hhkLowLevelKybd);
  return (int) msg.wParam;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
  hInst = hInstance;
  HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT, 450, 400, nullptr, nullptr, hInstance, nullptr);
  if (!hWnd)
    return FALSE;
  globHwnd = hWnd;
  // Controls
  controlGroup = CreateWindow(L"BUTTON", L"Controls", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 20, 10, 200, 180, hWnd, 0, GetModuleHandle(0), 0);
  HWND upButton = CreateWindow(L"BUTTON", L"UP", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 70, 25, 50, 50, controlGroup, (HMENU)IDC_CNTRL_UP_BUTTON, nullptr, nullptr);
  HWND dwButton = CreateWindow(L"BUTTON", L"DOWN", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 70, 125, 50, 50, controlGroup, (HMENU)IDC_CNTRL_DW_BUTTON, nullptr, nullptr);
  HWND ltButton = CreateWindow(L"BUTTON", L"LEFT", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 20, 75, 50, 50, controlGroup, (HMENU)IDC_CNTRL_LT_BUTTON, nullptr, nullptr);
  HWND rtButton = CreateWindow(L"BUTTON", L"RIGHT", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 120, 75, 50, 50, controlGroup, (HMENU)IDC_CNTRL_RT_BUTTON, nullptr, nullptr);
  HWND lsrButton = CreateWindow(L"BUTTON", L"FIRE", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 70, 75, 50, 50, controlGroup, (HMENU)IDC_LASER_BUTTON, nullptr, nullptr);
  HWND stepSizeTextBox = CreateWindow(WC_COMBOBOX, TEXT(""), CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL, 150, 20, 40, 100, controlGroup, (HMENU)IDC_STEPSIZE_COMBOBOX, nullptr, nullptr);
  FILLCOMBOBOX(stepSizeTextBox)
  // Commands
  HFONT hFont = CreateFont(32, NULL, NULL, NULL, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Console"));
  cmdGroup = CreateWindow(L"BUTTON", L"Command Line", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 200, 410, 120, hWnd, NULL, GetModuleHandle(NULL), nullptr);
  HWND resultTextBox = CreateWindow(L"Edit", L"", WS_TABSTOP | WS_VISIBLE | WS_DISABLED | WS_CHILD | WS_BORDER, 10, 30, 390, 36, cmdGroup, (HMENU)IDC_RESULT_TEXTBOX, nullptr, nullptr);
  HWND cmdLineTextBox = CreateWindow(L"Edit", L"", WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 70, 390, 36, cmdGroup, (HMENU)IDC_CMDLINE_TEXTBOX, nullptr, nullptr);
  // Status
  angleGroup = CreateWindow(L"BUTTON", L"Status", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 220, 10, 200, 180, hWnd, NULL, GetModuleHandle(NULL), nullptr);
  HWND angle1TextBox = CreateWindow(L"EDIT", L"0", WS_TABSTOP | WS_VISIBLE  | WS_CHILD | WS_BORDER, 60, 20, 75, 36, angleGroup, (HMENU)IDC_ANGLE1_TEXTBOX, nullptr, nullptr);
  HWND angle2TextBox = CreateWindow(L"EDIT", L"0", WS_TABSTOP | WS_VISIBLE | WS_DISABLED | WS_CHILD | WS_BORDER, 60, 60, 75, 36, angleGroup, (HMENU)IDC_ANGLE2_TEXTBOX, nullptr, nullptr);
  HWND laserCheckbox = CreateWindow(L"BUTTON", L"Laser", WS_TABSTOP | WS_VISIBLE | WS_DISABLED | WS_CHILD | BS_CHECKBOX, 60, 100, 75, 36, angleGroup, (HMENU)IDC_LASER_CHECKBOX, nullptr, nullptr);
  HWND getButton = CreateWindow(L"BUTTON", L"Refresh", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 60, 140, 75, 36, angleGroup, (HMENU)IDC_GET_BUTTON, nullptr, nullptr);
  // Adjust handling procedures
  origBtnProc = (WNDPROC)GetWindowLongPtr(dwButton, GWLP_WNDPROC);
  origEditProc = (WNDPROC)GetWindowLongPtr(cmdLineTextBox, GWLP_WNDPROC);
  SetWindowLongPtr(upButton, GWLP_WNDPROC, (LONG_PTR)CntrlBtnProc);
  SetWindowLongPtr(dwButton, GWLP_WNDPROC, (LONG_PTR)CntrlBtnProc);
  SetWindowLongPtr(ltButton, GWLP_WNDPROC, (LONG_PTR)CntrlBtnProc);
  SetWindowLongPtr(rtButton, GWLP_WNDPROC, (LONG_PTR)CntrlBtnProc);
  SetWindowLongPtr(lsrButton, GWLP_WNDPROC, (LONG_PTR)CntrlBtnProc);
  SetWindowLongPtr(getButton, GWLP_WNDPROC, (LONG_PTR)CntrlBtnProc);
  SetWindowLongPtr(cmdLineTextBox, GWLP_WNDPROC, (LONG_PTR)ShProc);
  // Increase font size
  SendMessage(angle1TextBox, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
  SendMessage(angle2TextBox, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
  SendMessage(cmdLineTextBox, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
  SendMessage(resultTextBox, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
  // disable group elements at startup
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  setGroupStatus(angleGroup, false);
  setGroupStatus(cmdGroup, false);
  setGroupStatus(controlGroup, false);
  UNREFERENCED_PARAMETER(laserCheckbox);
  return TRUE;
}

ATOM RegisterWindowClasses(HINSTANCE hInstance) {
  WNDCLASSEXW defaultWin;
  defaultWin.cbSize = sizeof(WNDCLASSEX);
  defaultWin.style = CS_HREDRAW | CS_VREDRAW;
  defaultWin.lpfnWndProc = WndProc;
  defaultWin.cbClsExtra = NULL;
  defaultWin.cbWndExtra = NULL;
  defaultWin.hInstance = hInstance;
  defaultWin.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ROBOMANGUI));
  defaultWin.hCursor = LoadCursor(nullptr, IDC_ARROW);
  defaultWin.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  defaultWin.lpszMenuName = MAKEINTRESOURCEW(IDC_ROBOMANGUI);
  defaultWin.lpszClassName = szWindowClass;
  defaultWin.hIconSm = LoadIcon(defaultWin.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  WNDCLASS lConWin;
  lConWin.lpfnWndProc = (WNDPROC)ConProc;
  lConWin.style = CS_HREDRAW | CS_VREDRAW;
  lConWin.hInstance = hInst;
  lConWin.lpszClassName = CONWIN_NAME;
  lConWin.cbClsExtra = NULL;
  lConWin.cbWndExtra = NULL;
  lConWin.hIcon = NULL;
  lConWin.hCursor = NULL;
  lConWin.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  lConWin.lpszMenuName = NULL;
  RegisterClassW(&lConWin);
  return RegisterClassExW(&defaultWin);
}