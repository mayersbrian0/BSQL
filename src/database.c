#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
//local headers 
#include "arg_buffer.h"
#include "compiler.h"

#define INPUT_ERROR { printf("Error Reading Command\n"); exit(EXIT_FAILURE);} //error reading user input
#define VERSION "0.1" //is it possible to create enviornment variable of version # set using git and update it that way?

//function that prints the start of the program
void print_start() {
    printf("BSQL shell version %s\n Type -help for help\n Type -exit to exit\n\n", VERSION); 
}

void general_print() {
    printf(">> ");
}

/* For Testing hard coded table FORMAT: insert id username email

*/


int main(int argc, char* argv[]) {
    ArgBuffer* arg_inputs = create_arg_buffer(); //used to hold the values the user inputs
    print_start();

    while(1) { 
        general_print();
        //note since arg_inputs->buffer is NULL, getline will allocate this form the buffer
        ssize_t input_bytes = getline(&(arg_inputs->buffer), &(arg_inputs->buffer_size), stdin); //read lines of stdin
        if (input_bytes == -1) INPUT_ERROR;
        trim_whitespace(arg_inputs, input_bytes); 

        //handle meta commands
        if (arg_inputs->buffer[0] == '-') { 
            switch (meta_command(arg_inputs)) {
                case (META_VALID):
                    break;
                default: 
                   printf("Invalid Command: %s\n", arg_inputs->buffer); 
            }
        }

        else {
            Statement statement;
            switch (check_statement(arg_inputs, &statement)) {
                case (STATEMENT_VALID):
                    execute_statement(&statement);
                    break;
                case (STATEMENT_INVALID):
                    printf("Unrecognized statement at start of %s\n", arg_inputs->buffer);
            }
        }

    }  
}

