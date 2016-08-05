# commander

  Commander option parser ported to C.

## Installation

  Install with [clib](https://github.com/clibs/clib):

```
$ clib install clibs/commander
```

## Automated --help

  The [example](#example) below would produce the following `--help`:

```

Usage: example [options]

Commands:

  test1, test1 sub command
  test2, test2 sub command

Options:

  -V, --version                 output program version
  -h, --help                    output help information
  -v, --verbose                 enable verbose stuff
  -r, --required <arg>          required arg
  -o, --optional [arg]          optional arg

```

## Example

```c
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
```

## Closure

  `cmd.data` is a `void *` so pass along a struct to the callbacks if you want.

## Usage

  `cmd.usage` defaults to "[options]".

## Links

  - Used by the [mon(1)](https://github.com/visionmedia/mon/blob/master/src/mon.c) process monitor

## Short flags

  Compound short flags are automatically expanded to their canonical form. For example `-vLO` would
  become `-v -L -O`.

## License

(The MIT License)

Copyright (c) 2012 TJ Holowaychuk &lt;tj@vision-media.ca&gt;

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

