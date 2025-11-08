#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_flags(int argc, char* argv[], char* pattern_buffer, int* e_flag,
                int* i_flag, int* v_flag, int* c_flag, int* l_flag,
                int* n_flag);
void process_files(int argc, char* argv[], const char* pattern, int e_flag,
                   int i_flag, int v_flag, int c_flag, int l_flag, int n_flag);

#endif