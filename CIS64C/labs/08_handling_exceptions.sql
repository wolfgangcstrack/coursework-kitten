-- Intro to PL/SQL
-- Lab Assignment 6, Practice 08
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 19 October 2015
-- Date Handed In: 19 October 2015

-----

----- 1. Write a PL/SQL block to select the name of the employee with a given
----- salary value.
--- a. Use the DEFINE command to provide the salary. 
--& b. Pass the value to the PL/SQL block through a iSQL*Plus substitution
--- variable. If the salary entered returns more than one row, handle the
--- exception with an appropriate exception handler and insert into the
--- MESSAGES table the message “More than one employee with a salary of 
--- <salary>.”
--& c. If the salary entered does not return any rows, handle the exception
--- with an appropriate exception handler and insert into the MESSAGES table
--- the message “No employee with a salary of <salary>.”
--& d. If the salary entered returns only one row, insert into the MESSAGES
--- table the employee’s name and the salary amount.
--& e. Handle any other exception with an appropriate exception handler and
--- insert into the MESSAGES table the message “Some other error occurred.”
--& f. Test the block for a variety of test cases. Display the rows from the
--- MESSAGES table to check whether the PL/SQL block has executed successfully.
--- Some sample output is [in the assignment specification].

SET VERIFY OFF;
SET SERVEROUTPUT ON;

-- a/f:
-- DEFINE p_sal = 6000;
-- DEFINE p_sal = 5000;
-- DEFINE p_sal = 7000;
-- DEFINE p_sal = 2000;
DEFINE p_sal = 24000;

DECLARE
  v_emp employees%ROWTYPE;
BEGIN
  SELECT * INTO v_emp
  FROM employees
  WHERE salary = &p_sal;

  -- d:
  INSERT INTO messages(results) VALUES(
    v_emp.first_name || ' ' || v_emp.last_name ||
    ' is the only employee with a salary of ' || &p_sal
  );
EXCEPTION
  -- b:
  WHEN TOO_MANY_ROWS THEN
    INSERT INTO messages(results)
      VALUES('More than one employee with a salary of ' || &p_sal);
  -- c:
  WHEN NO_DATA_FOUND THEN
    INSERT INTO messages(results)
      VALUES('No employee with a salary of ' || &p_sal);
  -- e:
  WHEN OTHERS THEN
    INSERT INTO messages(results) VALUES('Some other error occurred');
END;
/

-----

----- 2. Modify the code in p3q3.sql to add an exception handler.
--- a. Use the DEFINE command to provide the department ID and department
--- location. Pass the values to the PL/SQL block through a iSQL*Plus
--- substitution variables.
--& b. Write an exception handler for the error to pass a message to the user
--- that the specified department does not exist. Use a bind variable to pass
--- the message to the user.
--& c. Execute the PL/SQL block by entering a department that does not exist.

SET VERIFY OFF;
SET SERVEROUTPUT ON;

DEFINE p_dept_name = 'Education';

/* -- PL/SQL block to INSERT new department and display (for reference)
DECLARE
  v_max_dept_id NUMBER;
BEGIN
  SELECT MAX(department_id) INTO v_max_dept_id FROM departments;
  INSERT INTO departments(department_id, department_name, location_id) VALUES(v_max_dept_id + 10, '&p_dept_name', NULL);
END;
/
SELECT * FROM departments WHERE department_id = (SELECT MAX(department_id) FROM departments);
*/

-- a:
-- DEFINE p_dept_id = 280;
--& c (department 500 should not exist):
DEFINE p_dept_id = 500;
DEFINE p_dept_loc_id = 1700;

VARIABLE g_message VARCHAR2(50);

DECLARE
  e_invalid_department_id EXCEPTION;
BEGIN
  UPDATE departments
  SET location_id = &p_dept_loc_id
  WHERE department_id = &p_dept_id;

  IF SQL%NOTFOUND THEN
    RAISE e_invalid_department_id;
  END IF;

  :g_message := 'Update successful';
-- b:
EXCEPTION
  WHEN e_invalid_department_id THEN
    :g_message := 'Department ' || &p_dept_id || ' does not exist.';
  WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE('Some other error occurred');
END;
/

PRINT g_message;


-----

----- 3. Write a PL/SQL block that prints the number of employees who earn plus
----- or minus $100 of the salary value set for an iSQL*Plus substitution
----- variable. Use the DEFINE command to provide the salary value. Pass the
----- value to the PL/SQL block through a iSQL*Plus substitution variable.
--- a. If there is no employee within that salary range, print a message to the
--- user indicating that is the case. Use an exception for this case.
--& b. If there are one or more employees within that range, the message should
--- indicate how many employees are in that salary range.
--& c. Handle any other exception with an appropriate exception handler. The
--- message should indicate that some other error occurred.

SET VERIFY OFF;
SET SERVEROUTPUT ON;

DEFINE p_sal = 7000;
-- DEFINE p_sal = 2500;
-- DEFINE p_sal = 6500;

DECLARE
  v_emp_count NUMBER;
  v_lower_bound NUMBER := &p_sal - 100;
  v_upper_bound NUMBER := &p_sal + 100;
BEGIN
  SELECT COUNT(employee_id) INTO v_emp_count
  FROM employees
  WHERE salary BETWEEN (v_lower_bound) AND (v_upper_bound);

  -- b:
  DBMS_OUTPUT.PUT_LINE(
    'There is/are ' || v_emp_count ||
    ' employee(s) with a salary between ' ||
    v_lower_bound || ' and ' || v_upper_bound
  );
EXCEPTION
  -- a:
  WHEN NO_DATA_FOUND THEN
    DBMS_OUTPUT.PUT_LINE(
      'There are no employees with a salary between ' ||
      v_lower_bound || ' and ' || v_upper_bound
    );
  -- c:
  WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE('Some other error occurred');
END;
/
