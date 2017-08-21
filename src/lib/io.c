#include <stdio.h>
#include "io.h"

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
 *
 * @return     Returns 1 in case of success on reading io files. Returns -1 if
 *             the arguments of the program dont follow the expected format.
 *             Returns -2 if an error ocurred on reading the input file. Returns
 *             -3 if an error ocurred on reading the output file.
 */
int IOFilesOpen(FILE **in, FILE **out, int argc, char *argv[]) {
    // Check if the input has the expected format
    if(argc != 3) return -1;

    char *in_file_name = argv[1], *out_file_name = argv[2];

    *in = fopen(in_file_name, INPUT_FILE_OPEN_MODE);

    if(*in == NULL) return -2;

    *out = fopen(out_file_name, OUTPUT_FILE_OPEN_MODE);

    if(*out == NULL) return -3;

    return 1;
}

/**
 * @brief      Close Input and Output files
 *
 * @param      in    Pointer to the input file
 * @param      out   Pointer to the output file
 *
 * @return     Returns 1 in case of success on closing io files. Returns -1 if an error ocurred while closing the input file. Returns -2 if an error ocurred while closing the output file.
 */
int IOFilesClose(FILE *in, FILE *out) {
    if(fclose(in) != 0) return -1;
    if(fclose(out) != 0) return -2;

    return 1;
}