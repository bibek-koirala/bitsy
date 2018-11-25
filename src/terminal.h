#ifndef TERMINAL_H
#define TERMINAL_H

enum editorKey {
  // giving large enough int value that is out of range of char(individual keypresses).
  ARROW_LEFT = 1000,
  ARROW_RIGHT ,
  ARROW_UP ,
  ARROW_DOWN,
  PAGE_UP,
  PAGE_DOWN
};

struct editorConfig {
  int curPosX, curPosY;
  int screenRows;
  int screenCols;
  struct termios origTermInfo;
};

extern struct editorConfig E;

void die (const char * errorMsg);
void enableCanonicalMode ();
void disableCanonicalMode ();
int editorReadKey ();
int getCursorPosition(int *rows, int *cols);
int getWindowSize(int *rows, int *cols);
#endif
