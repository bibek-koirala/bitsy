/*
   Author : Bibek Koirala
   Description : Entry point  of the bitsy editor.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "terminal.h"
#include "input.h"
#include "output.h"
#include "file.h"

struct editorConfig E;

void initEditor() {
  // Column Position of cursor
  E.curPosX = 0; 
  // Row position of cursor
  E.curPosY = 0;

  E.numRows = 0;
  
  if (getWindowSize(&E.screenRows, &E.screenCols) == -1) die("getWindowSize");
}


int main (int argc, char *argv[]) {
  disableCanonicalMode();
  initEditor();
  if (argc >= 2){
     editorOpen(argv[1]);
  }

  while (1) {
    editorRefreshScreen();
    editorProcessKeypress();
  };

  return 0;
}

