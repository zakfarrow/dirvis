#include "config.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define CONFIG_LOCATION "/home/dirvis.ini"

void hex_to_rgb(char *hex, RGB *rgb) {
  const char *hex_start = (hex[0] == '#') ? hex + 1 : hex;

  int len = strlen(hex_start);

  if (len == 6) {
    sscanf(hex_start, "%02x%02x%02x", &rgb->r, &rgb->g, &rgb->b);
  } else if (len == 3) {
    int r, g, b;
    sscanf(hex_start, "%1x%1x%1x", &r, &g, &b);
    rgb->r = r * 17;
    rgb->g = g * 17;
    rgb->b = b * 17;
  }
}

bool init_config(Config *conf) {
  FILE *fp;
  fp = fopen(CONFIG_LOCATION, "r");

  if (fp == NULL) {
    return false;
  }

  char line[256];

  RGB directory_rgb;
  RGB file_rgb;
  RGB hidden_rgb;
  RGB executable_rgb;

  while (fgets(line, sizeof(line), fp)) {
    line[strcspn(line, "\r\n")] = 0;
    if (line[0] == '!') {
      break;
    }

    char *value;

    if ((line[0] != '[')) {
      char *key = strtok_r(line, "=", &value);
      if (key == NULL || value == NULL)
        continue;
      if (strcmp("directory", key) == 0) {
        hex_to_rgb(value, &directory_rgb);
        conf->colour_theme->directory = directory_rgb;
      }
      if (strcmp("file", key) == 0) {
        hex_to_rgb(value, &file_rgb);
        conf->colour_theme->file = file_rgb;
      }
      if (strcmp("hidden", key) == 0) {
        hex_to_rgb(value, &hidden_rgb);
        conf->colour_theme->hidden = hidden_rgb;
      }
      if (strcmp("executable", key) == 0) {
        hex_to_rgb(value, &executable_rgb);
        conf->colour_theme->executable = executable_rgb;
      }
    }
  }

  fclose(fp);
  return true;
}
