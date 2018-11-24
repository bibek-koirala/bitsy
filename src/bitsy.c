#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "terminal.h"
#include "input.h"
#include "output.h"

struct editorConfig E;

void initEditor() {
  // Column Position of cursor
  E.curPosX = 0; 
  // Row position of cursor
  E.curPosY = 0;
  
  if (getWindowSize(&E.screenRows, &E.screenCols) == -1) die("getWindowSize");
}


int main () {
  disableCanonicalMode();
  initEditor();

  while (1) {
    editorRefreshScreen();
    editorProcessKeypress();
  };

  return 0;
}

