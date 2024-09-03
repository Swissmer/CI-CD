#include "s21_grep.h"

int main(int argc, char** argv) {
  flags flags_s = {0};
  stack* patterns = createStack();
  if (argc != 1) switch_in(&flags_s, patterns, argc, argv);
  int index_file = argc - optind;
  if (argc == 1) print_error();
  if (argc == 2) {
    if (flags_s.flag_count == 0) flags_s.stuck = 1;
    if (flags_s.flag_count != 0) print_error();
  } else if (argc == 3) {
    if (argc > flags_s.flag_count + 1) {
      if (flags_s.flag_count != 0) flags_s.stuck = 1;
      if (flags_s.flag_count == 0) flags_s.stuck = 0;
    } else
      print_error();
  }
  while (optind < argc) {
    main_func(&flags_s, patterns, index_file, argv);
    optind++;
  }
  deleteStack(patterns);
}

void main_func(flags* flags_s, stack* pat, int index, char** argv) {
  char* buf = calloc(SIZE, sizeof(char*));
  int status = 0;
  regex_t reg;
  regmatch_t pmatch[1] = {0};
  int line_add = 1;

  FILE* f = NULL;
  if ((f = fopen(argv[optind], "r")) != NULL) {
    int count = 1, digit = 0;
    while (fgets(buf, SIZE, (flags_s->stuck ? stdin : f))) {
      while (pat->top != 0) {
        char* pattern = pop(pat);
        if (flags_s->i)
          regcomp(&reg, pattern, REG_ICASE);
        else
          regcomp(&reg, pattern, REG_EXTENDED);
        status = regexec(&reg, buf, 1, pmatch, 0);
        if (status == 0) {
          regfree(&reg);
          break;
        }
        regfree(&reg);
      }
      changeSize(pat);
      if (flags_s->v) {
        flags_s->o = 0;
        if (status == 1)
          status = 0;
        else
          status = 1;
      }
      if (status != REG_NOMATCH) {
        if (!flags_s->c && !flags_s->l) {
          if (!flags_s->h && index > 1) printf("%s:", argv[optind]);
          if (flags_s->n) printf("%d:", count);
          if (flags_s->o && !flags_s->v) {
            line_add = 0;
            char* ptr = buf;
            pat->top = 0;
            while (pat->top != pat->size) {
              char* pattern = pop_o(pat);
              if (flags_s->i)
                regcomp(&reg, pattern, REG_ICASE);
              else
                regcomp(&reg, pattern, REG_EXTENDED);
              status = regexec(&reg, ptr, 1, pmatch, 0);
              while (!status && pmatch[0].rm_eo - pmatch[0].rm_so) {
                printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
                       ptr + pmatch[0].rm_so);
                ptr += pmatch[0].rm_eo;
                status = regexec(&reg, ptr, 1, pmatch, 0);
              }
              regfree(&reg);
            }
          }
          if (!flags_s->o) printf("%s", buf);
          if (buf[strlen(buf) - 1] != '\n' && line_add) printf("\n");
        }
        digit++;
      }
      count++;
    }
    if (flags_s->c) {
      if (!flags_s->h && index > 1) printf("%s:", argv[optind]);
      if (flags_s->l && digit)
        printf("1\n");
      else
        printf("%d\n", digit);
    }
    if (flags_s->l && digit) printf("%s\n", argv[optind]);
    fclose(f);
  } else if (!flags_s->s) {
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", argv[optind]);
  }
  free(buf);
}

void switch_in(flags* flags_s, stack* pat, int argc, char** argv) {
  int opt = 0;
  const char* opt_s = "e:ivclnhsf:o";
  while ((opt = getopt_long(argc, argv, opt_s, NULL, NULL)) != -1) {
    switch (opt) {
      case 'e':
        flags_s->e = 1;
        flags_s->flag_count++;
        push(pat, optarg);
        break;
      case 'i':
        flags_s->i = 1;
        flags_s->flag_count++;
        break;
      case 'v':
        flags_s->v = 1;
        flags_s->flag_count++;
        break;
      case 'c':
        flags_s->c = 1;
        flags_s->flag_count++;
        break;
      case 'l':
        flags_s->l = 1;
        flags_s->flag_count++;
        break;
      case 'n':
        flags_s->n = 1;
        flags_s->flag_count++;
        break;
      case 'h':
        flags_s->h = 1;
        flags_s->flag_count++;
        break;
      case 's':
        flags_s->s = 1;
        flags_s->flag_count++;
        break;
      case 'f':
        flags_s->f = 1;
        flags_s->flag_count++;
        flag_f(pat, argv);
        break;
      case 'o':
        flags_s->o = 1;
        flags_s->flag_count++;
        break;
      case '?':
        fprintf(stderr,
                "usage: ./s21_grep [-chilnosv][-e pattern][-f file][pattern] "
                "[file ...]\n");
        flags_s->stuck = 1;
        break;
    }
  }

  if (!flags_s->e && !flags_s->f && !flags_s->stuck) push(pat, argv[optind++]);
}

void flag_f(stack* pat, char** argv) {
  FILE* f_p = NULL;
  char* bufer = calloc(SIZE, sizeof(char*));
  if ((f_p = fopen(optarg, "r"))) {
    while (fgets(bufer, SIZE, f_p)) {
      if (strlen(bufer) == 1) {
        push_f(pat, bufer);
        continue;
      }
      if (bufer[strlen(bufer) - 1] == '\n') bufer[strlen(bufer) - 1] = 0;
      char* istr = strtok(bufer, " ");
      while (istr != NULL) {
        push_f(pat, istr);
        istr = strtok(NULL, " ");
      }
    }
    changeSize(pat);
    fclose(f_p);
  } else
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", argv[optind]);
  free(bufer);
}

void print_error() {
  printf(
      "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
      "[-C[num]]\n"
      "\t[-e pattern] [-f file] [--binary-files=value] [--color=when]\n"
      "\t[--context[=num]] [--directories=action] [--label] "
      "[--line-buffered]\n"
      "\t[--null] [pattern] [file ...]");
}