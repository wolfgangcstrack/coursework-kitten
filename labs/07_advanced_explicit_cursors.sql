-- Intro to PL/SQL
-- Lab Assignment 5, Practice 07
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 15 October 2015
-- Date Handed In: 15 October 2015

-----

----- 1. In a loop, use a cursor to retrieve the department number and the
----- department name from the DEPARTMENTS table for those departments whose
----- DEPARTMENT_ID is less than 100. Pass the department number to another
----- cursor to retrieve from the EMPLOYEES table the details of employee last
----- name, job, hire date, and salary of those employees whose EMPLOYEE_ID is
----- less than 120 and who work in that department.


-----

----- 2. Modify the code in sol04_4.sql to incorporate a cursor using the FOR
----- UPDATE and WHERE CURRENT OF functionality in cursor processing.
--- a. Define the host variables.
/*
DEFINE p_empno=104
DEFINE p_empno=174
DEFINE p_empno=176
*/
--& b. Execute the modified PL/SQL block 
--& c. Execute the following command to check if your PL/SQL block has worked
--- successfully: 
/*
SELECT employee_id,salary,stars 
FROM EMP
WHERE employee_id IN (176,174,104);
*/
