#include <stdio.h>
#include <string.h>
#include "parser.h"

void say_hello() {
    // printf("Hello\n");
}

STATE_MACHINE_RETURN_VALUE_t at_command_parse(uint8_t current_character){
    static uint8_t state = 0;
    STATE_ADDRESS = &state;

    switch (state) {
        case 0:
            // printf("state --> %u\n", state);
            if(current_character == 0x0d){
                state = 1;
                // printf("next state --> %u\n", state);
            } else {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 1:
            // printf("state --> %u\n", state);
            if(current_character == 0x0a){
                state = 2;
                // printf("next state --> %u\n", state);
            } else {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 2:
            // printf("state --> %u\n", state);
            if(current_character == 'O'){
                state = 3;
                // printf("next state --> %u\n", state);
            } else if(current_character == 'E'){
                state = 6;
                // printf("next state --> %u\n", state);
            } else if(current_character == '+'){
                state = 12;
                // printf("next state --> %u\n", state);
                write_at_command_data(current_character,0);
            } else {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 3:
            // printf("state --> %u\n", state);
            if(current_character == 'K'){
                state = 4;
                // printf("next state --> %u\n", state);
            } else {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 4:
            // printf("state --> %u\n", state);
            if(current_character == 0x0d){
                state = 5;
                // printf("next state --> %u\n", state);
            } else {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 5:
            // printf("state --> %u\n", state);
            if(current_character == 0x0a){
                DATA_MATRIX.ok = 1;
                return STATE_MACHINE_READY_OK;
            } else {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 6:
            // printf("state --> %u\n", state);
            if(current_character == 'R'){
                state = 7;
                // printf("next state --> %u\n", state);
            } else {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 7:
            // printf("state --> %u\n", state);
            if(current_character == 'R'){
                state = 8;
                // printf("next state --> %u\n", state);
            } else {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 8:
            // printf("state --> %u\n", state);
            if(current_character == 'O'){
                state = 9;
                // printf("next state --> %u\n", state);
            } else {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 9:
            // printf("state --> %u\n", state);
            if(current_character == 'R'){
                state = 10;
                // printf("next state --> %u\n", state);
            } else {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 10:
            // printf("state --> %u\n", state);
            if(current_character == 0x0d){
                state = 11;
                // printf("next state --> %u\n", state);
            } else {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 11:
            // printf("state --> %u\n", state);
            if(current_character == 0x0a){
                DATA_MATRIX.ok = 0;
                return STATE_MACHINE_READY_OK;
            } else {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 12:
            // printf("state --> %u\n", state);
            if(current_character > 0x1f && current_character < 0x7f && current_character != '+'){
                state = 13;
                // printf("next state --> %u\n", state);
                write_at_command_data(current_character,0);
            } else {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 13:
            // printf("state --> %u\n", state);
            if(current_character > 0x1f && current_character < 0x7f ){
                state = 13;
                // printf("next state --> %u\n", state);
                write_at_command_data(current_character,0);
            } else if (current_character == 0x0d) {
                state = 14;
                // printf("next state --> %u\n", state);
                write_at_command_data(current_character,0);
            } else {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 14:
            // printf("state --> %u\n", state);
            if(current_character == 0x0a){
                state = 15;
                // printf("next state --> %u\n", state);
                write_at_command_data(current_character,1);
            } else {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 15:
            // printf("state --> %u\n", state);
            if(current_character == 0x0d){
                state = 16;
                // printf("next state --> %u\n", state);
            } else if (current_character == '+') {
                state = 12;
                // printf("next state --> %u\n", state);
                write_at_command_data(current_character,0);
            }else {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 16:
            // printf("state --> %u\n", state);
            if(current_character == 0x0a){
                state = 17;
                // printf("next state --> %u\n", state);
            }else {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 17:
            // printf("state --> %u\n", state);
            if(current_character == 'O'){
                state = 3;
                // printf("next state --> %u\n", state);
            } else if (current_character == 'E') {
                state = 6;
                // printf("next state --> %u\n", state);
            }else {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
    }


    return STATE_MACHINE_NOT_READY;
}


AT_COMMAND_t get_current_at_command() {
    if (DATA_MATRIX.ok == 0)
        return AT_C_ERROR;
    // https://en.cppreference.com/w/c/language/string_literal
    // if(memcmp(DATA_MATRIX.data[0],u8"+COPN:",6) == 0)
    if(memcmp(DATA_MATRIX.data[0],"+COPN:",6) == 0)
        return AT_C_COPN;
    if(memcmp(DATA_MATRIX.data[0],"+CSQ:",5) == 0)
        return AT_C_CSQ;

    return AT_C_UNKNOWN;
};


uint8_t handle_at_command(AT_COMMAND_t at_command) {
    return 0;
}


void rest_at_command_data() {
    DATA_MATRIX.ok = 0;
    memset(DATA_MATRIX.data, 0, sizeof(DATA_MATRIX.data));
    DATA_MATRIX.line_count = 0;
    DATA_MATRIX.col_count = 0;
}


// TODO handle line overflow
void write_at_command_data(uint8_t current_character, uint8_t increase_line_count) {

    if (DATA_MATRIX.line_count < AT_COMMAND_MAX_LINES) {
        if (DATA_MATRIX.col_count == AT_COMMAND_MAX_LINE_SIZE-1) {
            DATA_MATRIX.data[DATA_MATRIX.line_count][DATA_MATRIX.col_count]='\0';
        }
        if (DATA_MATRIX.col_count < AT_COMMAND_MAX_LINE_SIZE-1) {
            DATA_MATRIX.data[DATA_MATRIX.line_count][DATA_MATRIX.col_count]=current_character;
            DATA_MATRIX.col_count++;
        }

        if (increase_line_count) {
            DATA_MATRIX.data[DATA_MATRIX.line_count][DATA_MATRIX.col_count]='\0';
            DATA_MATRIX.line_count++;
            DATA_MATRIX.col_count=0;
        }
    }

}

void print_at_command_data() {
    uint32_t line_iter;
    uint32_t col_iter;

    for(line_iter=0; line_iter < DATA_MATRIX.line_count; ++line_iter) {
        col_iter=0;
        // fprintf(stdout,"[%u]:",line_iter);
        while (DATA_MATRIX.data[line_iter][col_iter] != '\0'){
            fprintf(stdout,"%c", DATA_MATRIX.data[line_iter][col_iter]);
            ++col_iter;
        }
    }
}