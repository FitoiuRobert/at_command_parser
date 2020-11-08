#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "parser.h"

int main(int argc, char *argv[]) {
    uint8_t c;
    FILE *fp=NULL;

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
        if((DATA_MATRIX.ok = at_command_parse(c)) == STATE_MACHINE_READY_WITH_ERROR)
            break;
    }

    if (fclose(fp) != 0) {
        fprintf(stderr, "error: Failed to close the file \"%s\"\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if(DATA_MATRIX.ok == STATE_MACHINE_READY_OK) {
        print_at_command_data();
        exit(EXIT_SUCCESS);
    } else {
        fprintf(stderr, "%lu\n", *STATE_ADDRESS);
    }

    exit(EXIT_FAILURE);
}