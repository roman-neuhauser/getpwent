setup::

  $ . $TESTDIR/setup


insufficient operands::

  $ getgrent
  usage: getgrent -h
  usage: getgrent [-q] -t USER GROUP
  usage: getgrent [options] GROUP
  [1]


unknown option::

  $ getgrent -Y foo
  getgrent: invalid option -- 'Y'
  usage: getgrent -h
  usage: getgrent [-q] -t USER GROUP
  usage: getgrent [options] GROUP
  [1]


nonexistent group::

  $ getgrent snafu
  getgrent: snafu: no such group
  [1]
