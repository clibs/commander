
#include <stdio.h>
#include "src/commander.h"

typedef struct {
  int verbose;
  const char *required;
  const char *optional;
} flags_t;

static void
verbose(command_t *self) {
  flags_t *flag = (flags_t*)(self->data);
  flag->verbose = 1;
}

static void
required(command_t *self) {
  flags_t *flag = (flags_t*)(self->data);
  flag->required = self->arg;
}

static void
optional(command_t *self) {
  flags_t *flag = (flags_t*)(self->data);
  flag->optional = self->arg;
}

static void
cmd_test1(command_t *self) {
  flags_t *flag = (flags_t*)(self->data);
  printf("sub command test1 running! options: verbose '%d' required '%s' optional '%s'\n", flag->verbose, flag->required, flag->optional);
}

static void
cmd_test2(command_t *self) {
  flags_t *flag = (flags_t*)(self->data);
  printf("sub command test2 running! options: verbose '%d' required '%s' optional '%s'\n", flag->verbose, flag->required, flag->optional);
}

static void
cmd_test3(command_t *self) {
  printf("sub command test3 running with extra parameters:\n");
  if (self->argc > 1) {
    for (int i = 1; i < self->argc; ++i) {
      printf("%s\n", self->argv[i]);
    }
  }

}

int
main(int argc, char **argv){
  flags_t flags = (flags_t){.verbose = 0, .required = "default", .optional = ""};
  command_t cmd;
  cmd.data = &flags;
  command_init(&cmd, argv[0], "0.0.1");
  command_option(&cmd, "-v", "--verbose", "enable verbose stuff", verbose);
  command_option(&cmd, "-r", "--required <arg>", "required arg", required);
  command_option(&cmd, "-o", "--optional [arg]", "optional arg", optional);
  command_sub(&cmd, "test1", "test1 sub command", cmd_test1);
  command_sub(&cmd, "test2", "test2 sub command", cmd_test2);
  command_sub(&cmd, "test3", "test3 sub command", cmd_test3);

  command_parse(&cmd, argc, argv);
  command_run(&cmd);

  command_free(&cmd);
  return 0;
}
