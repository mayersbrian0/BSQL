#ifndef ARG_BUFFER_H
#define ARG_BUFFER_H

#include "stdlib.h" //TO-DO: check if the preprocessor will bring in stdlib twice
#include "sys/types.h"

typedef struct {
    char* buffer;
    size_t buffer_size; //return a value in bytes
    ssize_t input_length; //return a value in bytes or 
} ArgBuffer;

ArgBuffer* create_arg_buffer();

void free_arg_buffer(ArgBuffer* arg_buffer);

void trim_whitespace(ArgBuffer* arg_buffer, int input_bytes);

#endif 