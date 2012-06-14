
//
// commander.c
//
// Copyright (c) 2012 TJ Holowaychuk <tj@vision-media.ca>
//

#include <stdio.h>
#include <string.h>
#include "commander.h"

static void
command_version(command_t *self) {
  printf("%s\n", self->version);
}

void
command_help(command_t *self) {
  printf("\n");
  printf("  Usage: %s [options]\n", self->name);
  printf("\n");
  printf("  Options:\n");
  printf("\n");
  for (int i = 0; i < self->option_count; ++i) {
    command_option_t *option = &self->options[i];
    printf("    %s, %-12s %s\n", option->small, option->large, option->description);
  }
  printf("\n");
}

void
command_init(command_t *self, const char *name, const char *version) {
  self->name = name;
  self->version = version;
  self->option_count = 0;
  command_option(self, "-V", "--version", "Display program version", command_version);
  command_option(self, "-h", "--help", "Display help information", command_help);
}

void
command_option(command_t *self, const char *small, const char *large, const char *desc, command_callback_t cb) {
  command_option_t *option = &self->options[self->option_count++];
  option->small = small;
  option->large = large;
  option->description = desc;
  option->cb = cb;
}

void
command_parse(command_t *self, int argc, const char **argv) {
  for (int i = 1; i < argc; ++i) {
    const char *arg = argv[i];
    for (int i = 0; i < self->option_count; ++i) {
      command_option_t *option = &self->options[i];
      if (!strcmp(arg, option->small) || !strcmp(arg, option->large)) {
        option->cb(self);
      }
    }
  }
}