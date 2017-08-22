#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void exit_with_code(char *message, int code) {
    printf("%s\n", message);
    exit(code);
}