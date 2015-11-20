-- Intro to PL/SQL
-- Lab Assignment 14, Practice 16
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 20 November 2015
-- Date Handed In: 20 November 2015

-----

----- 1. Changes to data are allowed on tables only during normal office hours
----- of 8:45 a.m. until 5:30 p.m., Monday through Friday. Create a stored
----- procedure called SECURE_DML that prevents the DML statement from
----- executing outside of normal office hours, returning the message, “You may
----- only make changes during normal office hours.”


-----

----- 2.
--- a. Create a statement trigger on the JOBS table that calls the above
--- procedure.
--& b. Test the procedure by temporarily modifying the hours in the procedure
--- and attempting to insert a new record into the JOBS table. (Example:
--- replace 08:45 with 16:45; This attempt results in an error message) After
--- testing, reset the procedure hours asspecified in question 1 and recreate
--- the procedure as in question 1 above.


-----

----- 3. Employees should receive an automatic increase in salary if the
----- minimum salary for a job is increased. Implement this requirement through
----- a trigger on the JOBS table.
--- a. Create a stored procedure named UPD_EMP_SAL to update the salary amount.
--- This procedure accepts two parameters: the job ID for which salary has to
--- be updated, and the new minimum salary for this job ID. This procedure is
--- executed from the trigger on the JOBS table.
--& b. Create a row trigger named UPDATE_EMP_SALARY on the JOBS table that
--- invokes the procedure UPD_EMP_SAL, when the minimum salary in the JOBS
--- table is updated for a specified job ID. 
--& c. Query the EMPLOYEES table to see the current salary for employees who
--- are programmers.
--& d. Increase the minimum salary for the Programmer job from 4,000 to 5,000.
--& e. Employee Lorentz (employee ID 107) had a salary of less than 4,500.
--- Verify that her salary has been increased to the new minimum of 5,000.

