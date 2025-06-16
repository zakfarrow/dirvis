#include "config.h"
#include "dir_print.h"
#include "flags.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *option_flags[] = {"--help",      "-h", "--show-hidden", "-a",
                              "--max-depth", "-d", "--no-color",    "-c"};

#define OPTIONS_LEN (sizeof(option_flags) / sizeof(option_flags[0]))

void show_help() {
  printf("---- Help Menu ----\n");
  printf("  --exclude (-e): exclude hidden files and directories\n");
  printf("  --help(-h): open the help menu\n");
}

int depth_arg_to_int(char *val, long num) {
  num = strtol(val, &val, num);

  if (num < 1) {
    return 0;
  }
  return num;
}

bool set_optional_flags(int argc, char **argv, Flags *flags) {

  if (argc < 2) {
    printf("Usage: %s <directory_path> [options]\n", argv[0]);
    printf("Try '%s --help' for more information.\n", argv[0]);
    flags->help = true;
    return false;
  }

  for (int i = 2; i < argc; i++) {
    if ((strcmp(argv[i], "--help") == 0) | (strcmp(argv[i], "-h") == 0)) {
      flags->help = true;
      return false;
    } else if ((strcmp(argv[i], "--show-hidden") == 0) |
               (strcmp(argv[i], "-a") == 0)) {
      flags->show_hidden = true;
    } else if ((strcmp(argv[i], "--max-depth") == 0) |
               (strcmp(argv[i], "-d") == 0)) {
      if ((i + 1) >= argc) {
        printf("Error: Flag '%s' requires a depth value (positive integer)\n",
               argv[i]);
        printf("Example: %s /path --max-depth 3\n", argv[0]);
        return false;
      }
      int depth_arg_value;
      depth_arg_value = depth_arg_to_int(argv[i + 1], depth_arg_value);
      if (depth_arg_value > 0) {
        flags->max_depth = depth_arg_value;
        i++;
      } else {
        printf("Error: Invalid depth value '%s' for flag '%s'\n", argv[i + 1],
               argv[i]);
        printf("Depth must be a positive integer (1, 2, 3, ...)\n");
        return false;
      }
    } else if ((strcmp(argv[i], "--no-color") == 0) |
               (strcmp(argv[i], "-c") == 0)) {
      flags->no_color = true;
    } else {
      printf("Error: Unknown flag '%s'\n", argv[i]);
      printf("Try '%s --help' for a list of available options.\n", argv[0]);
      return false;
    }
  }

  return true;
}

int main(int argc, char **argv) {

  Flags flags = {0};
  init_flags(&flags);

  ColorTheme color_theme = {0};
  Config conf = {&color_theme};
  init_config(&conf, &flags);

  if (!set_optional_flags(argc, argv, &flags)) {
    if (flags.help) {
      show_help();
    }
    return 1;
  }

  const char *path = argv[1];

  int len = strlen(argv[1]);
  int print_len = (len > 0 && argv[1][len - 1] == '/') ? len - 1 : len;

  if (flags.no_color) {
    if (argv[1][(strlen(argv[1]) - 1)] == '/') {
      printf("%s\n", argv[1]);
    } else {
      printf("%s/\n", argv[1]);
    }
  } else {
    printf("\033[38;2;%d;%d;%dm%.*s\033[0m", color_theme.directory.r,
           color_theme.directory.g, color_theme.directory.b, print_len,
           argv[1]);
    printf("/\n");
  }

  print_directory_recursive(path, 1, &flags, &conf);

  return 0;
}
