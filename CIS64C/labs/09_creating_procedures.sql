-- Intro to PL/SQL
-- Lab Assignment 7, Practice 09
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 22 October 2015
-- Date Handed In: 22 October 2015

-----

----- 1. Create and invoke the ADD_JOB procedure and consider the results.

--- a. Create a procedure called ADD_JOB to insert a new job into the JOBS
--- table. Provide the ID and title of the job, using two parameters.
CREATE OR REPLACE PROCEDURE add_job
  (p_job_id IN jobs.job_id%TYPE,
   p_job_title IN jobs.job_title%TYPE)
IS
BEGIN
  INSERT INTO jobs(job_id, job_title) VALUES(p_job_id, p_job_title);
END add_job;
/

--- b. Compile the code, and invoke the procedure with IT_DBA as job ID and
--- Database Administrator as job title. Query the JOBS table to view the results.
EXECUTE add_job('IT_DBA', 'Database Administrator');
COMMIT;

--- c. Invoke your procedure again, passing a job ID of ST_MAN and a job title
--- of Stock Manager. What happens and why?
EXECUTE add_job('ST_MAN', 'Stock Manager');
/*
An error is returned because the primary key jobs.job_id's unique constraint is
violated. A record with job_id ST_MAN already exists in the table so we can no
longer use this ID to insert a new record.
*/


-----

----- 2. Create a procedure called UPD_JOB to modify a job in the JOBS table.
SET SERVEROUTPUT ON;

--- a. Create a procedure called UPD_JOB to update the job title. Provide the
--- job ID and a new title, using two parameters. Include the necessary
--- exception handling if no update occurs.
CREATE OR REPLACE PROCEDURE upd_job
  (p_job_id IN jobs.job_id%TYPE,
   p_job_title IN jobs.job_title%TYPE)
IS
  e_invalid_job_id EXCEPTION;
BEGIN
  UPDATE jobs
  SET job_title = p_job_title
  WHERE job_id = p_job_id;

  IF SQL%NOTFOUND THEN
    RAISE e_invalid_job_id;
  END IF;

  DBMS_OUTPUT.PUT_LINE('Update successful.');
EXCEPTION
  WHEN e_invalid_job_id THEN
    DBMS_OUTPUT.PUT_LINE('ERROR: ' || p_job_id || ' is an invalid job_id.');
END upd_job;
/

--- b. Compile the code; invoke the procedure to change the job title of the
--- job ID IT_DBA to Data Administrator. Query the JOBS table to view the
--- results. Also check the exception handling by trying to update a job that
--- does not exist (you can use job ID IT_WEB and job title Web Master).
EXECUTE upd_job('IT_DBA', 'Data Administrator');
-- will print ERROR message:
EXECUTE upd_job('IT_WEB', 'Web Master');
COMMIT;

-----

----- 3. Create a procedure called DEL_JOB to delete a job from the JOBS table.
SET SERVEROUTPUT ON;

--- a. Create a procedure called DEL_JOB to delete a job. Include the necessary
--- exception handling if no job is deleted.
CREATE OR REPLACE PROCEDURE del_job
  (p_job_id IN jobs.job_id%TYPE)
IS
  e_invalid_job_id EXCEPTION;
BEGIN
  DELETE FROM jobs
  WHERE job_id = p_job_id;

  IF SQL%NOTFOUND THEN
    RAISE e_invalid_job_id;
  END IF;

  DBMS_OUTPUT.PUT_LINE('Delete successful.');
EXCEPTION
  WHEN e_invalid_job_id THEN
    DBMS_OUTPUT.PUT_LINE('ERROR: ' || p_job_id || ' is an invalid job_id.');
END del_job;
/

--- b. Compile the code; invoke the procedure using job ID IT_DBA. Query the
--- JOBS table to view the results. Also, check the exception handling by
--- trying to delete a job that does not exist (use job ID IT_WEB). You should
--- get the message you used in the exception-handling section of the procedure
--- as output.
EXECUTE del_job('IT_DBA');
-- will print ERROR message:
EXECUTE del_job('IT_WEB');
COMMIT;

----- 4. Create a procedure called QUERY_EMP to query the EMPLOYEES table,
----- retrieving the salary and job ID for an employee when provided with the
----- employee ID.
SET SERVEROUTPUT ON;
SET VERIFY OFF;

--- a. Create a procedure that returns a value from the SALARY and JOB_ID
--- columns for a specified employee ID. Use host variables for the two OUT
--- parameters salary and job ID.
VARIABLE p_salary NUMBER;
VARIABLE p_job_id VARCHAR2(30);

CREATE OR REPLACE PROCEDURE query_emp
  (p_emp_id IN employees.employee_id%TYPE,
   p_emp_salary OUT employees.salary%TYPE,
   p_emp_job_id OUT employees.job_id%TYPE)
IS
BEGIN
  SELECT salary, job_id
  INTO p_emp_salary, p_emp_job_id
  FROM employees
  WHERE employee_id = p_emp_id;

  DBMS_OUTPUT.PUT_LINE('Employee ID: ' || &p_emp_id);
  DBMS_OUTPUT.PUT_LINE('Salary: ' || p_emp_salary);
  DBMS_OUTPUT.PUT_LINE('Job ID: ' || p_emp_job_id);
END query_emp;
/

--- b. Compile the code, invoke the procedure to display the salary and job ID
--- for employee ID 120.
-- Note: p_salary and p_job_id host variables defined in 4a.
DEFINE p_emp_id = 120;
EXECUTE query_emp(&p_emp_id, :p_salary, :p_job_id);

--- c. Invoke the procedure again, passing an EMPLOYEE_ID of 300. What happens
--- and why?
DEFINE p_emp_id = 300;
EXECUTE query_emp(&p_emp_id, :p_salary, :p_job_id);
/*
An error is returned because the employee_id of 300 does not exist in the
employee table. Consequently, the error report says "no data found". The return
of this error can be circumvented by handling the NO_DATA_FOUND exception.
*/
