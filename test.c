
#include <stdio.h>
#include "src/commander.h"

static void
foo(command_t *self) {
  printf("foo\n");
}

static void
bar(command_t *self) {
  printf("bar\n");
}

int
main(int argc, const char **argv){
  command_t cmd;
  command_init(&cmd, argv[0], "0.0.1");
  command_option(&cmd, "-f", "--foo", "Add some foo", foo);
  command_option(&cmd, "-b", "--bar", "Add some bar", bar);
  command_parse(&cmd, argc, argv);
  printf("args:\n");
  for (int i = 0; i < cmd.argc; ++i) {
    printf("  - '%s'\n", cmd.argv[i]);
  }
  return 0;
}