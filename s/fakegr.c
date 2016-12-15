#include <sys/types.h>
#include <err.h>
#include <grp.h>
#include <stdint.h>
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
getgrgid(gid_t id)
{
  char *envid = getenv("FAKEGR_gid");
  if (!envid)
    return NULL;
  const char *err;
  gid_t gid = strtonum(envid, 0, UINT32_MAX, &err);
  if (err)
    errx(1, "gid value is %s: %s", err, envid);
  if (id != gid)
    return NULL;
  rv.gr_gid     = gid;
  rv.gr_name    = coalesce(getenv("FAKEGR_name"), "<none>");
#if __FreeBSD__
  rv.gr_passwd  = coalesce(getenv("FAKEGR_passwd"), "-");
#endif
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
