.. vim: ft=rst sts=2 sw=2 tw=77

.. :Author: Roman Neuhauser
.. :Contact: neuhauser+getpwent@sigpipe.cz
.. :Copyright: This document is in the public domain.

.. this file is marked up using reStructuredText
.. lines beginning with ".." are reST directives
.. "foo_" or "`foo bar`_" is a link, defined at ".. _foo" or ".. _foo bar"
.. "::" introduces a literal block (usually some form of code)
.. "`foo`" is some kind of identifier
.. suspicious backslashes in the text ("`std::string`\s") are required for
.. reST to recognize the preceding character as syntax


Introduction
============

`getpwent` is a POSIX shell-friendly CLI frontend to `getpwnam(3)`_ /
`getpwuid(3)`_ and `getgrnam(3)`_ / `getgrgid(3)`_ functions.

.. _getpwnam(3): http://pubs.opengroup.org/onlinepubs/9699919799/functions/getpwnam.html
.. _getpwuid(3): http://pubs.opengroup.org/onlinepubs/9699919799/functions/getpwuid.html
.. _getgrnam(3): http://pubs.opengroup.org/onlinepubs/9699919799/functions/getgrnam.html
.. _getgrgid(3): http://pubs.opengroup.org/onlinepubs/9699919799/functions/getgrgid.html

Usage
=====

`getpwent` on FreeBSD::

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


`getgrent` on FreeBSD::

  $ getgrent -h
  usage: getgrent -h
  usage: getgrent [-Nq] -t USER GROUP
  usage: getgrent [-FNgmnpq] GROUP

  Display groups(5) info for a group

    Options:
      -h                Display this message
      -F                Omit field names from output
      -N                USER is user id, not name
      -g                Display group id
      -m                Display group members
      -n                Display group name
      -p                Display encrypted password
      -q                No error message for nonexistent GROUP or USER
      -t USER           Test whether USER in is GROUP
    Operands:
      GROUP             Display information for group GROUP


Examples
========

Display the minimal set of fields prescribed by
IEEE Std 1003.1-2008/Cor 1-2013 (“POSIX.1”), for
the user named `root`::

  $ getpwent -dgnsu root
  name=root
  uid=0
  gid=0
  dir=/root
  shell=/bin/csh


List members of the group named `wheel`::

  $ getgrent -m wheel
  members=2
  member_0=root
  member_1=roman


Installation
============

::

  $ ./configure
  $ make
  $ sudo make install


License
=======

Published under the `MIT license`_, see `LICENSE file`_.

.. _MIT license: https://opensource.org/licenses/MIT
.. _LICENSE file: LICENSE
