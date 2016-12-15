setup::

  $ . $TESTDIR/setup

  $ export FAKEGR_name=fubar
  $ export FAKEGR_passwd=encrypted
  $ export FAKEGR_gid=76543
  $ export FAKEGR_members=2
  $ export FAKEGR_member_0=rofl
  $ export FAKEGR_member_1=lmao

  $ export FAKEPW_name=rofl
  $ export FAKEPW_uid=321

default behavior::

  $ getgrent fubar


POSIX-mandated minimum::

  $ getgrent -gnm fubar
  name=fubar
  gid=76543
  members=2
  member_0=rofl
  member_1=lmao


all fields::

  $ getgrent -gnpm fubar
  name=fubar
  passwd=encrypted
  gid=76543
  members=2
  member_0=rofl
  member_1=lmao


field names omitted::

  $ getgrent -Fng fubar
  fubar
  76543


quiet mode::

  $ getgrent -qn fubar
  name=fubar

  $ getgrent -qn snafu
  [1]


test membership with names::

  $ getgrent -t rofl fubar

  $ getgrent -t notthere fubar
  getgrent: notthere: no such user
  [1]

  $ getgrent -qt notthere fubar
  [1]


test membership with ids::

  $ getgrent -Nt 321 76543

  $ getgrent -Nt 42 76543
  getgrent: 42: no such user
  [1]

  $ getgrent -Nqt 42 76543
  [1]
