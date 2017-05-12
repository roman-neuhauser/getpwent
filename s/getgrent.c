#include <err.h>
#include <errno.h>
#include <grp.h>
#include <libgen.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static
void
usage(int ex)
{
  fprintf(
    stderr
  , "usage: getgrent -h\n"
    "usage: getgrent [-q] -t USER GROUP\n"
    "usage: getgrent [options] GROUP\n"
  );

  if (ex != 0) exit(ex);

  fprintf(
    stderr
  , "\n"
    "Display groups(5) info for a group\n"
    "\n"
    "  Options:\n"
    "    -h                Display this message\n"
    "    -N                Omit field names from output\n"
    "    -g                Display group id\n"
    "    -m                Display group members\n"
    "    -n                Display group name\n"
#ifdef __FreeBSD__
    "    -p                Display encrypted password\n"
#endif
    "    -q                No error message for nonexistent GROUP or USER\n"
    "    -t USER           Test whether USER in is GROUP\n"
    "  Operands:\n"
    "    GROUP             Display information for group GROUP\n"
  );
  exit(ex);
}

#define bit(opt) \
  (1 << (opt - 'a'))

static
void
enable(uint32_t *opts, char opt)
{
  *opts |= bit(opt);
}

static
int
is_on(uint32_t opts, char opt)
{
  return opts & bit(opt);
}

#define field(rec, fmt, fname) \
  do { \
    printf("%s" fmt "\n", (names ? #fname "=" : ""), (rec)->gr_ ## fname); \
  } while (0)

int
main(int argc, char **argv)
{
  char const *progname = basename(argv[0]);
  uint32_t opts = 0;
  int names = 1;
  int noerror = 0;
  int membertest = 0;
  char const *testee = NULL;
  int opt;
  while ((opt = getopt(argc, argv, ":hNgmnpqt:")) > -1) {
    switch (opt) {
    case 'g': // gid
    case 'm': // members
    case 'n': // name
    case 'p': // passwd
      enable(&opts, opt);
      break;
    case 'N': // no field names
      names = 0;
      break;
    case 'q': // quiet: no error for nonexistent group
      noerror = 1;
      break;
    case 't':
      membertest = 1;
      testee = optarg;
      break;
    case 'h':
      usage(0);
    case '?':
    default:
      fprintf(stderr, "%s: invalid option -- '%c'\n"
      , progname
      , optopt
      );
      usage(1);
    }
  }
  argc -= optind;
  argv += optind;

  if (argc != 1)
    usage(1);

  char const *arg = argv[0];

  struct group *gr = getgrnam(arg);

  if (!gr)
    errno
    ? err(1, NULL)
    : noerror
      ? exit(1)
      : errx(1, "%s: no such group", arg)
  ;

  if (membertest) {
    if (!noerror && !getpwnam(testee))
      errx(1, "%s: no such user", testee);
    for (char **p = gr->gr_mem; *p != NULL; ++p)
      if (0 == strcmp(*p, testee))
        exit(0);
    exit(1);
  }
  // output in field order in group(5)
  if (is_on(opts, 'n')) field(gr, "%s", name);
  if (is_on(opts, 'p')) field(gr, "%s", passwd);
  if (is_on(opts, 'g')) field(gr, "%d", gid);
  if (is_on(opts, 'm')) {
    int memcnt = 0;
    for (char **p = gr->gr_mem; *p != NULL; ++p)
      ++memcnt;
    printf("members=%d\n", memcnt);
    for (int i = 0; i < memcnt; ++i) {
      printf("member_%d=%s\n", i, gr->gr_mem[i]);
    }
  }

  return 0;
}
