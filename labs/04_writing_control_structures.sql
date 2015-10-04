-- Intro to PL/SQL
-- Lab Assignment 2
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 05 October 2015
-- Date Handed In: 05 October 2015

----- 1. Execute the command in the file lab04_1.sql to create the MESSAGES
----- table. Write a PL/SQL block to insert numbers into the MESSAGES table.

--- a. Insert the numbers 1 to 10, excluding 6 and 8.

--- b. Commit before the end of the block.

--- c. Select from the MESSAGES table to verify that your PL/SQL block worked.


-----

----- 2. Create a PL/SQL block that computes the commission amount for a given
----- employee based on the employee's salary.
----- Note: Include SET VERIFY OFF in your solution.

--- a. Use the DEFINE command to provide the employee ID. Pass the value to the
--- PL/SQL block through iSQL*Plus substitution variable. DEFINE p_empno = 100

--- b. If the employee's salary is less than $5,000, display the bonus amount
--- for the employee as 10% of the salary.

--- c. If the employee's salary is less than $5,000 and $10,000, display the
--- bonus amount for the employee as 15% of the salary.

--- d. If the employee's salary exceeds $10,000, display the bonus amount for
--- the employee as 20% of the salary.

--- e. If the employee's salary is NULL, display the bonus amount for the
--- employee as 0.

--- f. Test the PL/SQL block for each case using the following test cases, and
--- check each bonus amount.


-----

----- 3. Create and EMP table that is a replica of the EMPLOYEES table. You can
----- do this by executing the script lab04_3.sql. Add a new column, STARS, of
----- VARCHAR2 data type and length of 50 to the EMP table for storing asterisk
----- (*).


-----

----- 4. Create a PL/SQL block that rewards an employee by appending an
----- asterisk in the STARS column for every $1000 of the employee's salary.
----- Save your PL/SQL block in a file called p4q4.sql by clicking on the Save
----- Script button. Remember to save the script with a .sql extension.
----- Note: SET VERIFY OFF in the PL/SQL block

--- a. Use the DEFINE command to provide the employee ID. Pass the value to the
--- PL/SQL block through a iSQL*Plus substitution variable. DEFINE p_empno=104

--- b.  Initialize a v_asterisk variable that contains a NULL.

--- c.  Append an asterisk to the string for every $1000 of the salary amount.
--- For example, if the employee has a salary amount of $8000, the string of
--- asterisks should contain eight asterisks. If the employee has a salary
--- amount of $12500, the string of asterisks should contain 13 asterisks.

--- d.  Update the STARS column for the employee with the string of asterisks.

--- e.  Commit.

--- f.  Test the block for the following values:
-- DEFINE p_empno=174
-- DEFINE p_empno=176

--- g.  Display the rows from the EMP table to verify whether your PL/SQL block has executed successfully.
