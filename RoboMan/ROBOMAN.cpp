#include "ROBOMAN.hpp"
#include "FILEHANDLER.hpp"
#include "CMD.hpp"
#include "NUM.hpp"
#include "POINTERARM.hpp"
#include "ARDU.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int RoboMan::RoboMain(int argc, char* argv[]) {
  printf("RoboMan 0.0\n");
  if (FILEHANDLER::IsFileReadable("settings.dat")) {
    settingsFile = new FILEHANDLER("settings.dat");
    settingsFile->ApplySettings();
  } else {
    printf("settings.dat not found.\n");
  }
  ardu = new ARDU(ARDU::comPort);

  if (argc == 1) {
    std::string currentCommand;
    printf("[R]aw or [I]nterpreted?\n");
    std::getline(std::cin, currentCommand);

    if (currentCommand == "R"){
      while (true) {
        printf("[R]~ ");
        std::getline(std::cin, currentCommand);
        switch (currentCommand[0]) {
        case 'Q': ardu->SendBuffer(std::string("Q"));
                  printf(ardu->ReadBuffer().c_str());
                  break;
        default: ardu->SendBuffer(currentCommand);
                 break;
        }
      }
    }
    else if (currentCommand == "I") {
      while (true) {
        printf("[I]~ ");
        std::getline(std::cin, currentCommand);
        CMD realCommand;
        ardu->SendCommand(realCommand = POINTERARM::InterpretLine(currentCommand));
        switch (realCommand.command) {
          case MOVE:
            printf("Angles set to: %s \n", POINTERARM::CommandToBuffer(realCommand).c_str());
            break;
          case LASER:
            printf("Laser set to: %s \n", POINTERARM::CommandToBuffer(realCommand).c_str());
            break;
          default:
            break;
        }
      }
    }
    return FALSE;
  } else {
    if (FILEHANDLER::IsFileReadable(argv[1])) {
      commandFile = new FILEHANDLER(argv[1]);
      printf("Using file \"%s\".\n", commandFile->GetFileName());
    } else {
      printf("Error in command file.\n");
      return FALSE;
    }
    commandDeque = new CMD_DEQUE(POINTERARM::GenerateCommandDeque(commandFile->GetLines()));
    printf("Press [ENTER] to start %zd commands from \"%s\". \n", commandDeque->size(), commandFile->GetFileName());
    getchar();
    while(!commandDeque->empty()) {
      CMD *current = &commandDeque->front();
      commandDeque->pop_front();
      ardu->SendCommand(*current);
      Sleep(500);
    }
  }
  return FALSE;
}

int main(int argc, char* argv[]) {
  return RoboMan::RoboMain(argc, argv);
}