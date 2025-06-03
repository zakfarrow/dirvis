#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

typedef struct {
  int r;
  int g;
  int b;
} RGB;

typedef struct {
  RGB directory;
  RGB file;
  RGB hidden;
  RGB executable;
} ColourTheme;

typedef struct {
  ColourTheme *colour_theme;
} Config;

void init_config(Config *conf);
void hex_to_rgb(char *hex, RGB *rgb);
void set_default_colours(ColourTheme *ct);

#endif /* CONFIG_H */
