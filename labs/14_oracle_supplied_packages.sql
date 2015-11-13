-- Intro to PL/SQL
-- Lab Assignment 12, Practice 14
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 13 November 2015
-- Date Handed In: 13 November 2015

-----

----- 1.
--- a. Create a DROP_TABLE procedure that drops the table specified in the
--- input parameter. Use the procedures and functions from the supplied
--- DBMS_SQL package.
--& b. To test the DROP_TABLE procedure, first create a new table called
--- EMP_DUP as a copy of the EMPLOYEES table. 
--& c. Execute the DROP_TABLE procedure to drop the EMP_DUP table.


-----

----- 2.
--- a. Create another procedure called DROP_TABLE2 that drops the table
--- specified in the input parameter. Use the EXECUTE IMMEDIATE statement.
--& b. Repeat the test outlined in steps 1-b and 1-c.


-----

----- 3.
--- a. Create a procedure called ANALYZE_OBJECT that analyzes the given object
--- that you specified in the input parameters. Use the DBMS_DDL package, and
--- use the COMPUTE method.
--& b. Test the procedure using the EMPLOYEES table. Confirm that the
--- ANALYZE_OBJECT procedure has run by querying the LAST_ANALYZED column in
--- the USER_TABLES data dictionary view.


-----

----- 4.
--- a. Schedule ANALYZE_OBJECT by using DBMS_JOB. Analyze the DEPARTMENTS table,
--- and schedule the job to run in five minutes time from now. (To start the
--- job in five minutes from now, set the parameter NEXT_DATE = 5/(24*60) = 1/288.)
--& b. Confirm that the job has been scheduled by using USER_JOBS.


-----

----- 5. Create a procedure called CROSS_AVGSAL that generates a text file
----- report of employees who have exceeded the average salary of their
----- department. The partial code is provided for you in the file lab14_5.sql.

--- a. Your program should accept two parameters. The first parameter
--- identifies the output directory. The second parameter identifies the text
--- file name to which your procedure writes. 
--& b. Your instructor will inform you of the directory location. When you
--- invoke the program, name the second parameter sal_rptxx.txt where xx stands
--- for your user number, such as 01, 15, and so on.
--& c. Add an exception handling section to handle errors that may be
--- encountered from using the UTL_FILE package.
---Sample output from this file follows:
/*
EMPLOYEES OVER THE AVERAGE SALARY OF THEIR DEPARTMENT: 

REPORT GENERATED ON 26-FEB-01

Hartstein 20 $13,000.00

Raphaely 30 $11,000.00

Marvis 40 $6,500.00

...

*** END OF REPORT ***
*/
