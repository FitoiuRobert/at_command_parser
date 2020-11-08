#ifndef _PARSER_
#define _PARSER_

    #include <stdint.h>

    #define AT_COMMAND_MAX_LINES 100
    #define AT_COMMAND_MAX_LINE_SIZE 128

    size_t *STATE_ADDRESS;
    typedef struct {
        uint8_t ok;
        uint8_t data[AT_COMMAND_MAX_LINES][AT_COMMAND_MAX_LINE_SIZE + 1];
        uint32_t line_count;
        uint32_t col_count;
    } AT_COMMAND_DATA;

    AT_COMMAND_DATA DATA_MATRIX;

    typedef enum {
        STATE_MACHINE_READY_OK = 0,
        STATE_MACHINE_NOT_READY = 1,
        STATE_MACHINE_READY_WITH_ERROR = 2
    }STATE_MACHINE_RETURN_VALUE;

    STATE_MACHINE_RETURN_VALUE at_command_parse(uint8_t current_character);

    void write_at_command_data(uint8_t current_character, uint8_t increase_line_count);

    void print_at_command_data();


#endif