-- Oracle SQL
-- Lab Assignment 7
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 31 July 2015
-- Date Handed In: 31 July 2015

--------------------------------------------------

-- Q1: Based on the schema in Lab 6, create tables with constraints.
-- Consider using the following constraints as appropriate Primary Key,
-- Foreign key, Unique, Null or Check.
DROP TABLE StudentFee CASCADE CONSTRAINTS;
DROP TABLE Section CASCADE CONSTRAINTS;
DROP TABLE Course CASCADE CONSTRAINTS;
DROP TABLE Department CASCADE CONSTRAINTS;
DROP TABLE Member CASCADE CONSTRAINTS;
DROP TABLE Resident CASCADE CONSTRAINTS;
DROP TABLE FeeSchedule;
DROP TABLE Location;
DROP TABLE College;
DROP TABLE Payment;

CREATE TABLE Payment (
ID NUMBER(4) NOT NULL,
name CHAR(100),
type CHAR(25),
CONSTRAINT Payment_ID_pk PRIMARY KEY(ID));

CREATE TABLE College (
ID NUMBER(4) NOT NULL,
name CHAR(100),
address CHAR(100),
tel_no CHAR(25),
CONSTRAINT College_name_uk UNIQUE (name),
CONSTRAINT College_ID_pk PRIMARY KEY(ID));

CREATE TABLE Location (
ID NUMBER(5) NOT NULL,
name CHAR(100),
CONSTRAINT Location_ID_pk PRIMARY KEY(ID));

CREATE TABLE FeeSchedule (
ID NUMBER(4) NOT NULL,
start_date DATE,
end_date DATE,
period_in_days NUMBER(3),
amount_per_period NUMBER(10, 2),
CONSTRAINT FeeSchedule_ID_pk PRIMARY KEY(ID));

CREATE TABLE Resident (
ID NUMBER(4) NOT NULL,
name CHAR(100),
FeeSchedule_ID NUMBER(4) NOT NULL,
CONSTRAINT Resident_ID_pk PRIMARY KEY(ID),
CONSTRAINT Resident_FeeSchedule_fk FOREIGN KEY(FeeSchedule_ID) REFERENCES FeeSchedule(ID));

CREATE TABLE Member (
  ID NUMBER(10) NOT NULL CHECK (ID >= 1000000000),
  first_name CHAR(50),
  last_name CHAR(50),
  address CHAR(100),
  email CHAR(50),
  tel_no CHAR(25),
  type NUMBER(2),
  Resident_ID NUMBER(4) NOT NULL,
  CONSTRAINT Member_ID_pk PRIMARY KEY(ID),
  CONSTRAINT Member_Resident_fk FOREIGN KEY(Resident_ID) REFERENCES Resident(ID)
)
PARTITION BY RANGE (ID) (
  PARTITION Member_ID_r1 VALUES LESS THAN (2000000000),
  PARTITION Member_ID_r2 VALUES LESS THAN (3000000000),
  PARTITION Member_ID_r3 VALUES LESS THAN (4000000000),
  PARTITION Member_ID_r4 VALUES LESS THAN (5000000000),
  PARTITION Member_ID_r5 VALUES LESS THAN (6000000000),
  PARTITION Member_ID_r6 VALUES LESS THAN (7000000000),
  PARTITION Member_ID_r7 VALUES LESS THAN (8000000000),
  PARTITION Member_ID_r8 VALUES LESS THAN (9000000000),
  PARTITION Member_ID_r9 VALUES LESS THAN (MAXVALUE)
);

CREATE TABLE Department (
ID NUMBER(4) NOT NULL,
name CHAR(100),
Location_ID NUMBER(5) NOT NULL,
College_ID NUMBER(4) NOT NULL,
CONSTRAINT Department_ID_pk PRIMARY KEY(ID),
CONSTRAINT Department_Location_fk FOREIGN KEY(Location_ID) REFERENCES Location(ID),
CONSTRAINT Department_College_fk FOREIGN KEY(College_ID) REFERENCES College(ID));

CREATE TABLE Course (
ID NUMBER(4) NOT NULL,
course_no NUMBER(2),
name CHAR(100),
prereq_ID NUMBER(4) CONSTRAINT Course_prereq_sk REFERENCES Course(ID),
Department_ID NUMBER(4) NOT NULL,
CONSTRAINT Course_ID_pk PRIMARY KEY(ID),
CONSTRAINT Course_Department_fk FOREIGN KEY(Department_ID) REFERENCES Department(ID));

CREATE TABLE Section (
ID NUMBER(4) NOT NULL,
section_no NUMBER(2),
Course_ID NUMBER(4) NOT NULL,
Location_ID NUMBER(5) NOT NULL,
start_time NUMBER(4),
end_time NUMBER(4),
start_date DATE,
end_date DATE,
Member_ID NUMBER(4) NOT NULL,
CONSTRAINT Section_ID_pk PRIMARY KEY(ID),
CONSTRAINT Section_Course_fk FOREIGN KEY(Course_ID) REFERENCES Course(ID),
CONSTRAINT Section_Location_fk FOREIGN KEY(Location_ID) REFERENCES Location(ID),
CONSTRAINT Section_Member_fk FOREIGN KEY(Member_ID) REFERENCES Member(ID));

CREATE TABLE StudentFee (
  ID NUMBER(10) NOT NULL,
  fee_paid CHAR(1) CHECK (fee_paid IN ('Y', 'N')),
  Student_ID NUMBER(4) NOT NULL,
  Section_ID NUMBER(4) NOT NULL,
  Payment_ID NUMBER(4) NOT NULL,
  CONSTRAINT StudentFee_ID_pk PRIMARY KEY(ID),
  CONSTRAINT StudentFee_Student_fk FOREIGN KEY(Student_ID) REFERENCES Member(ID),
  CONSTRAINT StudentFee_Section_fk FOREIGN KEY(Section_ID) REFERENCES Section(ID),
  CONSTRAINT StudentFee_Payment_fk FOREIGN KEY(Payment_ID) REFERENCES Payment(ID)
)
PARTITION BY HASH (ID)
PARTITIONS 10;

--------------------------------------------------

-- Q2. Project which tables will increase quickly and implement
-- partitioning types in at least 2 tables in your schema. Explain why
-- these partitioning types would be useful in the context of your implementation.
/* -- See answers above for actual partitioning statements.
The Member table was partitioned by range because the Member.ID field must
always be at least 10 digits and these 10 digits also fall within certain
numerical ranges; these ranges are specified in the partitioning statement.

The StudentFee table was partitioned by hash because, while StudentFee.ID is
very similar to the Member.ID field, the StudentFee table is not partitioned
the same way because Students can have multiple fees whose id's are not always
organized in an easily ordered, numerical manner. In other words, partitioning
the StudentFee by range of its ID's would be pointless since the ID's only serve
to distinguish each record and nothing else (unlike Member.ID being a foreign
key for multiple tables).

In general, both tables were chosen to be partitioned also because of the fact
that there can/will be a very large number of students and most likely an even
larger number of student fees as each student can have zero or more student fees.
*/
