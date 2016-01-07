SET ECHO OFF
/* Script to build the Video Application (Part 1 - buildvid1.sql) 
   for the Oracle Introduction to Oracle with Procedure Builder course.
   Created by: Debby Kramer Creation date: 12/10/95 
   Last upated: 2/13/96
   Modified by Nagavalli Pataballa on 26-APR-2001
    For the course Introduction to Oracle9i: PL/SQL
    This part of the script creates tables and sequences that are used
    by Part B of the Additional Practices of the course.
*/

DROP TABLE rental CASCADE CONSTRAINTS;
DROP TABLE reservation CASCADE CONSTRAINTS;
DROP TABLE title_copy CASCADE CONSTRAINTS;
DROP TABLE title CASCADE CONSTRAINTS;
DROP TABLE member CASCADE CONSTRAINTS;

PROMPT Please wait while tables are created....

CREATE TABLE MEMBER
  (member_id  NUMBER (10)        CONSTRAINT member_id_pk PRIMARY KEY
 , last_name  VARCHAR2(25) 
    CONSTRAINT member_last_nn NOT NULL
 , first_name VARCHAR2(25)
 , address    VARCHAR2(100)
 , city       VARCHAR2(30)
 , phone      VARCHAR2(25)
 , join_date  DATE DEFAULT SYSDATE 
    CONSTRAINT join_date_nn NOT NULL)
/

CREATE TABLE TITLE
  (title_id   NUMBER(10)
     CONSTRAINT title_id_pk PRIMARY KEY
 , title      VARCHAR2(60)
     CONSTRAINT title_nn NOT NULL
 , description VARCHAR2(400) 
     CONSTRAINT title_desc_nn NOT NULL
 , rating      VARCHAR2(4)  
     CONSTRAINT title_rating_ck CHECK (rating IN ('G','PG','R','NC17','NR'))
 , category     VARCHAR2(20) DEFAULT 'DRAMA'   
     CONSTRAINT title_categ_ck CHECK (category IN ('DRAMA','COMEDY','ACTION',    						   'CHILD','SCIFI','DOCUMENTARY'))
 , release_date DATE)
/

CREATE TABLE TITLE_COPY
  (copy_id   NUMBER(10)
 , title_id  NUMBER(10) 
    CONSTRAINT copy_title_id_fk 
       REFERENCES title(title_id)
 , status    VARCHAR2(15) 
     CONSTRAINT copy_status_nn NOT NULL 
     CONSTRAINT copy_status_ck CHECK (status IN ('AVAILABLE', 'DESTROYED', 
						 'RENTED', 'RESERVED'))
 , CONSTRAINT copy_title_id_pk  PRIMARY KEY(copy_id, title_id))
/

CREATE TABLE RENTAL
  (book_date DATE DEFAULT SYSDATE
 , copy_id   NUMBER(10)
 , member_id NUMBER(10) 
    CONSTRAINT rental_mbr_id_fk REFERENCES member(member_id)
 , title_id  NUMBER(10)
 , act_ret_date DATE
 , exp_ret_date DATE DEFAULT SYSDATE+2
 , CONSTRAINT rental_copy_title_id_fk FOREIGN KEY (copy_id, title_id)  
              REFERENCES title_copy(copy_id,title_id)
 , CONSTRAINT rental_id_pk PRIMARY KEY(book_date, copy_id, title_id, member_id))
/

CREATE TABLE RESERVATION
  (res_date  DATE
 , member_id NUMBER(10)
 , title_id  NUMBER(10)
 , CONSTRAINT res_id_pk PRIMARY KEY(res_date, member_id, title_id))
/

PROMPT Tables created.

DROP SEQUENCE title_id_seq;
DROP SEQUENCE member_id_seq;

PROMPT Creating Sequences...

CREATE SEQUENCE member_id_seq 
  START WITH 101 
  NOCACHE
/

CREATE SEQUENCE title_id_seq 
  START WITH 92 
  NOCACHE
/

PROMPT Sequences created.

PROMPT Run buildvid2.sql now to populate the above tables.
