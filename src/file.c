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

void editorOpen(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp) die("fopen");
  char *line = NULL;
  size_t lineCapacity = 0;
  ssize_t lineLength;
  lineLength = getline(&line, &lineCapacity, fp);
  if (lineLength != -1) {
      while (lineLength > 0 && (line[lineLength - 1] == '\n' || line[lineLength - 1] == '\r')){
         lineLength--;
      }
      E.row.size = lineLength;
      E.row.chars = malloc(lineLength + 1);
      memcpy(E.row.chars, line, lineLength);
      E.row.chars[lineLength] = '\0';
      E.numRows = 1;
  }
  free(line);
  fclose(fp);
}