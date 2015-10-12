-- Intro to PL/SQL
-- Lab Assignment 6
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 12 October 2015
-- Date Handed In: 12 October 2015

-----

----- 1. Run the command in the script lab06_1.sql to create a new table for
----- storing the salaries of the employees.

-----

----- 2. Create a PL/SQL block that determines the top employees with respect
----- to salaries.
--- a. Accept a number n from the user where n represents the number of top n
--- earners from the EMPLOYEES table. For example, to view the top five earners,
--- enter 5. Note: Use the DEFINE command to provide the value for n. Pass the
--- value to the PL/SQL block through a iSQL*Plus substitution variable.
--& b. In a loop use the iSQL*Plus substitution parameter created in step 1 and
--- gather the salaries of the top n people from the EMPLOYEES table. There
--- should be no duplication in the salaries. If two employees earn the same
--- salary, the salary should be picked up only once. 
--& c. Store the salaries in the TOP_DOGS table. 
--& d. Test a variety of special cases, such as n = 0 or where n is greater
--- than the number of employees in the EMPLOYEES table. Empty the TOP_DOGS
--- table after each test. The output shown [in the assignment specification] 
--- represents the five highest salaries in the EMPLOYEES table.


-----

----- 3. Create a PL/SQL block that does the following:
--- a. Use the DEFINE command to provide the department ID. Pass the value to
--- the PL/SQL block through a iSQL*Plus substitution variable. 
--& b. In a PL/SQL block, retrieve the last name, salary, and MANAGER ID of the
--- employees working in that department.
--& c. If the salary of the employee is less than 5000 and if the manager ID is
--- either 101 or 124, display the message <<last_name>> Due for a raise.
--- Otherwise, display the message <<last_name>> Not due for a raise. Note: SET
--- ECHO OFF to avoid displaying the PL/SQL code every time you execute the
--- script.
--& d. Test the PL/SQL block for the following cases [in the assignment
--- specification].
