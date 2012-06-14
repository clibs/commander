
//
// commander.c
//
// Copyright (c) 2012 TJ Holowaychuk <tj@vision-media.ca>
//

#include <stdio.h>
#include "commander.h"

void
command_init(command_t *self, const char *name, const char *version) {
  self->name = name;
  self->version = version;
  self->option_count = 0;
  command_option(self, "-V", "--version", "Display program version");
  command_option(self, "-h", "--help", "Display help information");
}

void
command_option(command_t *self, const char *small, const char *large, const char *desc) {
  command_option_t *option = &self->options[self->option_count++];
  option->small = small;
  option->large = large;
  option->description = desc;
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
command_parse(command_t *self, int argc, const char **argv) {
  
}