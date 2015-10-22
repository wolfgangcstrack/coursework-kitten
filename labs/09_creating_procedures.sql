-- Intro to PL/SQL
-- Lab Assignment 7, Practice 09
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 21 October 2015
-- Date Handed In: 21 October 2015

-----

----- 1. Create and invoke the ADD_JOB procedure and consider the results.

--- a. Create a procedure called ADD_JOB to insert a new job into the JOBS
--- table. Provide the ID and title of the job, using two parameters.

--- b. Compile the code, and invoke the procedure with IT_DBA as job ID and
--- Database Administrator as job title. Query the JOBS table to view the results.

--- c. Invoke your procedure again, passing a job ID of ST_MAN and a job title
--- of Stock Manager. What happens and why?


-----

----- 2. Create a procedure called UPD_JOB to modify a job in the JOBS table.

--- a. Create a procedure called UPD_JOB to update the job title. Provide the
--- job ID and a new title, using two parameters. Include the necessary exception handling if no update occurs.

--- b. Compile the code; invoke the procedure to change the job title of the
--- job ID IT_DBA to Data Administrator. Query the JOBS table to view the
--- results. Also check the exception handling by trying to update a job that
--- does not exist (you can use job ID IT_WEB and job title Web Master).


-----

----- 3. Create a procedure called DEL_JOB to delete a job from the JOBS table.

--- a. Create a procedure called DEL_JOB to delete a job. Include the necessary
--- exception handling if no job is deleted.

--- b. Compile the code; invoke the procedure using job ID IT_DBA. Query the
--- JOBS table to view the results. Also, check the exception handling by
--- trying to delete a job that does not exist (use job ID IT_WEB). You should
--- get the message you used in the exception-handling section of the procedure
--- as output.


----- 4. Create a procedure called QUERY_EMP to query the EMPLOYEES table,
----- retrieving the salary and job ID for an employee when provided with the
----- employee ID.

--- a. Create a procedure that returns a value from the SALARY and JOB_ID
--- columns for a specified employee ID. Use host variables for the two OUT
--- parameters salary and job ID.

--- b. Compile the code, invoke the procedure to display the salary and job ID
--- for employee ID 120.

--- c. Invoke the procedure again, passing an EMPLOYEE_ID of 300. What happens
--- and why?
