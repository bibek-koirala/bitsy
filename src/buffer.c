#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "buffer.h"


void abufAppend(struct appendBuffer *abuf, const char *s, int len) {
  char *new = realloc(abuf->buf, abuf->len + len);
  if (new == NULL) return;
  memcpy(&new[abuf->len], s, len);
  abuf->buf = new;
  abuf->len += len;
}

void abufFree(struct appendBuffer *abuf) {
  free(abuf->buf);
}