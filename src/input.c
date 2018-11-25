#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "terminal.h"

#define CTRL_KEY(keyFollowingCtrl) (keyFollowingCtrl & 0x1f)

void editorMoveCursor(int key) {
  switch (key) {
    case ARROW_LEFT:
        if (E.curPosX != 0) {
            E.curPosX--;
        }
        break;

    case ARROW_RIGHT:
         if (E.curPosX != E.screenCols -1) {
             E.curPosX++;
         }
         break;

    case ARROW_UP:
        if (E.curPosY != 0){
            E.curPosY--;
        }
        break;

    case ARROW_DOWN:
        if (E.curPosY != E.screenRows -1) {
            E.curPosY++;
        }
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
      
      case HOME_KEY:
          E.curPosX = 0;
          break;
      case END_KEY:
          E.curPosX = E.screenCols - 1;
          break;

      case PAGE_UP:
      case PAGE_DOWN:
         // Need to create code block with curly braces to declare variable inside switch cases
         {
           int times = E.screenRows;
           while (times--)
               editorMoveCursor( (input == PAGE_UP) ? ARROW_UP : ARROW_DOWN);
          }
          break;
      case ARROW_UP:
      case ARROW_DOWN:
      case ARROW_LEFT:
      case ARROW_RIGHT:
          editorMoveCursor(input);
          break;
  }
}