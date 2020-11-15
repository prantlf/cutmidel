#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "cutmidel.h"

void usage() {
  printf(
    "cutmidel %d.%d.%d\n"
    "  Shortens a text by trimming it by an ellipsis in the middle.\n\n"
    "Usage: cutmidel [options] <text> <leading> <trailing> [ellipsis]\n\n"
    "  Specify the text and the maximum count of leading and trailing\n"
    "  characters. The overall maximum length will be their sum plus\n"
    "  the length of an ellipsis (3 dots by default). Zero for either leading\n"
    "  or trailing count means no leading or trailing parts.\n\n"
    "Options:\n"
    "  -V|--version  prints the version of the executable and exits\n\n"
    "  -h|--help     prints th usage information and exits\n\n"
    "Examples:\n"
    "  $ cutmidel \"~/Sources/private/cutmidel\" 5 10\n"
    "  ~/Sou...e/cutmidel\n"
    "  $ cutmidel ~/Sources/private/cutmidel 0 12 ..\n"
    "  ..ate/cutmidel\n", cutmidel_VERMAJ, cutmidel_VERMIN, cutmidel_VERPAT
  );
}

char const * const hint = "use -h to get help";
char const * ellipsis = "...";
size_t elliplen = 3;

int main (int argc, char * const * const argv) {
  // print usage information if no arguments were provided
  if (argc == 1) {
    usage();
    return 0;
  }
  // check if printing the version number or usage information was requested
  if (argc == 2) {
    char const * const arg = argv[1];
    if (strcmp(arg, "-V") == 0 || strcmp(arg, "--version") == 0) {
      printf("%d.%d.%d", cutmidel_VERMAJ, cutmidel_VERMIN, cutmidel_VERPAT);
      return 0;
    }
    if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) {
      usage();
      return 0;
    }
    // unexpected one argument or fail if unexpected arguments were not provided
    printf("invalid argument: %s (%s)\n", arg, hint);
    return 1;
  }
  // check if exactly three arguments are available
  if (argc == 3) {
    printf("too few arguments (%s)\n", hint);
    return 1;
  }
  if (argc > 5) {
    printf("too many arguments (%s)\n", hint);
    return 1;
  }

  // make sure that leading and trailing character count are numeric
  int lead = strtoul(argv[2], NULL, 10);
  if (errno != 0) {
    printf("invalid leading character count: \"%s\" (%s - %s)\n",
      argv[1], strerror(errno), hint);
    return 1;
  }
  int trail = strtoul(argv[3], NULL, 10);
  if (errno != 0) {
    printf("invalid trailing character count: \"%s\" (%s - %s)\n", argv[2], strerror(errno), hint);
    return 1;
  }
  // ellipsis cannot be put to the middle unless the middle is specified
  if (lead == 0 && trail == 0) {
    printf("both leading and trailing counts cannot be zero (%s)\n", hint);
    return 1;
  }
  // check if a custom ellipsis was specified
  if (argc == 5) {
    ellipsis = argv[4];
    elliplen = strlen(ellipsis);
  }

  // get the text to trim with its length; it will be trimmed in-place
  char * const txt = argv[1];
  size_t txtlen = strlen(txt);

  // if the input text is shorter than the ledting and trailing character
  // count plus the ellipsis length, leave it intact
  if (txtlen > lead + trail + elliplen) {
    if (lead == 0) {
      // if only the trailing part should be displayed, put the ellipsis
      // to the beginning and move the trailing part behind it
      memcpy(txt, ellipsis, elliplen);
      memmove(txt + elliplen, txt + txtlen - trail, trail);
      txt[trail + elliplen] = 0;
    } else if (trail == 0) {
      // if only the leading part should be displayed, put the ellipsis
      // right behind it
      strcpy(txt + lead, ellipsis);
    } else {
      // if both leading and trailing parts should be displayed, put the
      // ellipsis behind the leading part and move the trailing part behind it
      memcpy(txt + lead, ellipsis, elliplen);
      memmove(txt + lead + elliplen, txt + txtlen - trail, trail);
      txt[lead + trail + elliplen] = 0;
    }
  }

  // print the final text and exit
  puts(txt);
  return 0;
}
