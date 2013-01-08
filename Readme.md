
# commander.c

  Commander option parser ported to C.

## Automated --help

  The previous example would produce the following `--help`:

```

Usage: example [options]

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
#include "commander.h"

static void
verbose(command_t *self) {
  printf("verbose: enabled\n");
}

static void
required(command_t *self) {
  printf("required: %s\n", self->arg);
}

static void
optional(command_t *self) {
  printf("optional: %s\n", self->arg);
}

int
main(int argc, const char **argv){
  command_t cmd;
  command_init(&cmd, argv[0], "0.0.1");
  command_option(&cmd, "-v", "--verbose", "enable verbose stuff", verbose);
  command_option(&cmd, "-r", "--required <arg>", "required arg", required);
  command_option(&cmd, "-o", "--optional [arg]", "optional arg", optional);
  command_parse(&cmd, argc, argv);
  printf("additional args:\n");
  for (int i = 0; i < cmd.argc; ++i) {
    printf("  - '%s'\n", cmd.argv[i]);
  }
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

