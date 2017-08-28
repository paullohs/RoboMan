#include "stdafx.h"
#include "GlobalVar.h"
#include "Procedures.h"
#include "RobomanGUI.h"
#include "Status.h"
#include "commctrl.h"
#include "Pathcch.h"
#include <windows.h>
#include <thread>
#include <boost\algorithm\string\split.hpp>
#include <boost\algorithm\string\trim.hpp>
#include <boost\thread\thread.hpp>

void laserOnOffWait(void) {
  gArdu->SendBuffer("ON");
  boost::this_thread::sleep(boost::posix_time::milliseconds(500));
  gArdu->SendBuffer("NO");
}

void setGroupStatus(HWND groupHandle, BOOL enable) {
  HWND hWndChild = nullptr;
  hWndChild = ::GetWindow(groupHandle, GW_CHILD);
  while (hWndChild) {
    EnableWindow(hWndChild, enable);
    hWndChild = GetWindow(hWndChild, GW_HWNDNEXT);
  }
}

BOOL ConnectionWindow(void) {
  conWin = CreateWindow(L"ConWin", L"Connection", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, CW_USEDEFAULT, 0, 100, 100, globHwnd, nullptr, hInst, nullptr);
  HWND comText = CreateWindow(L"STATIC", L"Port:", WS_VISIBLE | WS_CHILD, 10, 10, 40, 20, conWin, nullptr, nullptr, nullptr);
  HWND okButton = CreateWindow(L"BUTTON", L"Connect", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 10, 35, 100, 20, conWin, (HMENU)IDC_COM_BUTTON, nullptr, nullptr);
  HWND comBox = CreateWindow(WC_COMBOBOX, TEXT(""), CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL, 60, 10, 40, 100, conWin, (HMENU)IDC_COM_COMBOBOX, nullptr, nullptr);
  FILLCOMBOBOX(comBox)
  SetWindowLongPtr(okButton, GWLP_WNDPROC, (LONG_PTR)CntrlBtnProc);
  ShowWindow(conWin, TRUE);
  UNREFERENCED_PARAMETER(comText);
  return conWin ? TRUE : FALSE;
}

BOOL moveServo(enum servo servoOrd, int stepSize) {
  switch (servoOrd) {
    case servo::one:
      gArdu->SendBuffer((std::to_string(stepSize) + ";" + "+0").c_str());
      return TRUE;
    case servo::two:
      gArdu->SendBuffer((std::string("+0") + ";" + std::to_string(stepSize)).c_str());
      return TRUE;
  }
  return FALSE;
}

INT btoi(TCHAR *buffer) {
  if (buffer[0]) {
    return std::stoi(std::wstring(buffer));
  }
  return NULL;
}

BOOL moveServoCombobox(enum servo servoOrd, bool direction) {
  TCHAR buffer[3];
  GetWindowText(GetDlgItem(controlGroup, IDC_STEPSIZE_COMBOBOX), buffer, 2);
  moveServo(servoOrd, direction ? btoi(buffer) : -btoi(buffer));
  return TRUE;
}

BOOL RefreshThread(void) {
  gArdu->SendBuffer("Q");
  boost::this_thread::sleep(boost::posix_time::milliseconds(200));
  std::string buffer = gArdu->ReadBuffer();
  std::vector<std::string> splitVec;
  boost::split(splitVec, buffer, boost::is_any_of(";"), boost::token_compress_on);
  if (splitVec.size() == 3) {
    SetWindowTextA(GetDlgItem(angleGroup, IDC_ANGLE1_TEXTBOX), splitVec[0].c_str());
    angle1 = std::stoi(splitVec[0].c_str());
    SetWindowTextA(GetDlgItem(angleGroup, IDC_ANGLE2_TEXTBOX), splitVec[1].c_str());
    angle2 = std::stoi(splitVec[1].c_str());
    SendMessageA(GetDlgItem(angleGroup, IDC_LASER_CHECKBOX), BM_SETCHECK, splitVec[2][0] == '1' ? BST_CHECKED : BST_UNCHECKED, 0);
    return TRUE;
  }
  return FALSE;
}

BOOL RefreshData(bool start) {
  if (start) {
    boost::this_thread::sleep(boost::posix_time::milliseconds(200));
  }
  new std::thread(RefreshThread);
  return TRUE;
}

void SetDirectoryToExecutable(void) {
  TCHAR buffer[100];
  GetModuleFileName(NULL, buffer, 100);
  PathCchRemoveFileSpec(buffer, 100);
  SetCurrentDirectory(buffer);
}
