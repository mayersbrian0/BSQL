#ifndef COMPILER_H
#define COMPILER_H

#include "string.h"
#include "stdint.h"
#include "stdio.h"


#ifndef ARG_BUFFER_H
    #include "arg_buffer.h"
    #define ARG_BUFFER_H
#endif


#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
typedef struct {
  uint32_t id;
  char username[COLUMN_USERNAME_SIZE + 1];
  char email[COLUMN_EMAIL_SIZE + 1];
} Row;


// Serialized row in memory
#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

static const uint32_t ID_SIZE = size_of_attribute(Row, id);
static const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
static const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
static const uint32_t ID_OFFSET = 0;
static const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
static const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
static const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;
//

#define PAGE_SIZE 4096 
#define MAX_PAGES_PER_TABLE 100 //limit to how much we allocate
static const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE; //small internal fragmentation
static const uint32_t MAX_ROWS_PER_TABLE = ROWS_PER_PAGE * MAX_PAGES_PER_TABLE;

typedef struct {
    uint32_t num_rows;
    void * pages[MAX_PAGES_PER_TABLE];
} Table;

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

typedef struct {
   StatementType type;
   Row insert_row;  // only used by insert statement
} Statement;

typedef enum {
   EXECUTE_SUCC,
   EXECUTE_TABLE_FULL 
} ExecuteResult;

Table* init_table();

void serialize_row(Row * source, void * destination);

void deserialize_row(void * source, Row* destination);

void free_table();

StatementResult check_statement(ArgBuffer* arg_inputs, Statement* statement);

ExecuteResult execute_statement(Statement* statement, Table* table);

MetaResult meta_command(ArgBuffer* arg_inputs);

void* pager(Table* table, uint32_t row_num);

#endif