#include <stdio.h>
#include <sys/time.h>
#include <setjmp.h>

#include "src/commander.h"
 
#define assertEqualsI(a,e) _assertEqualsI(a,e,__FILE__,__LINE__)

static void _assertEqualsI(int actual, int expected, char *file, int line) {
    if (actual == expected) {
        printf("%s:%d:\033[0;32m %d OK\033[0m\n", file, line, actual);
    } else {
        printf("%s:%d:\033[0;31m expected %d but got %d\033[0m\n",
               file, line, expected, actual);
    }
}

#define assertFalse(a) _assertTrue(!(a),__FILE__,__LINE__)
#define assertTrue(a) _assertTrue((a),__FILE__,__LINE__)

static void _assertTrue(int actual, char *file, int line) {
    if (actual) {
        printf("%s:%d:\033[0;32m %d OK\033[0m\n", file, line, actual);
    } else {
        printf("%s:%d:\033[0;31m got %d\033[0m\n", file, line, actual);
    }
}

static double getElapsedSecondsSince(struct timeval* start) {
    struct timeval now;
    gettimeofday(&now, 0);
    int usec = now.tv_usec - start->tv_usec;
    int sec = now.tv_sec - start->tv_sec;

    return usec * 1e-6 + sec;
}

static int isVerboseSet = 0;
static int isRequiredSet = 0;
static int exitStatus = 0;

static void
verbose(command_t *self) {
  isVerboseSet = 1;
}

static void
required(command_t *self) {
  isRequiredSet = 1;
}
 
static jmp_buf exitCalled;

static void setStatus(int status) {
  exitStatus = status;
  longjmp(exitCalled, 1);
}

static void setUp() {
  isVerboseSet = 0;
  isRequiredSet = 0;
  exitStatus = 0;
}

static void init(command_t* target) {
  command_init(target, "name", "0.0.1");
  target->exit = setStatus;
}

static void shouldDoNothingIfArgumentListIsEmpty(void) {
  setUp();
  command_t target = {0};
  if (!setjmp(exitCalled)) command_parse(&target, 0, 0);
  assertEqualsI(target.data, 0);
}

static void shouldEnableVerbose(void)
{
  setUp();
  command_t target;
  init(&target);
  command_option(&target, "-v", "--verbose", "enable verbose stuff", verbose);
  char* argv[] = { "name", "-v", 0 };
  if (!setjmp(exitCalled)) command_parse(&target, 2, argv);
  assertTrue(isVerboseSet);
}

static void shouldSetExitStatus(void)
{
  setUp();
  command_t target;
  init(&target);
  command_option(&target, "-v", "--verbose", "enable verbose stuff", verbose);
  char* argv[] = { "name", "-w", 0 };
  if (!setjmp(exitCalled)) command_parse(&target, 2, argv);
  assertFalse(isVerboseSet);
  assertEqualsI(exitStatus, 1);
}

static void shouldSetRequired(void)
{
  setUp();
  command_t target;
  init(&target);
  command_option(&target, "-r", "--required <arg>", "required arg", required);
  char* argv[] = { "name", "-r", "val", 0 };
  if (!setjmp(exitCalled)) command_parse(&target, 3, argv);
  assertEqualsI(exitStatus, 0);
  assertTrue(isRequiredSet);
}

static void shouldFailIfRequiredIsMissingValue(void)
{
  setUp();
  command_t target;
  init(&target);
  command_option(&target, "-r", "--required <arg>", "required arg", required);
  char* argv[] = { "name", "-r", 0 };
  if (!setjmp(exitCalled)) command_parse(&target, 2, argv);
  assertEqualsI(exitStatus, 1);
  assertFalse(isRequiredSet);
}

int main(void) {
    struct timeval start;
    gettimeofday(&start, 0);

    shouldDoNothingIfArgumentListIsEmpty();
    shouldEnableVerbose();
    shouldSetExitStatus();
    shouldSetRequired();
    shouldFailIfRequiredIsMissingValue();
    printf("%f seconds\n", getElapsedSecondsSince(&start));

    return 0;
}
