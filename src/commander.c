
//
// commander.c
//
// Copyright (c) 2012 TJ Holowaychuk <tj@vision-media.ca>
//

#include <stdio.h>
#include "commander.h"

void
command_init(command_t *self) {
  self->option_count = 0;
}

void
command_option(command_t *self, char *small, char *large, char *desc) {
  command_option_t *option = &self->options[self->option_count++];
  option->small = small;
  option->large = large;
  option->description = desc;
}

void
command_help(command_t *self, const char *name) {
  printf("\n");
  printf("  Usage: %s [options]\n", name);
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