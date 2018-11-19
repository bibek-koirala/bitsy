#include <stdlib.h>
#include <unistd.h>
#include "terminal.h"

#define CTRL_KEY(keyFollowingCtrl) (keyFollowingCtrl & 0x1f)

void editorProcessKeypress (){
  char input = editorReadKey();

  switch(input){
      case CTRL_KEY('q'):
          write(STDOUT_FILENO, "\x1b[2J", 4);
          write(STDOUT_FILENO, "\x1b[H", 3);
          exit(0);
          break;
  }
}