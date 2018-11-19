#ifndef TERMINAL_H
#define TERMINAL_H

struct editorConfig {
  int screenRows;
  int screenCols;
  struct termios origTermInfo;
};

extern struct editorConfig E;

void die (const char * errorMsg);
void enableCanonicalMode ();
void disableCanonicalMode ();
char editorReadKey ();
int getWindowSize(int *rows, int *cols);
#endif
