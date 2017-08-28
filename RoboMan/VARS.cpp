#include "ROBOMAN.hpp"
#include "ARDU.hpp"
#include "CMD.hpp"
#include "FILEHANDLER.hpp"

ARDU *RoboMan::ardu = nullptr;
FILEHANDLER *RoboMan::commandFile = nullptr;
CMD_DEQUE *RoboMan::commandDeque = nullptr;
FILEHANDLER *RoboMan::settingsFile = nullptr;
NUM ARDU::comPort = NULL;