#include <sys/types.h>
#include <err.h>
#include <pwd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static
char *
coalesce(char *lhs, char *rhs)
{
  return lhs ? lhs : rhs;
}

static struct passwd rv;

struct passwd *
getpwuid(uid_t id)
{
  char *envid = getenv("FAKEPW_uid");
  if (!envid)
    return NULL;
  const char *err;
  uid_t uid = strtonum(envid, 0, UINT32_MAX, &err);
  if (err)
    errx(1, "uid value is %s: %s", err, envid);
  if (id != uid)
    return NULL;
  rv.pw_uid     = uid;
  rv.pw_name    = coalesce(getenv("FAKEPW_name"), "-");
  rv.pw_passwd  = coalesce(getenv("FAKEPW_passwd"), "-");
  rv.pw_uid     = atol(coalesce(getenv("FAKEPW_uid"), "0"));
  rv.pw_gid     = atol(coalesce(getenv("FAKEPW_gid"), "0"));
#if __FreeBSD__
  rv.pw_class   = coalesce(getenv("FAKEPW_class"), "-");
  rv.pw_change  = atoll(coalesce(getenv("FAKEPW_change"), "0"));
  rv.pw_expire  = atoll(coalesce(getenv("FAKEPW_expire"), "0"));
#endif
  rv.pw_gecos   = coalesce(getenv("FAKEPW_gecos"), "-");
  rv.pw_dir     = coalesce(getenv("FAKEPW_dir"), "-");
  rv.pw_shell   = coalesce(getenv("FAKEPW_shell"), "-");
  return &rv;
}

struct passwd *
getpwnam(char const *name)
{
  char *envname = getenv("FAKEPW_name");
  if (!envname || strcmp(name, envname))
    return NULL;
  rv.pw_name    = envname;
  rv.pw_passwd  = coalesce(getenv("FAKEPW_passwd"), "-");
  rv.pw_uid     = atol(coalesce(getenv("FAKEPW_uid"), "0"));
  rv.pw_gid     = atol(coalesce(getenv("FAKEPW_gid"), "0"));
#if __FreeBSD__
  rv.pw_class   = coalesce(getenv("FAKEPW_class"), "-");
  rv.pw_change  = atoll(coalesce(getenv("FAKEPW_change"), "0"));
  rv.pw_expire  = atoll(coalesce(getenv("FAKEPW_expire"), "0"));
#endif
  rv.pw_gecos   = coalesce(getenv("FAKEPW_gecos"), "-");
  rv.pw_dir     = coalesce(getenv("FAKEPW_dir"), "-");
  rv.pw_shell   = coalesce(getenv("FAKEPW_shell"), "-");
  return &rv;
}
