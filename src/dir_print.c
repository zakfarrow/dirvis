#include "dir_print.h"
#include "flags.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char *build_path(const char *dir, const char *name) {
  size_t dir_len = strlen(dir);
  size_t name_len = strlen(name);
  char *path = malloc(dir_len + name_len + 2);

  if (path == NULL) {
    return NULL;
  }

  strcpy(path, dir);
  if (dir[dir_len - 1] != '/' && dir[dir_len - 1] != '\\') {
    strcat(path, "/");
  }
  strcat(path, name);
  return path;
}

void print_indentation(int depth, int is_last) {
  for (int i = 0; i < depth; i++) {
    if (i == depth - 1) {
      if (is_last) {
        printf("└── ");
      } else {
        printf("├── ");
      }
    } else {
      printf("│   ");
    }
  }
}

int count_visible_entries(const char *path, Flags *flags) {
  DIR *dir = opendir(path);
  if (dir == NULL) {
    return 0;
  }

  struct dirent *dp;
  int count = 0;

  while ((dp = readdir(dir)) != NULL) {
    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
      continue;
    }

    if (!flags->show_hidden && dp->d_name[0] == '.') {
      continue;
    }

    count++;
  }

  closedir(dir);
  return count;
}

int is_hidden_folder(const char *name) {
  return (name[0] == '.' && strcmp(name, ".") != 0 && strcmp(name, "..") != 0);
}

void print_directory_recursive(const char *path, int depth, Flags *flags) {
  DIR *dir;
  struct dirent *dp;
  struct stat file_stat;
  char *full_path;
  int entry_count = 0;
  int total_entries = count_visible_entries(path, flags);

  dir = opendir(path);
  if (dir == NULL) {
    print_indentation(depth, 1);
    printf("[ERROR] Could not open directory\n");
    return;
  }

  while ((dp = readdir(dir)) != NULL && depth <= flags->max_depth) {
    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
      continue;
    }

    if (!flags->show_hidden && is_hidden_folder(dp->d_name)) {
      continue;
    }

    entry_count++;
    int is_last = (entry_count == total_entries);

    full_path = build_path(path, dp->d_name);
    if (full_path == NULL) {
      print_indentation(depth, is_last);
      printf("[ERROR] Memory allocation error\n");
      continue;
    }

    print_indentation(depth, is_last);

    if (stat(full_path, &file_stat) == 0) {
      if (S_ISDIR(file_stat.st_mode)) {
        printf("%s/\n", dp->d_name);
        print_directory_recursive(full_path, depth + 1, flags);
      } else {
        printf("%s\n", dp->d_name);
      }
    } else {
      printf("%s [ERROR: cannot stat]\n", dp->d_name);
    }

    free(full_path);
  }

  closedir(dir);
}
