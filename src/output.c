#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "terminal.h"
#include "buffer.h"

#define ABUF_INIT {NULL, 0}

struct editorConfig E;

void editorDrawRows(struct appendBuffer *abuf) {
  int tildes;
  for (tildes = 0; tildes < E.screenRows; tildes++) {
     abufAppend(abuf, "~", 1);
     if (tildes < E.screenRows - 1) {
        abufAppend( abuf, "\r\n", 2);
    }
  }
}

void editorRefreshScreen() {
  struct appendBuffer abuf = ABUF_INIT;
  // hiding the cursor to avoid flicker when screen refreshes
  abufAppend(&abuf, "\x1b[?25l", 6);
  // clearing the entire screen 
  abufAppend(&abuf, "\x1b[2J", 4);
  // Repositioning the cursor to top-left corner
  abufAppend(&abuf, "\x1b[H", 3);

  editorDrawRows(&abuf);
  // Repositioning the cursor to top-left corner after generating tildes
  abufAppend(&abuf, "\x1b[H", 3);
  // Displaying the cursor back
  abufAppend(&abuf, "\x1b[?25h", 6);

  // Writing buffer to screen
  write(STDOUT_FILENO, abuf.buf, abuf.len);
  abufFree(&abuf);
}