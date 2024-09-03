#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flags {
  int b, e, v, n, s, t, T, E;
};

const struct option long_options[] = {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
    {NULL, 0, NULL, 0}};

void switch_in(int *opt, struct flags *flags_s);
void main_func(FILE *f, struct flags *flags_s);
void edit_b(int simbol, int last_simbol, int *count);
void edit_n(char last_simbol, int *count);
void edit_e(int simbol);
void edit_t(int *simbol);
void edit_v(int *simbol);