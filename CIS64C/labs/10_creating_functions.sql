-- Intro to PL/SQL
-- Lab Assignment 8, Practice 10
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 29 October 2015
-- Date Handed In: 29 October 2015

-----

----- 1. Create and invoke the Q_JOB function to return a job title.

--- a. Create a function called Q_JOB to return a job title to a host variable.

CREATE OR REPLACE FUNCTION q_job
  (p_job_id IN jobs.job_id%TYPE)
RETURN VARCHAR2
IS
  v_job_title jobs.job_title%TYPE;
BEGIN
  SELECT job_title INTO v_job_title
  FROM jobs WHERE job_id = p_job_id;

  RETURN v_job_title;
END q_job;
/

--- b. Compile the code; create a host variable G_TITLE and invoke the function
--- with job ID SA_REP. Query the host variable to view the result.

VARIABLE g_title VARCHAR2(35);
EXECUTE :g_title := q_job('SA_REP');
PRINT g_title;

-----

----- 2. Create a function called ANNUAL_COMP to return the annual salary by
----- accepting two parameters: an employee’s monthly salary and commission.
----- The function should address NULL values.

--- a. Create and invoke the function ANNUAL_COMP, passing in values for
--- monthly salary and commission. Either or both values passed can be NULL,
--- but the function should still return an annual salary, which is not NULL.
--- The annual salary is defined by the basic formula:
--- (salary*12) + (commission_pct*salary*12)

CREATE OR REPLACE FUNCTION annual_comp
  (p_monthly_sal IN employees.salary%TYPE,
   p_commission_pct IN employees.commission_pct%TYPE)
RETURN NUMBER
IS
BEGIN
  IF p_monthly_sal IS NULL THEN
    RETURN 0;
  ELSIF p_commission_pct IS NULL THEN
    RETURN p_monthly_sal * 12;
  ELSE
    RETURN p_monthly_sal * 12 + p_commission_pct * p_monthly_sal * 12;
  END IF;
END annual_comp;
/

--- b. Use the function in a SELECT statement against the EMPLOYEES table for
--- department 80.

SELECT department_id,
       employee_id,
       last_name,
       annual_comp(salary, commission_pct) AS "Annual Compensation"
FROM employees
WHERE department_id = 80;


-----

----- 3. Create a procedure, NEW_EMP, to insert a new employee into the
----- EMPLOYEES table. The procedure should contain a call to the VALID_DEPTID
----- function to check whether the department ID specified for the new
----- employee exists in the DEPARTMENTS table.

--- a. Create the function VALID_DEPTID to validate a specified department ID.
--- The function should return a BOOLEAN value.

CREATE OR REPLACE FUNCTION valid_deptid
  (p_dept_id IN departments.department_id%TYPE)
RETURN BOOLEAN
IS
  v_temp departments.department_id%TYPE;
BEGIN
  SELECT department_id INTO v_temp
  FROM departments WHERE department_id = p_dept_id;
  RETURN TRUE;
EXCEPTION
  WHEN NO_DATA_FOUND THEN
    RETURN FALSE;
END valid_deptid;
/

--- b. Create the procedure NEW_EMP to add an employee to the EMPLOYEES table.
--- A new row should be added to the EMPLOYEES table if the function returns
--- TRUE. If the function returns FALSE, the procedure should alert the user
--- with an appropriate message. Define default values for most parameters. The
--- default commission is 0, the default salary is 1000, the default department
--- number is 30, the default job is SA_REP, and the default manager ID is 145.
--- For the employee’s ID, use the sequence EMPLOYEES_SEQ. Provide the last
--- name, first name, and e-mail address of the employee.

CREATE OR REPLACE PROCEDURE new_emp
  (p_first_name     IN employees.first_name%TYPE,
   p_last_name      IN employees.last_name%TYPE,
   p_email          IN employees.email%TYPE,
   p_department_id  IN employees.department_id%TYPE  DEFAULT 30,
   p_phone_number   IN employees.phone_number%TYPE   DEFAULT NULL,
   p_hire_date      IN employees.hire_date%TYPE      DEFAULT SYSDATE,
   p_job_id         IN employees.job_id%TYPE         DEFAULT 'SA_REP',
   p_salary         IN employees.salary%TYPE         DEFAULT 1000,
   p_commission_pct IN employees.commission_pct%TYPE DEFAULT 0,
   p_manager_id     IN employees.manager_id%TYPE     DEFAULT 145)
IS
  e_invalid_department_id EXCEPTION;
BEGIN
  IF valid_deptid(p_department_id) THEN
    INSERT INTO employees(
      first_name, last_name,
      email, phone_number,
      hire_date, job_id,
      salary, commission_pct,
      manager_id, department_id
    ) VALUES (
      p_first_name, p_last_name,
      p_email, p_phone_number,
      p_hire_date, p_job_id,
      p_salary, p_commission_pct,
      p_manager_id, p_department_id
    );
  ELSE
    RAISE e_invalid_department_id;
  END IF;
EXCEPTION
  WHEN e_invalid_department_id THEN
    DBMS_OUTPUT.PUT_LINE('Error: ' || p_department_id || ' is an invalid department ID.');
END new_emp;
/

--- c. Test your NEW_EMP procedure by adding a new employee named Jane Harris
--- to department 15. Allow all other parameters to default. What was the result?

SET SERVEROUTPUT ON;
EXECUTE new_emp('Jane', 'Harris', 'janeharris@example.com', 15);
-- RESULT: The Error message is printed because the department ID of 15 is invalid.

--- d. Test your NEW_EMP procedure by adding a new employee named Joe Harris to
--- department 80. Allow all other parameters to default. What was the result?

SET SERVEROUTPUT ON;
EXECUTE new_emp('Joe', 'Harris', 'joeharris@example.com', 80);
-- RESULT: The new employee is successfully inserted.
COMMIT;
