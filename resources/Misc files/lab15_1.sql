CREATE TABLE personnel
(id NUMBER(6) constraint personnel_id_pk PRIMARY KEY,
 last_name VARCHAR2(35),
 review CLOB,
 picture BLOB);
