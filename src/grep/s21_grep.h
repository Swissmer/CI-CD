#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

typedef struct flags {
  int help,
      i,  // Игнорит регистр
      v,  // ивертирует поиск
      c,  // выводит только количество совпадающих стрко
      l,  // вывод только совпадающие файлы
      n,  // Выводит номер строки, где найдёт
      h,  // выводит совпадающие строки, не приписывая название файла
      f,  // получает регулярки из файла
      s,  // подвляет ошибки
      e,  // Шаблон
      o,  // выводит только совпадающие части совпавшей строки
      flag_count,
      stuck;  // в случае зависания

} flags;

void main_func(flags* flags_s, stack* pat, int index, char** argv);
void switch_in(flags* flags_s, stack* pat, int argc, char** argv);
void flag_f(stack* pat, char** argv);
void print_error();