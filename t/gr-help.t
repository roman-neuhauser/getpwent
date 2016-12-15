setup::

  $ . $TESTDIR/setup


help::

  $ getgrent -h
  usage: getgrent -h
  usage: getgrent [-Nq] -t USER GROUP
  usage: getgrent [-FNgmnpq] GROUP
  
  Display group(5) info for a group
  
    Options:
      -h                Display this message
      -F                Omit field names from output
      -N                GROUP and USER are group and user ids, not names
      -g                Display group id
      -m                Display group members
      -n                Display group name
      -p                Display encrypted password
      -q                No error message for nonexistent GROUP or USER
      -t USER           Test whether USER in is GROUP
    Operands:
      GROUP             Display information for group GROUP
