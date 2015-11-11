-- Intro to PL/SQL
-- Lab Assignment 11, Practice 13
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 10 November 2015
-- Date Handed In: 10 November 2015

-----

----- 1. Create a package called OVER_LOAD. Create two functions in this
----- package; name each function PRINT_IT. The function accepts a date or
----- character string and prints a date or a number, depending on how the
----- function is invoked.

--- a. Test the first version of PRINT_IT with the following set of commands:
--- VARIABLE display_date VARCHAR2(20)
--- EXECUTE :display_date := over_load.print_it (TO_DATE('08-MAR-01'))
--- PRINT display_date
--& b. Test the second version of PRINT_IT with the following set of commands:
--- VARIABLE g_emp_sal NUMBER
--- EXECUTE :g_emp_sal := over_load.print_it('33,600')
--- PRINT g_emp_sal

-----

----- 2. Create a new package, called CHECK_PACK, to implement a new business rule.

--- a. Create a procedure called CHK_DEPT_JOB to verify whether a given
--- combination of department ID and job is a valid one. In this case valid
--- means that it must be a combination that currently exists in the EMPLOYEES
--- table.
--& b. Test your CHK_DEPT_JOB package procedure by executing the following command:
--- EXECUTE check_pack.chk_dept_job(50,'ST_CLERK')
--- What happens?
--& c. Test your CHK_DEPT_JOB package procedure by executing the following command:
--- EXECUTE check_pack.chk_dept_job(20,'ST_CLERK')
--- What happens, and why?

