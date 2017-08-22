#include <stdio.h>

#ifndef IO_H
#define IO_H

void IOFiles_open(FILE **in, FILE **out, int argc, char *argv[]);

void IOFiles_close(FILE *in, FILE *out);

#endif