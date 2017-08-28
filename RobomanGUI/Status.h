#pragma once
#include <Windows.h>

void laserOnOffWait(void);
BOOL ConnectionWindow(void);
void setGroupStatus(HWND groupHandle, BOOL enable);
BOOL moveServo(enum servo servoOrd, int stepSize);
BOOL moveServoCombobox(enum servo servoOrd, bool direction = true);
INT btoi(TCHAR *buffer);
BOOL RefreshData(bool start = false);
void SetDirectoryToExecutable(void);

enum direction {
  negative = 0,
  positive = 1
};

enum servo {
  one = 1,
  two = 2
};