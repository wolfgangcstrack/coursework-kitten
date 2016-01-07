-- Intro to PL/SQL
-- Lab Assignment 11, Practice 13
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 10 November 2015
-- Date Handed In: 10 November 2015

-----

----- 1. Create a package called OVER_LOAD. Create two functions in this
----- package; name each function PRINT_IT. The function accepts a date or
----- character string and prints a date or a number, depending on how the
----- function is invoked.

--- a. Test the first version of PRINT_IT with the following set of commands:
--- VARIABLE display_date VARCHAR2(20)
--- EXECUTE :display_date := over_load.print_it (TO_DATE('08-MAR-01'))
--- PRINT display_date
--& b. Test the second version of PRINT_IT with the following set of commands:
--- VARIABLE g_emp_sal NUMBER
--- EXECUTE :g_emp_sal := over_load.print_it('33,600')
--- PRINT g_emp_sal

CREATE OR REPLACE PACKAGE over_load IS
  FUNCTION print_it(p_date IN DATE) RETURN VARCHAR2;
  FUNCTION print_it(p_char_string IN VARCHAR2) RETURN NUMBER;
END over_load;
/

CREATE OR REPLACE PACKAGE BODY over_load IS
  FUNCTION print_it(p_date IN DATE) RETURN VARCHAR2
  IS
  BEGIN
    -- NOTE: invalid input is handled since p_date must always be of type DATE
    -- when the procedure is executed in the first place
    RETURN TO_CHAR(p_date, 'FMMonth dd, yyyy');
  END print_it;

  FUNCTION print_it(p_char_string IN VARCHAR2) RETURN NUMBER
  IS
  BEGIN
    RETURN TO_NUMBER(p_char_string, '999,999.00');
  END print_it;
END over_load;
/

-- a:
VARIABLE display_date VARCHAR2(20);
EXECUTE :display_date := over_load.print_it (TO_DATE('08-MAR-01'));
PRINT display_date;

-- b:
VARIABLE g_emp_sal NUMBER;
EXECUTE :g_emp_sal := over_load.print_it('33,600');
PRINT g_emp_sal;

-----

----- 2. Create a new package, called CHECK_PACK, to implement a new business rule.

--- a. Create a procedure called CHK_DEPT_JOB to verify whether a given
--- combination of department ID and job is a valid one. In this case valid
--- means that it must be a combination that currently exists in the EMPLOYEES
--- table.
--& b. Test your CHK_DEPT_JOB package procedure by executing the following command:
--- EXECUTE check_pack.chk_dept_job(50,'ST_CLERK')
--- What happens?
--& c. Test your CHK_DEPT_JOB package procedure by executing the following command:
--- EXECUTE check_pack.chk_dept_job(20,'ST_CLERK')
--- What happens, and why?

CREATE OR REPLACE PACKAGE check_pack IS
  PROCEDURE chk_dept_job
    (p_department_id employees.department_id%TYPE,
     p_job_id employees.job_id%TYPE);
END check_pack;
/

CREATE TABLE department_job_combos AS
  SELECT department_id, job_id FROM employees;
COMMIT;

CREATE OR REPLACE PACKAGE BODY check_pack IS
-- a:
  PROCEDURE chk_dept_job
    (p_department_id employees.department_id%TYPE,
     p_job_id employees.job_id%TYPE)
  IS
    v_temp department_job_combos%ROWTYPE;
  BEGIN
    SELECT * INTO v_temp
    FROM department_job_combos
    WHERE department_id = p_department_id AND job_id = p_job_id;

    DBMS_OUTPUT.PUT_LINE('Combination is valid');
  EXCEPTION
    WHEN NO_DATA_FOUND THEN
      DBMS_OUTPUT.PUT_LINE('Combination is invalid');
    WHEN TOO_MANY_ROWS THEN
      DBMS_OUTPUT.PUT_LINE('Combination is valid');
    WHEN OTHERS THEN
      DBMS_OUTPUT.PUT_LINE('Something else went wrong!');
  END chk_dept_job;
END check_pack;
/

-- b:
SET SERVEROUTPUT ON;
EXECUTE check_pack.chk_dept_job(50,'ST_CLERK');
/*
What happens is that the message prints for the combination being valid.
*/

-- c:
SET SERVEROUTPUT ON;
EXECUTE check_pack.chk_dept_job(20,'ST_CLERK');
/*
The message prints that the combination is invalid. This is because there is no
employee that works in department 20 and also has the job_id of ST_CLERK.
*/
