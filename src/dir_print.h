#ifndef DIR_PRINT_H
#define DIR_PRINT_H

#include "flags.h"
#include <stdbool.h>

char *build_path(const char *dir, const char *name);
void print_indentation(int depth, int is_last);
int count_visible_entries(const char *path, Flags *flags);
int is_hidden_folder(const char *name);
void print_directory_recursive(const char *path, int depth, Flags *flags);

#endif /* DIR_PRINT_H */
