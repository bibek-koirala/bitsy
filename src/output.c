/*
   Author : Bibek Koirala
   Description : Code related to drawing and displaying editor and user input after processing
*/

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include "terminal.h"
#include "buffer.h"

#define BITSY_VERSION "0.1"
#define ABUF_INIT {NULL, 0}

struct editorConfig E;

void editorScroll() {
  if (E.curPosY< E.rowOffset) {
    E.rowOffset = E.curPosY;
  }
  if (E.curPosY >= E.rowOffset + E.screenRows) {
    E.rowOffset = E.curPosY- E.screenRows + 1;
  }
  if (E.curPosY < E.colOffset) {
    E.colOffset = E.curPosX;
  }
  if (E.curPosX>= E.colOffset + E.screenCols) {
    E.colOffset = E.curPosX- E.screenCols + 1;
  }
}

void editorDrawRows(struct appendBuffer *abuf) {
  int drawRow;
  for (drawRow = 0; drawRow < E.screenRows; drawRow++) {
    int fileRow = drawRow + E.rowOffset;
    if (fileRow >= E.numRows) {
      // Display welcome message at one-third of screen from top
      if (E.numRows == 0 && drawRow == E.screenRows / 3) {
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
    }
    else {
      int len = E.row[fileRow].size - E.colOffset;
      if (len < 0) len = 0;
      if (len > E.screenCols) len = E.screenCols;
      abufAppend(abuf, &E.row[fileRow].chars[E.colOffset], len);
    }
     // Clear a line/row 
     abufAppend(abuf, "\x1b[K", 3);
     if (drawRow < E.screenRows - 1) {
        abufAppend( abuf, "\r\n", 2);
    }
  }
}

void editorRefreshScreen() {
  editorScroll();
  struct appendBuffer abuf = ABUF_INIT;
  // hiding the cursor to avoid flicker when screen refreshes
  abufAppend(&abuf, "\x1b[?25l", 6);
  // Repositioning the cursor to top-left corner
  abufAppend(&abuf, "\x1b[H", 3);

  editorDrawRows(&abuf);
  char buf[32];
  snprintf(buf, sizeof(buf), "\x1b[%d;%dH", (E.curPosY - E.rowOffset) + 1, E.curPosX + 1);
  abufAppend(&abuf, buf, strlen(buf));

  // Displaying the cursor back
  abufAppend(&abuf, "\x1b[?25h", 6);

  // Writing buffer to screen
  write(STDOUT_FILENO, abuf.buf, abuf.len);
  abufFree(&abuf);
}