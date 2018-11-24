#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "terminal.h"

#define CTRL_KEY(keyFollowingCtrl) (keyFollowingCtrl & 0x1f)

void editorMoveCursor(char key) {
  switch (key) {
    case 'a':
      E.curPosX--;
      break;
    case 'd':
      E.curPosX++;
      break;
    case 'w':
      E.curPosY--;
      break;
    case 's':
      E.curPosY++;
      break;
  }
}

void editorProcessKeypress (){
  char input = editorReadKey();

  switch(input){
      case CTRL_KEY('q'):
          write(STDOUT_FILENO, "\x1b[2J", 4);
          write(STDOUT_FILENO, "\x1b[H", 3);
          exit(0);
          break;
      case 'w':
      case 's':
      case 'a':
      case 'd':
          editorMoveCursor(input);
          break;
  }
}