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

1 1 0

2 2 0

3 5 0

4 6 0

5 8 0

6 9 0

7 110
*/
--& c. Using another loop, retrieve the department information from the INDEX
--- BY table and print it to the screen, using DBMS_OUTPUT.PUT_LINE. A sample
--- output is shown.
