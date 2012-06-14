
//
// commander.h
//
// Copyright (c) 2012 TJ Holowaychuk <tj@vision-media.ca>
//

#ifndef COMMANDER_H
#define COMMANDER_H

#ifndef MAX_OPTIONS
#define MAX_OPTIONS 64
#endif

struct command;

typedef void (* command_callback_t)(struct command *self);

typedef struct {
  const char *small;
  const char *large;
  const char *description;
  command_callback_t cb;
} command_option_t;

typedef struct command {
  const char *name;
  const char *version;
  int option_count;
  command_option_t options[MAX_OPTIONS];
} command_t;

void
command_init(command_t *self, const char *name, const char *version);

void
command_help(command_t *self);

void
command_option(command_t *self, const char *small, const char *large, const char *desc, command_callback_t cb);

void
command_parse(command_t *self, int argc, const char **argv);

#endif /* COMMANDER_H */