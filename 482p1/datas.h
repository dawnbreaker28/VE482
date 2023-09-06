#ifndef DATA_H
#define DATA_H

#include <stdbool.h>

#define BUFFER_SIZE 32
#define TOKEN_SIZE 512

typedef struct token {
  size_t argc;
  char *argv[BUFFER_SIZE];
} token_t;

typedef enum ERRORS{
  ERROR_NON_EXIST_PROGRAM,
  ERROR_NON_EXIST_FILE,
  ERROR_OPEN,
  ERROR_DUP_INPUT,
  ERROR_DUP_OUTPUT,
  ERROR_SYNTAX,
  ERROR_MISSING_PROGRAM,
  ERROR_CD
} errors_t;

typedef struct cmd{
    size_t numbers;
    token_t tokens[TOKEN_SIZE];
    char input_file[32];
    char output_file[32];
    bool input;
    bool output;
    bool append;
}cmd_t;

typedef struct parser {
  int buffer_len;
  bool is_input_file;
  bool is_output_file;
  bool is_pipe;
  int output_mode; // 0 for no, 1 for overwrite, 2 for append
  char buffer[BUFFER_SIZE]; //could be more
} parser_t;

extern cmd_t cmd;

#endif
