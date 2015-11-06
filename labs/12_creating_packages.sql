-- Intro to PL/SQL
-- Lab Assignment 10, Practice 12
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 5 November 2015
-- Date Handed In: 5 November 2015

-----

----- 1. Create a package specification and body called JOB_PACK. (You can save
----- the package body and specification in two separate files.) This package
----- contains your ADD_JOB, UPD_JOB, and DEL_JOB procedures, as well as your
----- Q_JOB function. Note: Use the code in your previously saved script files
----- when creating the package.

--- a. Make all the constructs public. Note: Consider whether you still need
--- the stand-alone procedures and functions you just packaged.

--- b. Invoke your ADD_JOB procedure by passing values IT_SYSAN and SYSTEMS
--- ANALYST as parameters.

--- c. Query the JOBS table to see the result.


-----

----- 2. Create and invoke a package that contains private and public constructs.

--- a. Create a package specification and package body called EMP_PACK that
--- contains your NEW_EMP procedure as a public construct, and your
--- VALID_DEPTID function as a private construct. (You can save the
--- specification and body into separate files.)

--- b. Invoke the NEW_EMP procedure, using 15 as a department number. Because
--- the department ID 15 does not exist in the DEPARTMENTS table, you should
--- get an error message as specified in the exception handler of your
--- procedure. 

--- c. Invoke the NEW_EMP procedure, using an existing department ID 80.


-----

----- 3.

/*
a. Create a package called CHK_PACK that contains the procedures CHK_HIREDATE and
CHK_DEPT_MGR. Make both constructs public. (You can save the specification and body 
into separate files.) The procedure CHK_HIREDATE checks whether an employee’s hire 
date is within the following range: [SYSDATE - 50 years, SYSDATE + 3 months].

Note: 
- If the date is invalid, you should raise an application error with an appropriate 
message indicating why the date value is not acceptable.
- Make sure the time component in the date value is ignored.
- Use a constant to refer to the 50 years boundary.
- A null value for the hire date should be treated as an invalid hire date. 

The procedure CHK_DEPT_MGR checks the department and manager combination for a 
given employee. The CHK_DEPT_MGR procedure accepts an employee ID and a manager 
ID. The procedure checks that the manager and employee work in the same department. 
The procedure also checks that the job title of the manager ID provided is
MANAGER.

Note: If the department ID and manager combination is invalid, you should raise an
application error with an appropriate message.

b. Test the CHK_HIREDATE procedure with the following command:
EXECUTE chk_pack.chk_hiredate('01-JAN-47')
What happens, and why?

c. Test the CHK_HIREDATE procedure with the following command:
EXECUTE chk_pack.chk_hiredate(NULL)
What happens, and why?

d. Test the CHK_DEPT_MGR procedure with the following command:
EXECUTE chk_pack.chk_dept_mgr(117,100)
What happens, and why?
*/