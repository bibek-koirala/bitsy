#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "terminal.h"

struct editorConfig E;

void editorDrawRows() {
  int tildes;
  for (tildes = 0; tildes < E.screenRows; tildes++) {
     write(STDOUT_FILENO, "~", 1);
     if (tildes < E.screenRows - 1) {
      write(STDOUT_FILENO, "\r\n", 2);
    }
  }
}

void editorRefreshScreen() {
  // clearing the entire screen 
  write(STDOUT_FILENO, "\x1b[2J", 4);
  // Repositioning the cursor to top-left corner
  write(STDOUT_FILENO, "\x1b[H", 3);

  editorDrawRows();
  write(STDOUT_FILENO, "\x1b[H", 3);
}