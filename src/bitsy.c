#include <stdio.h>
#include <stdlib.h>
#include "terminal.h"

#define CTRL_KEY(keyFollowingCtrl) (keyFollowingCtrl & 0x1f)


void editorProcessKeypress (){
  char input = editorReadKey();

  switch(input){
      case CTRL_KEY('q'):
          exit(0);
          break;
  }
}

int main () {
  disableCanonicalMode();

  while (1) {
    editorProcessKeypress();
  };

  return 0;
}

