#include <stdio.h>
#include "io.h"
#include "util.h"

const char INPUT_FILE_OPEN_MODE[] = "r";
const char OUTPUT_FILE_OPEN_MODE[] = "w";

/**
 * @brief      Open Input and Output files
 *
 *             Given the arguments to the program, this function opens the files
 *             required for the program.
 *
 * @param      in    Pointer to the input file
 * @param      out   Pointer to the output file
 * @param[in]  argc  The argc
 * @param      argv  The argv
 */
void IOFiles_open(FILE **in, FILE **out, int argc, char *argv[]) {
    if(argc != 3) exit_with_code("Wrong format argument", -1);

    char *in_file_name = argv[1], *out_file_name = argv[2];

    *in = fopen(in_file_name, INPUT_FILE_OPEN_MODE);

    if(*in == NULL) exit_with_code("Could not open input file", -1);

    *out = fopen(out_file_name, OUTPUT_FILE_OPEN_MODE);

    if(*out == NULL) exit_with_code("Could not open output file", -1);
}

/**
 * @brief      Close Input and Output files
 *
 * @param      in    Pointer to the input file
 * @param      out   Pointer to the output file
 */
void IOFiles_close(FILE *in, FILE *out) {
    if(fclose(in) != 0) exit_with_code("Could not close input file", -1);
    if(fclose(out) != 0) exit_with_code("Could not close output file", -1);
}