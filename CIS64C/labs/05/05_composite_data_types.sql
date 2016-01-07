-- Intro to PL/SQL
-- Lab Assignment 5, Problem 1 & 3
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 08 October 2015
-- Date Handed In: 08 October 2015

----- 

----- 1. Write a PL/SQL block to print information about a given country.

--- a. Declare a PL/SQL record based on the structure of the COUNTRIES table.
--& b. Use the DEFINE command to provide the country ID. Pass the value to the
--- PL/SQL block through a iSQL*Plus substitution variable. 
--& c. Use DBMS_OUTPUT.PUT_LINE to print selected information about the
--- country. [Sample output included in assignment specification]
--& d. Execute and test the PL/SQL block for the countries with the IDs CA, DE,
--- UK, US.

SET VERIFY OFF;
SET SERVEROUTPUT ON;

DEFINE v_country_id = 'CA';
-- DEFINE v_country_id = 'DE';
-- DEFINE v_country_id = 'UK';
-- DEFINE v_country_id = 'US';

DECLARE
  country_rec countries%ROWTYPE;
BEGIN
  SELECT * INTO country_rec
  FROM countries WHERE country_id = '&v_country_id';

  DBMS_OUTPUT.PUT('Country ID: ' || country_rec.country_id);
  DBMS_OUTPUT.PUT('; Country Name: ' || country_rec.country_name);
  DBMS_OUTPUT.PUT_LINE('; Region: ' || country_rec.region_id);
END;
/

-----

----- 2. SEE p5q2.sql

-----

----- 3. Modify the block you created in practice 2 to retrieve all information
----- about each department from the DEPARTMENTS table and print the
----- information to the screen, incorporating an INDEX BY table of records.

--- a. Declare an INDEX BY table, MY_DEPT_TABLE, to temporarily store the
--- number, name, and location of all the departments.
--& b. Using a loop, retrieve all department information currently in the
--- DEPARTMENTS table and store it in the INDEX BY table. Use the following
--- table to assign the value for DEPARTMENT_ID based on the value of the
--- counter used in the loop. Exit the loop when the counter reaches the
--- value 7.
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
--& c. Using another loop, retrieve the department information from the INDEX
--- BY table and print it to the screen, using DBMS_OUTPUT.PUT_LINE. A sample
--- output is shown.

SET SERVEROUTPUT ON;

DECLARE
  -- a:
  TYPE dept_table_type IS TABLE OF
    departments%ROWTYPE
    INDEX BY BINARY_INTEGER;

  my_dept_table dept_table_type;
BEGIN
  -- b:
  /*
  -- I think the following loop might be a better alternative to what is asked
  -- for in the assignment specification simply because it does not need to
  -- know how the department_id is structured (in this case,s the format is
  -- hard-coded to be multiples of 10) nor how many records there are (27 is
  -- also hard-coded in this case):
  FOR v_dept IN (
    SELECT * FROM DEPARTMENTS
  ) LOOP
    my_dept_table(v_dept.department_id) := v_dept.department_name;
  END LOOP;
  */
  -- Loop for assignment specification:
  FOR v_dept IN 1..27 LOOP
    SELECT * INTO my_dept_table(v_dept * 10)
      FROM departments WHERE department_id = v_dept * 10;
  END LOOP;

  -- c:
  FOR v_id IN my_dept_table.FIRST..my_dept_table.LAST LOOP
    IF my_dept_table.EXISTS(v_id) THEN
      DBMS_OUTPUT.PUT('Department Number: ' || my_dept_table(v_id).department_id);
      DBMS_OUTPUT.PUT('; Department Name: ' || my_dept_table(v_id).department_name);
      DBMS_OUTPUT.PUT_LINE('; Location ID: ' || my_dept_table(v_id).location_id);
    END IF;
  END LOOP;
END;
/
