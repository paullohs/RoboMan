#pragma once
#include "resource.h"
#include <windows.h>

ATOM RegisterWindowClasses(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);

#define FILLCOMBOBOX(box) TCHAR Steps[10][3] = { TEXT("1"), TEXT("2"), TEXT("3"), TEXT("4"), TEXT("5"), TEXT("6"), TEXT("7"), TEXT("8"), TEXT("9"), TEXT("10") }; \
                                                                                                                                                TCHAR A[30]; \
                                                                                                                                   memset(&A, 0, sizeof(A)); \
                                                                                                                              for (int k = 0; k <= 9; k++) { \
                                                                                                   wcscpy_s(A, sizeof(A) / sizeof(TCHAR), (TCHAR*)Steps[k]); \
                                                                                     SendMessage(box, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A);             \
                                                                                                                                                           } \
                                                                                           SendMessage(box, CB_SETCURSEL, (WPARAM)4, (LPARAM)0);