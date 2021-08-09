#ifndef COMPILER_H
#define COMPILER_H

#include "string.h"
#include "stdint.h"
#include "stdio.h"

#ifndef ARG_BUFFER_H
    #include "arg_buffer.h"
    #define ARG_BUFFER_H
#endif

typedef enum {
    META_VALID,
    META_INVALID
} MetaResult;

typedef enum {
    STATEMENT_VALID,
    STATEMENT_SYNTAX_ERROR,
    STATEMENT_INVALID
} StatementResult;

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;

typedef struct {
   StatementType type;
   Row row_to_insert;  // only used by insert statement
} Statement;

typedef struct {
    StatementType type;
} Statement;

StatementResult check_statement(ArgBuffer* arg_inputs, Statement* statement);

void execute_statement(Statement* statement);

MetaResult meta_command(ArgBuffer* arg_inputs);

#endif