#include <sys/types.h>
#include <err.h>
#include <errno.h>
#include <libgen.h>
#include <pwd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static
void
usage(int ex)
{
  fprintf(
    stderr
  , "usage: getpwent -h\n"
#ifdef __FreeBSD__
    "usage: getpwent [-FNcdgnprsux] USER\n"
#else
    "usage: getpwent [-FNdgnpsu] USER\n"
#endif
  );

  if (ex != 0) exit(ex);

  fprintf(
    stderr
  , "\n"
    "Display passwd(5) info for a user\n"
    "\n"
    "  Options:\n"
    "    -h                Display this message\n"
    "    -F                Omit field names from output\n"
    "    -N                USER is user id, not name\n"
#ifdef __FreeBSD__
    "    -c                Display login class\n"
#endif
    "    -d                Display home directory\n"
    "    -g                Display primary group id\n"
    "    -n                Display user name\n"
    "    -p                Display encrypted password\n"
    "    -q                No error message for nonexistent user\n"
#ifdef __FreeBSD__
    "    -r                Display password change date\n"
#endif
    "    -s                Display login shell\n"
    "    -u                Display user id\n"
#ifdef __FreeBSD__
    "    -x                Display account expiration date\n"
#endif
    "  Operands:\n"
    "    USER              Display information for USER\n"
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

#define field(pw, fmt, fname) \
  do { \
    printf("%s" fmt "\n", (names ? #fname "=" : ""), (pw)->pw_ ## fname); \
  } while (0)

#ifdef __FreeBSD__
# define optspec ":hFNcdgnpqrsux"
#else
# define optspec ":hFNdgnpqsu"
#endif

int
main(int argc, char **argv)
{
  char const *progname = basename(argv[0]);
  uint32_t opts = 0;
  int input_id = 0;
  int names = 1;
  int noerror = 0;
  int opt;
  while ((opt = getopt(argc, argv, optspec)) > -1) {
    switch (opt) {
#ifdef __FreeBSD__
    case 'c': // class
#endif
    case 'd': // dir
    case 'g': // gid
    case 'n': // name
    case 'p': // passwd
#ifdef __FreeBSD__
    case 'r': // change
      // 'r' as in "refresh"
      // since 'c' is "login class"
#endif
    case 's': // shell
    case 'u': // uid
#ifdef __FreeBSD__
    case 'x': // expire
#endif
      enable(&opts, opt);
      break;
    case 'F': // no field names
      names = 0;
      break;
    case 'N': // operand contains user id, not name
      input_id = 1;
      break;
    case 'q': // quiet: no error for nonexistent user
      noerror = 1;
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

  struct passwd *pw;

  if (input_id) {
    const char *err;
    uid_t uid = strtonum(arg, 0, UINT32_MAX, &err);
    if (err)
      errx(1, "uid value is %s: %s", err, arg);
    pw = getpwuid(uid);
  } else {
    pw = getpwnam(arg);
  }

  if (!pw)
    errno
    ? err(1, NULL)
    : noerror
      ? exit(1)
      : errx(1, "%s: no such user", arg)
  ;

  // output in field order in passwd(5)
  if (is_on(opts, 'n')) field(pw, "%s", name);
  if (is_on(opts, 'p')) field(pw, "%s", passwd);
  if (is_on(opts, 'u')) field(pw, "%d", uid);
  if (is_on(opts, 'g')) field(pw, "%d", gid);
#if __FreeBSD__
  if (is_on(opts, 'c')) field(pw, "%s", class);
  if (is_on(opts, 'r')) field(pw, "%ld", change);
  if (is_on(opts, 'x')) field(pw, "%ld", expire);
#endif
  if (is_on(opts, 'd')) field(pw, "%s", dir);
  if (is_on(opts, 's')) field(pw, "%s", shell);

  return 0;
}
