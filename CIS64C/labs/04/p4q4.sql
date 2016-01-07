-- Intro to PL/SQL
-- Lab Assignment 4, Problem 4
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 05 October 2015
-- Date Handed In: 05 October 2015

-----

----- 4. Create a PL/SQL block that rewards an employee by appending an
----- asterisk in the STARS column for every $1000 of the employee's salary.
----- Save your PL/SQL block in a file called p4q4.sql by clicking on the Save
----- Script button. Remember to save the script with a .sql extension.
----- Note: SET VERIFY OFF in the PL/SQL block

--- a. Use the DEFINE command to provide the employee ID. Pass the value to the
--- PL/SQL block through a iSQL*Plus substitution variable. DEFINE p_empno=104
--& b.  Initialize a v_asterisk variable that contains a NULL.
--& c.  Append an asterisk to the string for every $1000 of the salary amount.
--- For example, if the employee has a salary amount of $8000, the string of
--- asterisks should contain eight asterisks. If the employee has a salary
--- amount of $12500, the string of asterisks should contain 13 asterisks.
--& d.  Update the STARS column for the employee with the string of asterisks.
--& e.  Commit.
--& f.  Test the block for the following values:
-- DEFINE p_empno=174
-- DEFINE p_empno=176
--& g. Display the rows from the EMP table to verify whether your PL/SQL block
--- has executed successfully.

DEFINE p_empno = 104;
-- DEFINE p_empno = 174;
-- DEFINE p_empno = 176;

SET VERIFY OFF;
SET SERVEROUTPUT ON;

DECLARE
  v_salary emp.salary%TYPE;
  v_asterisk emp.stars%TYPE := NULL;
BEGIN
  SELECT emp.salary INTO v_salary
    FROM emp WHERE emp.employee_id = &p_empno;

  -- TRUNC() is used to round down floats that might cause the FOR loop to run
  -- one extra time (i.e. 8600 / 1000 = 8.6 which, without TRUNC(), will make
  -- the FOR loop run 9 times instead of 8).
  FOR counter IN 1..TRUNC(v_salary / 1000) LOOP
    v_asterisk := v_asterisk || '*';
  END LOOP;

  UPDATE emp SET stars = v_asterisk
    WHERE employee_id = &p_empno;
END;
/

-- show that the block executed successfully:
SELECT employee_id, salary, stars
  FROM emp
  WHERE employee_id IN (104, 174, 176);
