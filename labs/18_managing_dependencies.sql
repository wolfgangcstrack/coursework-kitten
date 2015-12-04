-- Intro to PL/SQL
-- Lab Assignment 16, Practice 18
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 3 December 2015
-- Date Handed In: 3 December 2015

-----

----- 1. Answer the following questions.
--- a. Can a table or a synonym be invalid?
--& b. Assuming the following scenario, is the stand-alone procedure MY_PROC
--- invalidated? The stand-alone procedure MY_PROC depends on the packaged
--- procedure MY_PROC_PACK. The MY_PROC_PACK procedure’s definition is changed
--- by recompiling the package body. The MY_PROC_PACK procedure’s declaration
--- is not altered in the package specification.


-----

----- 2. Execute the utldtree.sql script. This script is available in your lab
----- folder. Print a tree structure showing all dependencies involving your
----- NEW_EMP procedure and your VALID_DEPTID function.
----- Query the IDEPTREE view to see your results. (NEW_EMP and VALID_DEPTID
----- were created in lesson 10, “Creating Functions.” You can run the solution
----- scripts for the practice if you need to create the procedure and function.)


-----

----- 3. Dynamically validate invalid objects.
--- a. Make a copy of your EMPLOYEES table, called EMP_COP.
--& b. Alter your EMPLOYEES table and add the column TOTSAL with data type
--- NUMBER(9,2).
--& c. Create a script file to print the name, type, and status of all objects
--- that are invalid.
--& d. Create a procedure called COMPILE_OBJ that recompiles all invalid
--- procedures, functions, and packages in your schema. 
--- Make use of the ALTER_COMPILE procedure in the DBMS_DDL package.
--- Execute the COMPILE_OBJ procedure.
--& e. Run the script file that you created in question 3c again and check the
--- status column value. Do you still have INVALID objects? If you do, why are
--- they INVALID?

