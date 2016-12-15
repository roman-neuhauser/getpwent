setup::

  $ . $TESTDIR/setup


insufficient operands::

  $ getpwent
  usage: getpwent -h
  usage: getpwent [options] USER
  [1]


unknown option::

  $ getpwent -Y foo
  getpwent: invalid option -- 'Y'
  usage: getpwent -h
  usage: getpwent [options] USER
  [1]


nonexistent user::

  $ getpwent snafu
  getpwent: snafu: no such user
  [1]

  $ getpwent -cdgnprsux snafu
  getpwent: snafu: no such user
  [1]
