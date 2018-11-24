#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "terminal.h"

#define CTRL_KEY(keyFollowingCtrl) (keyFollowingCtrl & 0x1f)

void editorMoveCursor(int key) {
  switch (key) {
    case ARROW_LEFT:
      E.curPosX--;
      break;
    case ARROW_RIGHT:
      E.curPosX++;
      break;
    case ARROW_UP:
      E.curPosY--;
      break;
    case ARROW_DOWN:
      E.curPosY++;
      break;
  }
}

void editorProcessKeypress (){
  int input = editorReadKey();

  switch(input){
      case CTRL_KEY('q'):
          write(STDOUT_FILENO, "\x1b[2J", 4);
          write(STDOUT_FILENO, "\x1b[H", 3);
          exit(0);
          break;
      case ARROW_UP:
      case ARROW_DOWN:
      case ARROW_LEFT:
      case ARROW_RIGHT:
          editorMoveCursor(input);
          break;
  }
}