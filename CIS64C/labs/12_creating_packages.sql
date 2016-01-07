-- Intro to PL/SQL
-- Lab Assignment 10, Practice 12
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 5 November 2015
-- Date Handed In: 7 November 2015

-----

----- 1. Create a package specification and body called JOB_PACK. (You can save
----- the package body and specification in two separate files.) This package
----- contains your ADD_JOB, UPD_JOB, and DEL_JOB procedures, as well as your
----- Q_JOB function. Note: Use the code in your previously saved script files
----- when creating the package.
--- a. Make all the constructs public. Note: Consider whether you still need
--- the stand-alone procedures and functions you just packaged.
--& b. Invoke your ADD_JOB procedure by passing values IT_SYSAN and SYSTEMS
--- ANALYST as parameters.
--& c. Query the JOBS table to see the result.

-- a:
CREATE OR REPLACE PACKAGE job_pack IS
  PROCEDURE add_job
    (p_job_id IN jobs.job_id%TYPE,
     p_job_title IN jobs.job_title%TYPE);
  PROCEDURE upd_job
    (p_job_id IN jobs.job_id%TYPE,
     p_job_title IN jobs.job_title%TYPE);
  PROCEDURE del_job
    (p_job_id IN jobs.job_id%TYPE);
  FUNCTION q_job
    (p_job_id IN jobs.job_id%TYPE)
    RETURN VARCHAR2;
END job_pack;
/

CREATE OR REPLACE PACKAGE BODY job_pack IS
  PROCEDURE add_job
    (p_job_id IN jobs.job_id%TYPE,
     p_job_title IN jobs.job_title%TYPE)
  IS
  BEGIN
    INSERT INTO jobs(job_id, job_title) VALUES(p_job_id, p_job_title);
  END add_job;

  PROCEDURE upd_job
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

  PROCEDURE del_job
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

  FUNCTION q_job
    (p_job_id IN jobs.job_id%TYPE)
    RETURN VARCHAR2
  IS
    v_job_title jobs.job_title%TYPE;
  BEGIN
    SELECT job_title INTO v_job_title
    FROM jobs WHERE job_id = p_job_id;

    RETURN v_job_title;
  END q_job;
END job_pack;
/

-- b:
EXECUTE job_pack.add_job('IT_SYSAN', 'SYSTEMS ANALYST');
COMMIT;

-- c:
SELECT * FROM jobs WHERE job_id = 'IT_SYSAN';

-----

----- 2. Create and invoke a package that contains private and public constructs.
--- a. Create a package specification and package body called EMP_PACK that
--- contains your NEW_EMP procedure as a public construct, and your
--- VALID_DEPTID function as a private construct. (You can save the
--- specification and body into separate files.)
--& b. Invoke the NEW_EMP procedure, using 15 as a department number. Because
--- the department ID 15 does not exist in the DEPARTMENTS table, you should
--- get an error message as specified in the exception handler of your
--- procedure. 
--& c. Invoke the NEW_EMP procedure, using an existing department ID 80.

-- a:
CREATE OR REPLACE PACKAGE emp_pack IS
  PROCEDURE new_emp
    (p_first_name     IN employees.first_name%TYPE,
     p_last_name      IN employees.last_name%TYPE,
     p_email          IN employees.email%TYPE,
     p_department_id  IN employees.department_id%TYPE  DEFAULT 30,
     p_phone_number   IN employees.phone_number%TYPE   DEFAULT NULL,
     p_hire_date      IN employees.hire_date%TYPE      DEFAULT SYSDATE,
     p_job_id         IN employees.job_id%TYPE         DEFAULT 'SA_REP',
     p_salary         IN employees.salary%TYPE         DEFAULT 1000,
     p_commission_pct IN employees.commission_pct%TYPE DEFAULT 0,
     p_manager_id     IN employees.manager_id%TYPE     DEFAULT 145);

  -- PRIVATE FUNCTION valid_deptid RETURN BOOLEAN;
END emp_pack;
/

CREATE OR REPLACE PACKAGE BODY emp_pack IS
  FUNCTION valid_deptid
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

  PROCEDURE new_emp
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
END emp_pack;
/

-- b:
SET SERVEROUTPUT ON;
EXECUTE emp_pack.new_emp('Jane', 'Harris', 'janeharris@example.com', 15);

-- c:
EXECUTE emp_pack.new_emp('Joe', 'Harris', 'joeharris@example.com', 80);
COMMIT;

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

-- An exception is raised and the error is printed out that this is an invalid
-- hire date. This is because the year '47 is more than 50 years before SYSDATE.

c. Test the CHK_HIREDATE procedure with the following command:
EXECUTE chk_pack.chk_hiredate(NULL)
What happens, and why?

-- Again, an exception is raised and the error is printed out that the parameter
-- is an invalid hire date. This is because the parameter passed is not even a
-- date.

-- 

d. Test the CHK_DEPT_MGR procedure with the following command:
EXECUTE chk_pack.chk_dept_mgr(117,100)
What happens, and why?

-- An exception is raised and the error is printed out that the given employee
-- and manager ID do not follow the given constraints. In this case, this is
-- because the employee IDs 117 and 100 do not have the same department ID, one
-- of the given constraints.

*/

-- a:
CREATE OR REPLACE PACKAGE chk_pack IS
  PROCEDURE chk_hiredate(p_hire_date IN employees.hire_date%TYPE);
  PROCEDURE chk_dept_mgr
    (p_emp_id IN employees.employee_id%TYPE,
     p_manager_id IN employees.manager_id%TYPE);
END chk_pack;
/

CREATE OR REPLACE PACKAGE BODY chk_pack IS
  PROCEDURE chk_hiredate(p_hire_date IN employees.hire_date%TYPE)
  IS
    e_invalid_hiredate EXCEPTION;
    v_fifty_years NUMBER := 50 * 365;
    v_three_months NUMBER := 3 * 30;
  BEGIN
    IF p_hire_date BETWEEN
      (SYSDATE - v_fifty_years) AND (SYSDATE + v_three_months)
    THEN
      DBMS_OUTPUT.PUT_LINE('Hire date is valid');
    ELSE
      RAISE e_invalid_hiredate;
    END IF;
  EXCEPTION
    WHEN e_invalid_hiredate THEN
      DBMS_OUTPUT.PUT_LINE('Invalid hire date - Date not within valid range.');
  END chk_hiredate;

  PROCEDURE chk_dept_mgr
    (p_emp_id IN employees.employee_id%TYPE,
     p_manager_id IN employees.manager_id%TYPE)
  IS
    v_job_id employees.job_id%TYPE;
    v_job_title jobs.job_title%TYPE;
    e_invalid_mgr EXCEPTION;
  BEGIN
    SELECT job_id INTO v_job_id
    FROM employees
    WHERE employee_id = manager_id AND
    department_id = (SELECT department_id
                     FROM employees
                     WHERE employee_id = p_emp_id);

    SELECT job_title INTO v_job_title
    FROM jobs WHERE job_id = v_job_id;

    IF INSTR(LOWER(v_job_title), 'manager') < 1 THEN
      RAISE e_invalid_mgr;
    END IF;

    -- ELSE:
    DBMS_OUTPUT.PUT_LINE('Manager ID is valid');
  EXCEPTION
    WHEN NO_DATA_FOUND THEN
      DBMS_OUTPUT.PUT_LINE('Invalid employee/manager IDs - Department ID does not match.');
    WHEN e_invalid_mgr THEN
      DBMS_OUTPUT.PUT_LINE('Invalid manager ID - ID given is not that of a manager.');
  END chk_dept_mgr;
END chk_pack;
/

SET SERVEROUTPUT ON;

-- b (see written answer next to question as well):
EXECUTE chk_pack.chk_hiredate('01-JAN-47');

-- c (see written answer next to question as well):
EXECUTE chk_pack.chk_hiredate(NULL);

-- d (see written answer next to question as well):
EXECUTE chk_pack.chk_dept_mgr(117, 100);
