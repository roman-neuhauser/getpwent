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

`getpwent` is a POSIX shell-friendly CLI frontend to `getpwnam(3)`_.

.. _getpwnam(3): http://pubs.opengroup.org/onlinepubs/9699919799/functions/getpwnam.html

Usage
=====

`getpwent` on FreeBSD::

  $ getpwent -h
  usage: getpwent -h
  usage: getpwent [options] USER

  Display passwd(5) info for a user

    Options:
      -h                Display this message
      -N                Omit field names from output
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
  usage: getgrent [-q] -t USER GROUP
  usage: getgrent [options] GROUP

  Display groups(5) info for a group

    Options:
      -h                Display this message
      -N                Omit field names from output
      -g                Display group id
      -n                Display group name
      -p                Display encrypted password
      -q                No error message for nonexistent GROUP or USER
      -t USER           Test whether USER in is GROUP
    Operands:
      GROUP             Display information for group GROUP


Example
=======

Display the minimal set of fields prescribed by
IEEE Std 1003.1-2008/Cor 1-2013 (“POSIX.1”), for
the user named `root`::

  $ getpwent -dgnsu root
  name=root
  uid=0
  gid=0
  dir=/root
  shell=/bin/csh


License
=======

Published under the `MIT license`_, see `LICENSE file`_.

.. _MIT license: https://opensource.org/licenses/MIT
.. _LICENSE file: LICENSE
