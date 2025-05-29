#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

char *build_path(const char *dir, const char *name) {
  size_t dir_len = strlen(dir);
  size_t name_len = strlen(name);
  char *path = malloc(dir_len + name_len + 2);

  if (path == NULL)
    return NULL;

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

int count_visible_entries(const char *path, int exclude_hidden) {
  DIR *dir = opendir(path);
  if (dir == NULL)
    return 0;

  struct dirent *dp;
  int count = 0;

  while ((dp = readdir(dir)) != NULL) {
    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
      continue;
    }

    if (exclude_hidden && dp->d_name[0] == '.') {
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

void print_directory_recursive(const char *path, int depth,
                               int exclude_hidden) {
  DIR *dir;
  struct dirent *dp;
  struct stat file_stat;
  char *full_path;
  int entry_count = 0;
  int total_entries = count_visible_entries(path, exclude_hidden);

  dir = opendir(path);
  if (dir == NULL) {
    print_indentation(depth, 1);
    printf("[ERROR] Could not open directory\n");
    return;
  }

  while ((dp = readdir(dir)) != NULL) {
    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
      continue;
    }

    if (exclude_hidden && is_hidden_folder(dp->d_name)) {
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
        if (is_hidden_folder(dp->d_name)) {
          printf("%s/ [hidden]\n", dp->d_name);
        } else {
          printf("%s/\n", dp->d_name);
        }

        print_directory_recursive(full_path, depth + 1, exclude_hidden);

      } else if (S_ISREG(file_stat.st_mode)) {
        if (is_hidden_folder(dp->d_name)) {
          printf("%s [hidden]\n", dp->d_name);
        } else {
          printf("%s\n", dp->d_name);
        }
      } else if (S_ISLNK(file_stat.st_mode)) {
        printf("%s → [link]\n", dp->d_name);
      } else {
        printf("%s [other]\n", dp->d_name);
      }
    } else {
      printf("%s [ERROR: cannot stat]\n", dp->d_name);
    }

    free(full_path);
  }

  closedir(dir);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <directory_path> [-e]\n", argv[0]);
    printf("  -e: exclude hidden files and directories\n");
    return 1;
  }

  const char *path = argv[1];

  int exclude_hidden = 0;
  if (argc >= 3 && strcmp(argv[2], "-e") == 0) {
    exclude_hidden = 1;
    printf("%s/ (excluding hidden files)\n", path);
  } else {
    printf("%s/\n", path);
  }

  print_directory_recursive(path, 1, exclude_hidden);

  return 0;
}
