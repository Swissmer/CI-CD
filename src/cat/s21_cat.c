#include "s21_cat.h"

int main(int argc, char **argv) {
  int opt;
  struct flags flags_s = {0};

  while ((opt = getopt_long(argc, argv, "+benstvTE", long_options, NULL)) !=
         -1) {
    switch_in(&opt, &flags_s);
  }

  int index = optind;
  FILE *f;

  while (index < argc) {
    f = fopen(argv[index], "rb");
    if (f == NULL) {
      fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
              argv[index]);
      exit(1);
    }
    main_func(f, &flags_s);
    fclose(f);
    index++;
  }
}

void switch_in(int *opt, struct flags *flag_s) {
  switch (*opt) {
    case 'b':
      (*flag_s).b = 1;
      break;
    case 'e':
      (*flag_s).e = 1;
      (*flag_s).v = 1;
      break;
    case 'n':
      (*flag_s).n = 1;
      break;
    case 's':
      (*flag_s).s = 1;
      break;
    case 't':
      (*flag_s).t = 1;
      (*flag_s).v = 1;
      break;
    case 'v':
      (*flag_s).v = 1;
      break;
    case 'T':
      (*flag_s).T = 1;
      break;
    case 'E':
      (*flag_s).E = 1;
      break;
    default:
      printf("usage: cat [-bens] [file ...]\n");
      exit(1);
  }
}

void main_func(FILE *f, struct flags *flags_s) {
  int pred_Line = 0;
  int number_Line = 1;
  int simbol;
  int last_simbol = '\n';

  while ((simbol = fgetc(f == NULL ? stdin : f)) != EOF) {
    if (flags_s->s) {
      int line = (last_simbol == '\n' && simbol == '\n') ? 1 : 0;  //
      if (line && pred_Line) continue;
      pred_Line = line;
    }

    if (flags_s->b) {
      edit_b(simbol, last_simbol, &number_Line);
    }

    if (flags_s->n && !flags_s->b) {
      edit_n(last_simbol, &number_Line);
    }

    if (flags_s->e) {
      edit_e(simbol);
    }

    if (flags_s->t) {
      edit_t(&simbol);
    }

    if (flags_s->v) {
      edit_v(&simbol);
    }

    if (flags_s->T) {
      edit_t(&simbol);
    }

    if (flags_s->E) {
      edit_e(simbol);
    }

    printf("%c", simbol);
    last_simbol = simbol;
  }
}

void edit_b(int simbol, int last_simbol, int *count) {
  if (last_simbol == '\n' && simbol != '\n') {
    printf("%6d\t", (*count)++);
  }
}

void edit_n(char last_simbol, int *count) {
  if (last_simbol == '\n') {
    printf("%6d\t", (*count)++);
  }
}

void edit_e(int simbol) {
  if (simbol == '\n') printf("$");
}

void edit_t(int *simbol) {
  if (*simbol == '\t') {
    printf("^");
    *simbol = 'I';
  }
}

void edit_v(int *simbol) {
  if (*simbol != '\n') {
    if (*simbol < 32 && *simbol != '\n' && *simbol != '\t') {
      printf("^");
      *simbol += 64;
    } else if (*simbol > 127 && *simbol < 160) {
      printf("M-^");
      *simbol -= 64;
    } else if (*simbol == 127) {
      printf("^");
      *simbol -= 64;
    }
  }
}