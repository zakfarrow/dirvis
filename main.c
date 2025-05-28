#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>

void read_directory_structure(DIR *dr) {

  struct dirent *de;

  while ((de = readdir(dr)) != NULL)
    printf("%s\n", de->d_name);

  closedir(dr);
}

bool parse_arguments(int count, char *values[], DIR **dr) {

  *dr = opendir(values[1]);

  return (*dr == NULL);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Too few arguments!\n");
    return 1;
  }

  DIR *dr = opendir(argv[1]);
  if (dr == NULL) {
    printf("%s is not a directory!\n", argv[1]);
    return 1;
  }

  printf("Directory opened successfully!\n");
  read_directory_structure(dr);
  return 0;
}
