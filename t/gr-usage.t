setup::

  $ . $TESTDIR/setup


insufficient operands::

  $ getgrent
  usage: getgrent -h
  usage: getgrent [-Nq] -t USER GROUP
  usage: getgrent [-FNgmnpq] GROUP
  [1]


unknown option::

  $ getgrent -Y foo
  getgrent: invalid option -- 'Y'
  usage: getgrent -h
  usage: getgrent [-Nq] -t USER GROUP
  usage: getgrent [-FNgmnpq] GROUP
  [1]


nonexistent group::

  $ getgrent snafu
  getgrent: snafu: no such group
  [1]

NaN input with -N::

  $ getgrent -N fubar
  getgrent: gid value is invalid: fubar
  [1]

  $ getgrent -Nt snafu fubar
  getgrent: gid value is invalid: fubar
  [1]

  $ getgrent -Nt snafu 69
  getgrent: uid value is invalid: snafu
  [1]
