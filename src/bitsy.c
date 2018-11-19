#include <stdio.h>
#include <stdlib.h>
#include "terminal.h"
#include "input.h"
#include "output.h"

int main () {
  disableCanonicalMode();

  while (1) {
    editorRefreshScreen();
    editorProcessKeypress();
  };

  return 0;
}

