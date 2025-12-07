#include "wrapper.h"
#include <windows.h>
#include <stdint.h>
#include <string.h>

// External function from COFFLoader.c
extern int RunCOFF(char* functionname, unsigned char* coff_data, uint32_t filesize, 
                   unsigned char* argumentdata, int argumentSize);

// External beacon output functions
extern char* BeaconGetOutputData(int* outsize);

EXPORT int run_bof(const unsigned char* bof_data, size_t bof_len, 
                   const unsigned char* args_data, size_t args_len, 
                   unsigned char** output, size_t* output_len) {
    
    // Validate inputs
    if (output == NULL || output_len == NULL) {
        return -1;
    }
    
    *output = NULL;
    *output_len = 0;
    
    if (bof_data == NULL || bof_len == 0) {
        return -1;
    }
    
    // Execute BOF (default entry point is "go")
    int result = RunCOFF("go", 
                         (unsigned char*)bof_data, 
                         (uint32_t)bof_len,
                         (unsigned char*)args_data, 
                         (int)args_len);
    
    // Capture beacon output
    int out_size = 0;
    char* beacon_output = BeaconGetOutputData(&out_size);
    
    if (beacon_output != NULL && out_size > 0) {
        *output = (unsigned char*)malloc(out_size);
        if (*output != NULL) {
            memcpy(*output, beacon_output, out_size);
            *output_len = out_size;
        }
    }
    
    return result;
}
