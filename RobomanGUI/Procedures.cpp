#include "stdafx.h"
#include "Procedures.h"
#include "Resource.h"
#include "Status.h"
#include "../RoboMan/ARDU.hpp"
#include "../RoboMan/FILEHANDLER.hpp"
#include "GlobalVar.h"
#include <Windows.h>
#include <thread>
#include <vector>
#include <string>
#include <boost\algorithm\string\split.hpp>
#include <boost\algorithm\string\trim.hpp>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
    case WM_COMMAND:
      switch (LOWORD(wParam)) {
      case IDC_GET_BUTTON:
      case IDC_CNTRL_UP_BUTTON:
      case IDC_CNTRL_DW_BUTTON:
      case IDC_CNTRL_LT_BUTTON:
      case IDC_CNTRL_RT_BUTTON:
        break;
      case IDM_CONNECT:
        ConnectionWindow();
        break;
      case IDM_EXIT:
        DestroyWindow(hWnd);
        break;
      case IDC_COM_DEFAULT:
      {
        if (FILEHANDLER::IsFileReadable("settings.dat")) {
          FILEHANDLER settings("settings.dat");
          settings.ApplySettings();
          gArdu = new ARDU(NUM(ARDU::GetStaticComPort()));
          if (gArdu->isOpen) {
            setGroupStatus(angleGroup, true);
            setGroupStatus(cmdGroup, true);
            setGroupStatus(controlGroup, true);
            RefreshData(true);
          }
          else {
            delete gArdu;
            gArdu = nullptr;
            MessageBox(hWnd, L"Could not Connect.", L"Error", MB_OK);
          }
        }
        else {
          MessageBox(hWnd, L"No settings.dat found.", L"Error", MB_OK);
        }
      }
        break;
      default:
        return DefWindowProc(hWnd, message, wParam, lParam);
      }
      break;
    case WM_KEYDOWN:
    {

      break;
    }
    case WM_PAINT:
    {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hWnd, &ps);
      UNREFERENCED_PARAMETER(hdc);
      EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
  }
  return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK CntrlBtnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
    case WM_LBUTTONDOWN:
      switch (GetDlgCtrlID(hWnd)) {
        case IDC_GET_BUTTON:
          RefreshData();
        break;
        case IDC_CNTRL_UP_BUTTON:
          moveServoCombobox(servo::two, direction::positive);
          break;
        case IDC_CNTRL_DW_BUTTON:
          moveServoCombobox(servo::two, direction::negative);
          break;
        case IDC_CNTRL_LT_BUTTON:
          moveServoCombobox(servo::one, direction::negative);
          break;
        case IDC_CNTRL_RT_BUTTON:
          moveServoCombobox(servo::one, direction::positive);
          break;
        case IDC_LASER_BUTTON:
          new std::thread(laserOnOffWait);
          break;
        case IDC_COM_BUTTON:
          TCHAR buffer[3];
          GetWindowText(GetDlgItem(GetParent(hWnd), IDC_COM_COMBOBOX), buffer, 2);
          gArdu = new ARDU(NUM(std::stoi(std::wstring(buffer))));
          if (gArdu->isOpen) {
            setGroupStatus(angleGroup, true);
            setGroupStatus(cmdGroup, true);
            setGroupStatus(controlGroup, true);
            RefreshData(true);
          }
          else {
            delete[] gArdu;
            gArdu = nullptr;
            MessageBox(hWnd, L"Could not Connect.", L"Error", MB_OK);
          }
          DestroyWindow(conWin);
          break;
      }
      break;
  }
  return CallWindowProc(origBtnProc, hWnd, message, wParam, lParam);
}

LRESULT CALLBACK AnFldProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  return CallWindowProc(origEditProc, hWnd, message, wParam, lParam);
}

LRESULT CALLBACK ShProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
    case WM_KEYDOWN:
    {
      switch (LOWORD(wParam)) {
        case VK_RETURN:
        {
          static char buffer[1024];
          GetWindowTextA(GetDlgItem(GetParent(hWnd), IDC_CMDLINE_TEXTBOX), buffer, 1024);
          gArdu->ARDU::SendBuffer(buffer);
          SetWindowTextA(GetDlgItem(GetParent(hWnd), IDC_CMDLINE_TEXTBOX), "");
          if (!std::string(buffer).compare("Q")) {
            std::string returnVal = gArdu->ARDU::ReadBuffer();
            SetWindowTextA(GetDlgItem(GetParent(hWnd), IDC_RESULT_TEXTBOX), returnVal.c_str());
          }
          RefreshData();
        }
        break;
      }
    }
  }
  return CallWindowProc(origEditProc, hWnd, message, wParam, lParam);
}

LRESULT CALLBACK ConProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
  case WM_COMMAND:
    switch (LOWORD(wParam)) {
    case IDM_CONNECT:
      ConnectionWindow();
      break;
    case IDM_EXIT:
      DestroyWindow(hWnd);
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
    }
    break;
  case WM_PAINT:
  {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    UNREFERENCED_PARAMETER(hdc);
    EndPaint(hWnd, &ps);
  }
  break;
  }
  return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK KeyProc(int nCode, WPARAM wParam, LPARAM lParam) {
  if (gArdu && gArdu->isOpen) {
    if (nCode == HC_ACTION) {
      switch (wParam) {
        case WM_SYSKEYDOWN:
        {
          PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
          switch (p->vkCode) {
          case VK_LEFT:
            moveServoCombobox(servo::one, direction::negative);
            RefreshData();
            break;
          case VK_RIGHT:
            moveServoCombobox(servo::one, direction::positive);
            RefreshData();
            break;
          case VK_UP:
            moveServoCombobox(servo::two, direction::positive);
            RefreshData();
            break;
          case VK_DOWN:
            moveServoCombobox(servo::two, direction::negative);
            RefreshData();
            break;
          case VK_SPACE:
            new std::thread(laserOnOffWait);
            RefreshData();
            break;
          }
        }
      }
    }
  }
  return CallNextHookEx(NULL, nCode, wParam, lParam);
}