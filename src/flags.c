#include "flags.h"

void init_flags(Flags *flags) {
  flags->show_hidden = false;
  flags->help = false;
  flags->max_depth = 999;
  flags->no_color = false;
}
