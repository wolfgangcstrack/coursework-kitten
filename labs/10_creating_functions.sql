-- Intro to PL/SQL
-- Lab Assignment 8, Practice 10
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 29 October 2015
-- Date Handed In: 29 October 2015

-----

----- 1. Create and invoke the Q_JOB function to return a job title.

--- a. Create a function called Q_JOB to return a job title to a host variable.


--- b. Compile the code; create a host variable G_TITLE and invoke the function
--- with job ID SA_REP. Query the host variable to view the result.


-----

----- 2. Create a function called ANNUAL_COMP to return the annual salary by
----- accepting two parameters: an employee’s monthly salary and commission.
----- The function should address NULL values.

--- a. Create and invoke the function ANNUAL_COMP, passing in values for
--- monthly salary and commission. Either or both values passed can be NULL,
--- but the function should still return an annual salary, which is not NULL.
--- The annual salary is defined by the basic formula:
--- (salary*12) + (commission_pct*salary*12)


--- b. Use the function in a SELECT statement against the EMPLOYEES table for
--- department 80.


-----

----- 3. Create a procedure, NEW_EMP, to insert a new employee into the
----- EMPLOYEES table. The procedure should contain a call to the VALID_DEPTID
----- function to check whether the department ID specified for the new
----- employee exists in the DEPARTMENTS table.

--- a. Create the function VALID_DEPTID to validate a specified department ID.
--- The function should return a BOOLEAN value.


--- b. Create the procedure NEW_EMP to add an employee to the EMPLOYEES table.
--- A new row should be added to the EMPLOYEES table if the function returns
--- TRUE. If the function returns FALSE, the procedure should alert the user
--- with an appropriate message. Define default values for most parameters. The
--- default commission is 0, the default salary is 1000, the default department
--- number is 30, the default job is SA_REP, and the default manager ID is 145.
--- For the employee’s ID, use the sequence EMPLOYEES_SEQ. Provide the last
--- name, first name, and e-mail address of the employee.


--- c. Test your NEW_EMP procedure by adding a new employee named Jane Harris
--- to department 15. Allow all other parameters to default. What was the result?


--- d. Test your NEW_EMP procedure by adding a new employee named Joe Harris to
--- department 80. Allow all other parameters to default. What was the result?

