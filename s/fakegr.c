#include <sys/types.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static
char *
coalesce(char *lhs, char *rhs)
{
  return lhs ? lhs : rhs;
}

static struct group rv;

struct group *
getgrnam(char const *name)
{
  char *envname = getenv("FAKEGR_name");
  if (!envname || strcmp(name, envname))
    return NULL;
  rv.gr_name    = envname;
#if __FreeBSD__
  rv.gr_passwd  = coalesce(getenv("FAKEGR_passwd"), "-");
#endif
  rv.gr_gid     = atol(coalesce(getenv("FAKEGR_gid"), "0"));
  int memcnt    = atol(coalesce(getenv("FAKEGR_members"), "0"));
  if (!memcnt)
    return &rv;
  char **members;
  if ((members = calloc(memcnt + 1, sizeof(char *))) == NULL)
    return NULL;
  char *ev;
  if ((ev = malloc(256)) == NULL)
    return NULL;
  for (int i = 0; i < memcnt; ++i) {
    snprintf(ev, 256, "FAKEGR_member_%d", i);
    members[i] = coalesce(getenv(ev), "0");
  }
  members[memcnt] = NULL;
  rv.gr_mem = members;
  return &rv;
}
