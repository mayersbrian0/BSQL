#include "compiler.h"

Table* init_table() {
    Table* table = malloc(sizeof(Table)); //create space
    table->num_rows = 0;
    for (int i = 0; i < MAX_PAGES_PER_TABLE; i++) {
        table->pages[i] = NULL;
    }
    
    return table;
}

void free_table(Table *table) {
    int i = 0;
    while (table->pages[i]) { //while not NULL
        free(table->pages[i]);
        i++;
    }
    free(table);
}

void serialize_row(Row * source, void * destination) {
    memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
    memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
    memcpy(destination + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

void deserialize_row(void * source, Row* destination) {
    memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
    memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);   
}

//this will create a page or return the page that we are on
void* pager(Table* table, uint32_t row_num) {
    uint32_t page_num = row_num / ROWS_PER_PAGE; //get page # we are on
    void* page = table->pages[page_num]; //get pointer ot mem
    if (page == NULL) page = table->pages[page_num] = malloc(PAGE_SIZE); //allocate memory to the page

    uint32_t row_offset = row_num % ROWS_PER_PAGE; //offset of current row
    uint32_t byte_offset = row_offset * ROW_SIZE; 
    return page + byte_offset; //this is the address to the page 
}



//TODO: make input string lowercase before comparing
StatementResult check_statement(ArgBuffer* arg_inputs, Statement* statement) {
    //add a to_lower function

    if (strncmp(arg_inputs->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        int args = sscanf(arg_inputs->buffer, "insert %d %s %s", &(statement->insert_row.id), statement->insert_row.username, statement->insert_row.email);
        if (args != 3) {
            return STATEMENT_SYNTAX_ERROR;
        }
        return STATEMENT_VALID;
    }

    else if (strncmp(arg_inputs->buffer, "select", 6) == 0) {
        statement->type = STATEMENT_SELECT;
        return STATEMENT_VALID;
    }

    return STATEMENT_INVALID;
}

void print_row(Row * row) {
    
}

ExecuteResult execute_insert(Statement* statement, Table* table) {
    if (table->num_rows >= MAX_PAGES_PER_TABLE) return EXECUTE_TABLE_FULL; //insert if no more pages can be allocated

    Row* new_row = &(statement->insert_row);

    serialize_row(new_row, pager(table, table->num_rows)); //create row in table
    table->num_rows += 1;

    return EXECUTE_SUCC;
}

ExecuteResult execute_select(Statement* statement, Table* table) {
    Row row;
    for (int i = 0; i < table->num_rows; i++) {
        deserialize_row(pager(table,i), &row);
        print_row(&row);
    }
}

ExecuteResult execute_statement(Statement* statement, Table* table) {
    switch (statement->type) {
        case (STATEMENT_INSERT):
            return execute_insert(statement, table);
        case(STATEMENT_SELECT):
            return execute_insert(statement, table);
        default:
            printf("Error resolving statement\n");
    }
}

MetaResult meta_command(ArgBuffer* arg_inputs) {
    if (strcmp(arg_inputs->buffer, "-exit") == 0) {
        free_arg_buffer(arg_inputs);
        exit(EXIT_SUCCESS);
    }

    else if (strcmp(arg_inputs->buffer, "-help") == 0) {
        printf("In progress, come back soon for more\n");
        return META_VALID;
    }

    return META_INVALID;  
}