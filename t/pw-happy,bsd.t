setup::

  $ test $(uname -s) = FreeBSD || exit 80

  $ . $TESTDIR/setup

  $ export FAKEPW_name=fubar
  $ export FAKEPW_passwd=encrypted
  $ export FAKEPW_uid=23456
  $ export FAKEPW_gid=76543
  $ export FAKEPW_class=high
  $ export FAKEPW_change=1287532800 # 2020-05-10T00:00:00
  $ export FAKEPW_expire=1589068800 # 2010-10-20T00:00:00
  $ export FAKEPW_gecos=more,stuff
  $ export FAKEPW_dir=/rofl/lmao
  $ export FAKEPW_shell=/bin/bam


default behavior::

  $ getpwent fubar


POSIX-mandated minimum::

  $ getpwent -dgnsu fubar
  name=fubar
  uid=23456
  gid=76543
  dir=/rofl/lmao
  shell=/bin/bam


all fields::

  $ getpwent -cdgnprsux fubar
  name=fubar
  passwd=encrypted
  uid=23456
  gid=76543
  class=high
  change=1287532800
  expire=1589068800
  dir=/rofl/lmao
  shell=/bin/bam


field names omitted::

  $ getpwent -Fnu fubar
  fubar
  23456


quiet mode::

  $ getpwent -qn fubar
  name=fubar

  $ getpwent -qn snafu
  [1]
