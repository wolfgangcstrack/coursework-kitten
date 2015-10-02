Rem 
Rem $Header: utldtree.sql,v 1.2 1992/10/26 16:24:44 RKOOI Stab $ 
Rem 
Rem  Copyright (c) 1991 by Oracle Corporation 
Rem    NAME
Rem      deptree.sql - Show objects recursively dependent on given object
Rem    DESCRIPTION
Rem      This procedure, view and temp table will allow you to see all
Rem      objects that are (recursively) dependent on the given object.
Rem      Note: you will only see objects for which you have permission.
Rem      Examples:
Rem        execute deptree_fill('procedure', 'scott', 'billing');
Rem        select * from deptree order by seq#;
Rem
Rem        execute deptree_fill('table', 'scott', 'emp');
Rem        select * from deptree order by seq#;
Rem
Rem        execute deptree_fill('package body', 'scott', 'accts_payable');
Rem        select * from deptree order by seq#;
Rem
Rem        A prettier way to display this information than
Rem		select * from deptree order by seq#;
Rem	   is
Rem             select * from ideptree;
Rem        This shows the dependency relationship via indenting.  Notice
Rem        that no order by clause is needed with ideptree.
Rem    RETURNS
Rem 
Rem    NOTES
Rem      Run this script once for each schema that needs this utility.
Rem      
Rem    MODIFIED   (MM/DD/YY)
Rem     rkooi      10/26/92 -  owner -> schema for SQL2 
Rem     glumpkin   10/20/92 -  Renamed from DEPTREE.SQL 
Rem     rkooi      09/02/92 -  change ORU errors 
Rem     rkooi      06/10/92 -  add rae errors 
Rem     rkooi      01/13/92 -  update for sys vs. regular user 
Rem     rkooi      01/10/92 -  fix ideptree 
Rem     rkooi      01/10/92 -  Better formatting, add ideptree view 
Rem     rkooi      12/02/91 -  deal with cursors 
Rem     rkooi      10/19/91 -  Creation 

drop sequence deptree_seq
/
create sequence deptree_seq cache 200 /* cache 200 to make sequence faster */
/
drop table deptree_temptab
/
create table deptree_temptab
(
  object_id            number,
  referenced_object_id number,
  nest_level           number,
  seq#                 number      
)
/
create or replace procedure deptree_fill (type char, schema char, name char) is
  obj_id number;
begin
  delete from deptree_temptab;
  commit;
  select object_id into obj_id from all_objects
    where owner        = upper(deptree_fill.schema)
    and   object_name  = upper(deptree_fill.name)
    and   object_type  = upper(deptree_fill.type);
  insert into deptree_temptab
    values(obj_id, 0, 0, 0);
  insert into deptree_temptab
    select object_id, referenced_object_id,
        level, deptree_seq.nextval
      from public_dependency
      connect by prior object_id = referenced_object_id
      start with referenced_object_id = deptree_fill.obj_id;
exception
  when no_data_found then
    raise_application_error(-20000, 'ORU-10013: ' ||
      type || ' ' || schema || '.' || name || ' was not found.');
end;
/

drop view deptree
/

set echo on

REM This view will succeed if current user is sys.  This view shows 
REM which shared cursors depend on the given object.  If the current
REM user is not sys, then this view get an error either about lack
REM of privileges or about the non-existence of table x$kglxs.

set echo off
create view sys.deptree
  (nested_level, type, schema, name, seq#)
as
  select d.nest_level, o.object_type, o.owner, o.object_name, d.seq#
  from deptree_temptab d, dba_objects o
  where d.object_id = o.object_id (+)
union all
  select d.nest_level+1, 'CURSOR', '<shared>', '"'||c.kglnaobj||'"', d.seq#+.5
  from deptree_temptab d, x$kgldp k, x$kglob g, obj$ o, user$ u, x$kglob c,
      x$kglxs a
    where d.object_id = o.obj#
    and   o.name = g.kglnaobj
    and   o.owner# = u.user#
    and   u.name = g.kglnaown
    and   g.kglhdadr = k.kglrfhdl
    and   k.kglhdadr = a.kglhdadr   /* make sure it is not a transitive */
    and   k.kgldepno = a.kglxsdep   /* reference, but a direct one */
    and   k.kglhdadr = c.kglhdadr
    and   c.kglhdnsp = 0 /* a cursor */
/

set echo on

REM This view will succeed if current user is not sys.  This view
REM does *not* show which shared cursors depend on the given object.
REM If the current user is sys then this view will get an error 
REM indicating that the view already exists (since prior view create
REM will have succeeded).

set echo off
create view deptree
  (nested_level, type, schema, name, seq#)
as
  select d.nest_level, o.object_type, o.owner, o.object_name, d.seq#
  from deptree_temptab d, all_objects o
  where d.object_id = o.object_id (+)
/

drop view ideptree
/
create view ideptree (dependencies)
as
  select lpad('*',3*max(nested_level)-3) || max(nvl(type, '<no permission>')
    || ' ' || schema || decode(type, NULL, '', '.') || name)
  from deptree
  group by seq# /* So user can omit sort-by when selecting from ideptree */
/
