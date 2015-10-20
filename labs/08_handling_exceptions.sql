-- Intro to PL/SQL
-- Lab Assignment 6, Practice 08
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 15 October 2015
-- Date Handed In: 15 October 2015

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

-----

----- 2. Modify the code in p3q3.sql to add an exception handler.
--- a. Use the DEFINE command to provide the department ID and department
--- location. Pass the values to the PL/SQL block through a iSQL*Plus
--- substitution variables.
--& b. Write an exception handler for the error to pass a message to the user
--- that the specified department does not exist. Use a bind variable to pass
--- the message to the user.
--& c. Execute the PL/SQL block by entering a department that does not exist.


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