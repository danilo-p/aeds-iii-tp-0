#include <stdio.h>

#ifndef IO_H
#define IO_H

int IOFiles_open(FILE **in, FILE **out, int argc, char *argv[]);

int IOFiles_close(FILE *in, FILE *out);

#endif