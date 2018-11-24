#ifndef TERMINAL_H
#define TERMINAL_H

enum editorKey {
  ARROW_LEFT = 'a',
  ARROW_RIGHT = 'd',
  ARROW_UP = 'w',
  ARROW_DOWN = 's'
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
char editorReadKey ();
int getCursorPosition(int *rows, int *cols);
int getWindowSize(int *rows, int *cols);
#endif
