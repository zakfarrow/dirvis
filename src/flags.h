#ifndef FLAGS_H
#define FLAGS_H

#include <stdbool.h>

typedef struct {
  bool help;
  bool show_hidden;
  int max_depth;
  bool no_colour;
} Flags;

void init_flags(Flags *flags);

#endif // FLAGS_H
