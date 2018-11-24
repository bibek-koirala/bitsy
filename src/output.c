#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "terminal.h"
#include "buffer.h"

#define BITSY_VERSION "0.1"
#define ABUF_INIT {NULL, 0}

struct editorConfig E;

void editorDrawRows(struct appendBuffer *abuf) {
  int tildes;
  for (tildes = 0; tildes < E.screenRows; tildes++) {
    // Display welcome message at one-third of screen from top
     if (tildes == E.screenRows / 3) {
        char welcome[80];
        int welcomeLen = snprintf(welcome, sizeof(welcome),
          "bitsy editor -- version %s", BITSY_VERSION);
        if (welcomeLen > E.screenCols) welcomeLen = E.screenCols;
        // Center the welcome message on screen
        int padding = (E.screenCols - welcomeLen) / 2;
        if (padding) {
           abufAppend(abuf, "~", 1);
           padding--;
        }
        while (padding--) abufAppend(abuf, " ", 1);
        abufAppend(abuf, welcome, welcomeLen);
     }

     else {
        abufAppend(abuf, "~", 1);
     }
     // Clear a line/row 
     abufAppend(abuf, "\x1b[K", 3);
     if (tildes < E.screenRows - 1) {
        abufAppend( abuf, "\r\n", 2);
    }
  }
}

void editorRefreshScreen() {
  struct appendBuffer abuf = ABUF_INIT;
  // hiding the cursor to avoid flicker when screen refreshes
  abufAppend(&abuf, "\x1b[?25l", 6);
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