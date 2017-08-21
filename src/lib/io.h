#include <stdio.h>

#ifndef IO_H
#define IO_H

int IOFilesOpen(FILE **in, FILE **out, int argc, char *argv[]);

int IOFilesClose(FILE *in, FILE *out);

#endif