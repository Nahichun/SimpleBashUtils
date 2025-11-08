#ifndef S21_CAT_H
#define S21_CAT_H

#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

int is_flag(const char *s);
int is_blank_line(const char *str);
void process_file(const char *flag, FILE *f, const char *filename);
void show_non_printable(unsigned char c);
void handle_b_flag(FILE *f);
void handle_n_flag(FILE *f);
void handle_E_flag(FILE *f);
void handle_e_flag(FILE *f);
void handle_T_flag(FILE *f);
void handle_t_flag(FILE *f);
void handle_s_flag(FILE *f);
void handle_regular(FILE *f);

#endif