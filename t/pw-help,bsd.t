setup::

  $ test $(uname -s) = FreeBSD || exit 80

  $ . $TESTDIR/setup


help::

  $ getpwent -h
  usage: getpwent -h
  usage: getpwent [-FNcdgnprsux] USER
  
  Display passwd(5) info for a user
  
    Options:
      -h                Display this message
      -F                Omit field names from output
      -N                USER is user id, not name
      -c                Display login class
      -d                Display home directory
      -g                Display primary group id
      -n                Display user name
      -p                Display encrypted password
      -q                No error message for nonexistent user
      -r                Display password change date
      -s                Display login shell
      -u                Display user id
      -x                Display account expiration date
    Operands:
      USER              Display information for USER
