#ifndef _PARSER_
#define _PARSER_

    #include <stdint.h>

    #define AT_COMMAND_MAX_LINES 100
    #define AT_COMMAND_MAX_LINE_SIZE 128

    uint8_t *STATE_ADDRESS;

    typedef struct {
        uint8_t ok;
        uint8_t data[AT_COMMAND_MAX_LINES][AT_COMMAND_MAX_LINE_SIZE + 1];
        uint32_t line_count;
        uint32_t col_count;
    } AT_COMMAND_DATA_t;

    AT_COMMAND_DATA_t DATA_MATRIX;

    typedef enum {
        STATE_MACHINE_READY_OK = 0,
        STATE_MACHINE_NOT_READY = 1,
        STATE_MACHINE_READY_WITH_ERROR = 2
    } STATE_MACHINE_RETURN_VALUE_t;

    STATE_MACHINE_RETURN_VALUE_t at_command_parse(uint8_t current_character);

    typedef enum {
        AT_C_UNKNOWN = 0,
        AT_C_ERROR = 1,
        AT_C_COPN = 2,
        AT_C_CSQ = 3
    } AT_COMMAND_t;

    AT_COMMAND_t get_current_at_command();

    uint8_t handle_at_command(AT_COMMAND_t at_command);

    void rest_at_command_data();

    void write_at_command_data(uint8_t current_character, uint8_t increase_line_count);

    void print_at_command_data();


#endif