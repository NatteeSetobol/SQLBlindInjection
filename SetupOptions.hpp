#ifndef __SETUP_OPTIONS__
#define __SETUP_OPTIONS__

#include "../lpop/cl_options.hpp"

Options *SetupOptions(int argc,char* args[]);

void SetupCleanup(Options *options);
void CreateOptions(Options *options);
void DeleteOptions(Options *options);
#endif
