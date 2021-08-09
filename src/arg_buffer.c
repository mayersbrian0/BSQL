#include "arg_buffer.h"

//function returns a default buffer 
ArgBuffer* create_arg_buffer() { 
    ArgBuffer *new_buffer= (ArgBuffer *)malloc(sizeof(ArgBuffer)); //allocate space for ArgBuffer
    new_buffer->buffer_size = 0;
    new_buffer->input_length = 0;
    new_buffer->buffer = NULL;

    return new_buffer;
}

//function that frees the allocated buffer
void free_arg_buffer(ArgBuffer* arg_buffer) {
    free(arg_buffer->buffer); //getline will allocate this so we must clean up here 
    free(arg_buffer);
}


//trims any whitespace trailing whitespace once the user enters the command
//if whitespace is found, decrement the input bytes and set null terminator appropriatly 
void trim_whitespace(ArgBuffer *arg_inputs, int input_bytes) {
    int i = input_bytes -1;
    while (arg_inputs->buffer[i] == ' ' || arg_inputs->buffer[i] == '\n') i -= 1;

    arg_inputs->input_length = i +1;
    arg_inputs->buffer[i+1] = 0; //set null terminator 
}