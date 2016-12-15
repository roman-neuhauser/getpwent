setup::

  $ test $(uname -s) = Linux || exit 80

  $ . $TESTDIR/setup


help::

  $ getpwent -h
  usage: getpwent -h
  usage: getpwent [options] USER
  
  Display passwd(5) info for a user
  
    Options:
      -h                Display this message
      -N                Omit field names from output
      -d                Display home directory
      -g                Display primary group id
      -n                Display user name
      -p                Display encrypted password
      -q                No error message for nonexistent user
      -s                Display login shell
      -u                Display user id
    Operands:
      USER              Display information for USER
