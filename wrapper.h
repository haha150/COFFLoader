#ifndef WRAPPER_H
#define WRAPPER_H

#ifdef _WIN64
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <stdlib.h>

EXPORT int run_bof(const unsigned char* bof_data, size_t bof_len, 
                   const unsigned char* args_data, size_t args_len, 
                   unsigned char** output, size_t* output_len);

#endif
