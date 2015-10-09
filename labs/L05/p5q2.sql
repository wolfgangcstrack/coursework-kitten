-- Intro to PL/SQL
-- Lab Assignment 5, Problem 2
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 08 October 2015
-- Date Handed In: 08 October 2015

-----

----- 2. Create a PL/SQL block to retrieve the name of each department from the
----- DEPARTMENTS table and print each department name on the screen,
----- incorporating an INDEX BY table. Save the code in a file called p5q2.sql
----- by clicking the Save Script button. Save the script with a .sql extension.

--- a. Declare an INDEX BY table, MY_DEPT_TABLE, to temporarily store the name
--- of the departments.
--& b. Using a loop, retrieve the name of all departments currently in the
--- DEPARTMENTS table and store them in the INDEX BY table. Use the following
--- table to assign the value for DEPARTMENT_ID based on the value of the
--- counter used in the loop.
/*
COUNTER DEPARTMENT_ID

1       10

2       20

3       50

4       60

5       80

6       90

7       110
*/
--& c. Using another loop, retrieve the department names from the INDEX BY
--- table and print them to the screen, using DBMS_OUTPUT.PUT_LINE. The output
--- from the program is shown on the [assignment specification].

SET SERVEROUTPUT ON;

DECLARE
  -- a:
  TYPE dept_table_type IS TABLE OF
    departments.department_name%TYPE
    INDEX BY BINARY_INTEGER;

  my_dept_table dept_table_type;
BEGIN
  -- b:
  FOR v_dept IN (
    SELECT department_id, department_name FROM DEPARTMENTS
  ) LOOP
    my_dept_table(v_dept.department_id) := v_dept.department_name;
  END LOOP;

  -- c:
  FOR v_id IN my_dept_table.FIRST..my_dept_table.LAST LOOP
    IF my_dept_table.EXISTS(v_id) THEN
      DBMS_OUTPUT.PUT_LINE(my_dept_table(v_id));
    END IF;
  END LOOP;
END;
/
