setup::

  $ test $(uname -s) = Linux || exit 80

  $ . $TESTDIR/setup


insufficient operands::

  $ getpwent
  usage: getpwent -h
  usage: getpwent [-FNdgnpsu] USER
  [1]


unknown option::

  $ getpwent -Y foo
  getpwent: invalid option -- 'Y'
  usage: getpwent -h
  usage: getpwent [-FNdgnpsu] USER
  [1]


nonexistent user::

  $ getpwent snafu
  getpwent: snafu: no such user
  [1]

  $ getpwent -dgnpsu snafu
  getpwent: snafu: no such user
  [1]

NaN input with -N::

  $ getpwent -N fubar
  getpwent: uid value is invalid: fubar
  [1]
