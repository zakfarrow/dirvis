#include "help_menu.h"

void show_help() {
  // clang-format off
  printf("usage: dirvis [options]\n\n");

  printf("A directory visualizer tool.\n\n");

  printf("options:\n");
  printf("  -h, --help            show this help message and exit\n");
  printf("  -a, --show-hidden     don't skip hidden files like .gitignore, .bashrc\n");
  printf("  -d, --max-depth X     prevent scanning too deep into nested folders\n");
  printf("  -D                    scan entire directory tree without depth restrictions\n");
  printf("  -c, --no-color        produce clean output suitable for scripts or logs\n");
  //clang-format on
}
