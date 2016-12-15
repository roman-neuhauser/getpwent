setup::

  $ test $(uname -s) = Linux || exit 80

  $ . $TESTDIR/setup

  $ export FAKEPW_name=fubar
  $ export FAKEPW_uid=23456
  $ export FAKEPW_gid=76543
  $ export FAKEPW_gecos=more,stuff
  $ export FAKEPW_dir=/rofl/lmao
  $ export FAKEPW_shell=/bin/bam


default behavior::

  $ getpwent fubar


happy path::

  $ getpwent -dgnsu fubar
  name=fubar
  uid=23456
  gid=76543
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
