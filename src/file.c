/*
   Author : Bibek Koirala
   Description : Code related to file i/o
*/

// macros for getline(). The header files included below use these macros.
#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include <sys/types.h>
#include "terminal.h"

void editorAppendRow(char *s, size_t len) {
  E.row = realloc(E.row, sizeof(editorRow) * (E.numRows + 1));
  int at = E.numRows;

  E.row[at].size = len;
  E.row[at].chars = malloc(len + 1);
  memcpy(E.row[at].chars, s, len);
  E.row[at].chars[len] = '\0';
  E.numRows++;
}

void editorOpen(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp) die("fopen");
  char *line = NULL;
  size_t lineCapacity = 0;
  ssize_t lineLength;

  while ((lineLength = getline(&line, &lineCapacity, fp)) != -1) {
       while (lineLength > 0 && (line[lineLength - 1] == '\n' || line[lineLength - 1] == '\r')){
              lineLength--;
        }
     editorAppendRow(line, lineLength);
  }
  free(line);
  fclose(fp);
}