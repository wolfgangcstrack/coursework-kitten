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

SET VERIFY OFF;
SET SERVEROUTPUT ON;

DEFINE dept_id_constraint = 100;
DEFINE emp_id_constraint = 120;

DECLARE
  CURSOR c_lower_depts
    (higher_id NUMBER)
  IS
    SELECT department_id, department_name
    FROM departments
    WHERE department_id < higher_id;

  CURSOR c_lower_emps_in_dept
    (higher_emp_id NUMBER, dept_id NUMBER)
  IS
    SELECT e.last_name, e.job_id, j.job_title, e.hire_date, e.salary
    FROM employees e, jobs j
    WHERE
      e.employee_id < higher_emp_id AND
      e.department_id = dept_id AND
      e.job_id = j.job_id;
BEGIN
  FOR v_dept IN c_lower_depts(&dept_id_constraint) LOOP
    DBMS_OUTPUT.PUT_LINE('----------');
    DBMS_OUTPUT.PUT(CHR(10)); -- output a newline character

    DBMS_OUTPUT.PUT('Department Number: ' || v_dept.department_id);
    DBMS_OUTPUT.PUT_LINE('; Department Name: ' || v_dept.department_name);

    DBMS_OUTPUT.PUT(CHR(10));

    FOR v_emp IN
      c_lower_emps_in_dept(&emp_id_constraint, v_dept.department_id)
    LOOP
      DBMS_OUTPUT.PUT(v_emp.last_name || ' ');
      DBMS_OUTPUT.PUT(v_emp.job_title || ' (' || v_emp.job_id || ') ');
      DBMS_OUTPUT.PUT_LINE(v_emp.hire_date || ' ' || v_emp.salary);
    END LOOP;

    DBMS_OUTPUT.PUT(CHR(10));
  END LOOP;
END;
/

-----

----- 2. Modify the code in sol04_4.sql to incorporate a cursor using the FOR
----- UPDATE and WHERE CURRENT OF functionality in cursor processing.
--- a. Define the host variables.
--& b. Execute the modified PL/SQL block 
--& c. Execute the following command to check if your PL/SQL block has worked
--- successfully: 
/*
SELECT employee_id,salary,stars 
FROM EMP
WHERE employee_id IN (176,174,104);
*/

SET VERIFY OFF;
SET SERVEROUTPUT ON;

DEFINE p_empno1 = 104;
DEFINE p_empno2 = 174;
DEFINE p_empno3 = 176;

DECLARE
  v_asterisk emp.stars%TYPE := NULL;

  CURSOR c_update_emp_stars
    -- 3 ID parameters here to reduce code repetition
    (empID1 NUMBER, empID2 NUMBER, empID3 NUMBER)
  IS
    SELECT salary, stars
    FROM emp 
    WHERE employee_id IN (empID1, empID2, empID3)
    FOR UPDATE OF stars NOWAIT;
  -- CURSOR c_update_emp_stars
  --   -- 3 ID parameters here to reduce code repetition
  --   (stars VARCHAR2, empID1 NUMBER, empID2 NUMBER, empID3 NUMBER)
  -- IS
  --   SELECT stars
  --   FROM emp
  --   WHERE employee_id IN (empID1, empID2, empID3);
BEGIN
  FOR v_emp IN
    c_update_emp_stars(&p_empno1, &p_empno2, &p_empno3)
  LOOP
    -- TRUNC() is used to round down floats that might cause the FOR loop to
    -- run one extra time (i.e. 8600 / 1000 = 8.6 which, without TRUNC(), will
    -- make the FOR loop run 9 times instead of 8).
    FOR counter IN 1..TRUNC(v_emp.salary / 1000) LOOP
      v_asterisk := v_asterisk || '*';
    END LOOP;

    UPDATE emp SET stars = v_asterisk
    WHERE CURRENT OF c_update_emp_stars;

    v_asterisk := '';
  END LOOP;
END;
/
