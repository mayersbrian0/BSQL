#include "compiler.h"

//TODO: make input string lowercase before comparing
StatementResult check_statement(ArgBuffer* arg_inputs, Statement* statement) {
    //add a to_lower function

    if (strncmp(arg_inputs->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        int args = sscanf(arg_inputs->buffer, "insert %d %s %s", &(statement->row_to_insert.id), statement->row_to_insert.username, statement->row_to_insert.email);
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

void execute_statement(Statement* statement) {
    switch (statement->type) {
        case (STATEMENT_INSERT):
            printf("In insert\n");
            break;
        case(STATEMENT_SELECT):
            printf("In select\n");
            break;

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