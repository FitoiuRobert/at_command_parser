#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "parser.h"

int main(int argc, char *argv[]) {
    uint8_t c;
    FILE *fp=NULL;
    STATE_MACHINE_RETURN_VALUE ret;


    if(argc != 2) {
        fprintf(stderr, "error: Incorrect number of parameters, expected 1, got %d\n", argc-1);
        fprintf(stderr, "usage: ./at_command_parser <test_file>\n");
    }

    fp = fopen(argv[1], "rb");

    if (fp == NULL) {
        fprintf(stderr, "error: Failed to open the file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (fread(&c, sizeof(uint8_t), 1, fp) > 0) {
        if((ret = at_command_parse(c)) == STATE_MACHINE_READY_WITH_ERROR)
            break;\
        // not "AT_COMMAND_MAX_LINES -1" because line_count is increased at the end
        // e.g. when DATA_MATRIX.line_count is 99 it writes on the 99'th line
        // and then when it reaches to end will set line_count to 100
        if(DATA_MATRIX.line_count == AT_COMMAND_MAX_LINES) {
            print_at_command_data();
            DATA_MATRIX.line_count=0;
            DATA_MATRIX.col_count=0;
        }
    }

    if(DATA_MATRIX.line_count < AT_COMMAND_MAX_LINES-1) {
        print_at_command_data();
    }

    if (fclose(fp) != 0) {
        fprintf(stderr, "error: Failed to close the file \"%s\"\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if(ret == STATE_MACHINE_READY_OK) {
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_FAILURE);
}