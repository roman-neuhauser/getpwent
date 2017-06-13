setup::

  $ . $TESTDIR/setup


help::

  $ getgrent -h
  usage: getgrent -h
  usage: getgrent [-q] -t USER GROUP
  usage: getgrent [options] GROUP
  
  Display groups(5) info for a group
  
    Options:
      -h                Display this message
      -I                Query by group id
      -N                Omit field names from output
      -g                Display group id
      -m                Display group members
      -n                Display group name
      -p                Display encrypted password
      -q                No error message for nonexistent GROUP or USER
      -t USER           Test whether USER in is GROUP
    Operands:
      GROUP             Display information for group GROUP
