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

CREATE OR REPLACE PROCEDURE secure_dml
IS
BEGIN
  IF TO_CHAR (SYSDATE, 'HH24:MI') NOT BETWEEN '08:45' AND '17:30'
      OR TO_CHAR (SYSDATE, 'DY') IN ('SAT', 'SUN')
  THEN
  RAISE_APPLICATION_ERROR (-20001, 
    'You may only make changes during normal office hours.');
  END IF;
END secure_dml;
/

-----

----- 2.
--- a. Create a statement trigger on the JOBS table that calls the above
--- procedure.
--& b. Test the procedure by temporarily modifying the hours in the procedure
--- and attempting to insert a new record into the JOBS table. (Example:
--- replace 08:45 with 16:45; This attempt results in an error message) After
--- testing, reset the procedure hours as specified in question 1 and recreate
--- the procedure as in question 1 above.

CREATE OR REPLACE TRIGGER secure_jobs
  BEFORE INSERT OR UPDATE OR DELETE ON jobs
BEGIN
  -- defined above
  secure_dml;
END secure_jobs;
/

-- test (with time-check changed to a short range):
INSERT INTO jobs(job_id, job_title) VALUES('A_JOB', 'A very special job');

-----

----- 3. Employees should receive an automatic increase in salary if the
----- minimum salary for a job is increased. Implement this requirement through
----- a trigger on the JOBS table.
--- a. Create a stored procedure named UPD_EMP_SAL to update the salary amount.
--- This procedure accepts two parameters: the job ID for which salary has to
--- be updated, and the new minimum salary for this job ID. This procedure is
--- executed from the trigger on the JOBS table.

CREATE OR REPLACE PROCEDURE upd_emp_sal
  (p_job_id IN employees.job_id%TYPE,
   p_min_sal IN employees.salary%TYPE)
IS
  CURSOR c_emp_sal_update(cp_job_id employees.job_id%TYPE) IS
    SELECT salary
    FROM employees
    WHERE job_id = cp_job_id
    FOR UPDATE OF salary NOWAIT;
BEGIN
  FOR v_c IN c_emp_sal_update(p_job_id)
  LOOP
    IF v_c.salary < p_min_sal THEN
      UPDATE employees SET salary = p_min_sal
      WHERE CURRENT OF c_emp_sal_update;
    END IF;
  END LOOP;
END upd_emp_sal;
/

--- b. Create a row trigger named UPDATE_EMP_SALARY on the JOBS table that
--- invokes the procedure UPD_EMP_SAL, when the minimum salary in the JOBS
--- table is updated for a specified job ID. 

CREATE OR REPLACE TRIGGER update_emp_salary
  AFTER INSERT OR UPDATE
  OF min_salary ON jobs
  FOR EACH ROW
BEGIN
  IF :NEW.min_salary > :OLD.min_salary THEN
    upd_emp_sal(:NEW.job_id, :NEW.min_salary);
  END IF;
END update_emp_salary;
/

--- c. Query the EMPLOYEES table to see the current salary for employees who
--- are programmers.

SELECT employee_id, job_id, salary
FROM employees ORDER BY job_id, employee_id;

--- d. Increase the minimum salary for the Programmer job from 4,000 to 5,000.

UPDATE jobs
SET min_salary = 5000
WHERE job_id = 'IT_PROG';

--- e. Employee Lorentz (employee ID 107) had a salary of less than 4,500.
--- Verify that her salary has been increased to the new minimum of 5,000.

-- The result is that the salary did indeed increase to the new minimum.
SELECT employee_id, salary
FROM employees
WHERE employee_id = 107;
