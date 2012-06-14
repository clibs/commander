
#include "src/commander.h"

int
main(int argc, const char **argv){
  command_t cmd;
  command_init(&cmd, argv[0], "0.0.1");
  command_parse(&cmd, argc, argv);
  return 0;
}