-- Oracle SQL
-- Lab Assignment 7
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 31 July 2015
-- Date Handed In: 31 July 2015

--------------------------------------------------

DROP TABLE StudentFee CASCADE CONSTRAINTS;
DROP TABLE Section CASCADE CONSTRAINTS;
DROP TABLE Course CASCADE CONSTRAINTS;
DROP TABLE Department CASCADE CONSTRAINTS;
DROP TABLE User CASCADE CONSTRAINTS;
DROP TABLE Resident CASCADE CONSTRAINTS;
DROP TABLE FeeSchedule;
DROP TABLE Location;
DROP TABLE College;
DROP TABLE Payment;

-- Q1: Based on the schema in Lab 6, create tables with constraints.
-- Consider using the following constraints as appropriate Primary Key,
-- Foreign key, Unique, Null or Check.
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

CREATE TABLE User (
ID NUMBER(4) NOT NULL,
first_name CHAR(50),
last_name CHAR(50),
address CHAR(100),
email CHAR(50),
tel_no CHAR(25),
type NUMBER(2),
Resident_ID NUMBER(4) NOT NULL,
CONSTRAINT User_ID_pk PRIMARY KEY(ID),
CONSTRAINT User_Resident_fk FOREIGN KEY(Resident_ID) REFERENCES Resident(ID));

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
User_ID NUMBER(4) NOT NULL,
CONSTRAINT Section_ID_pk PRIMARY KEY(ID),
CONSTRAINT Section_Course_fk FOREIGN KEY(Course_ID) REFERENCES Course(ID),
CONSTRAINT Section_Location_fk FOREIGN KEY(Location_ID) REFERENCES Location(ID),
CONSTRAINT Section_User_fk FOREIGN KEY(User_ID) REFERENCES User(ID));

CREATE TABLE StudentFee (
ID NUMBER(4) NOT NULL,
fee_paid char(1) CHECK (fee_paid in ( 'Y', 'N' )),
Student_ID NUMBER(4) NOT NULL,
Section_ID NUMBER(4) NOT NULL,
Payment_ID NUMBER(4) NOT NULL,
CONSTRAINT StudentFee_ID_pk PRIMARY KEY(ID),
CONSTRAINT StudentFee_Student_fk FOREIGN KEY(Student_ID) REFERENCES User(ID),
CONSTRAINT StudentFee_Section_fk FOREIGN KEY(Section_ID) REFERENCES Section(ID),
CONSTRAINT StudentFee_Payment_fk FOREIGN KEY(Payment_ID) REFERENCES Payment(ID));
