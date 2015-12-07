-- Intro to PL/SQL
-- Lab Assignment 16, Practice 18
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 3 December 2015
-- Date Handed In: 6 December 2015

-----

----- 1. Answer the following questions.
--- a. Can a table or a synonym be invalid?
/*
In both cases, yes. For example, a table can be invalid when its records
reference other objects from different tables and those objects are modified
such that they violate existing constraints. An example for a synonym becoming
invalid would be when there is a name referencing error, such as when a table
and a synonym are created with the same name.
*/

--- b. Assuming the following scenario, is the stand-alone procedure MY_PROC
--- invalidated? The stand-alone procedure MY_PROC depends on the packaged
--- procedure MY_PROC_PACK. The MY_PROC_PACK procedure’s definition is changed
--- by recompiling the package body. The MY_PROC_PACK procedure’s declaration
--- is not altered in the package specification.
/*
MY_PROC is not invalidated, but may throw an error depending on whether
MY_PROC_PACK was invalidated. If MY_PROC_PACK's definition was changed in the
package body such that its parameter declaration or return type was changed,
MY_PROC would throw an error when called because MY_PROC_PACK is invalid. To
fix this, MY_PROC_PACK's package specification must be changed to match the
package body definition.
*/

-----

----- 2. Execute the utldtree.sql script. This script is available in your lab
----- folder. Print a tree structure showing all dependencies involving your
----- NEW_EMP procedure and your VALID_DEPTID function.
----- Query the IDEPTREE view to see your results. (NEW_EMP and VALID_DEPTID
----- were created in lesson 10, “Creating Functions.” You can run the solution
----- scripts for the practice if you need to create the procedure and function.)
EXECUTE deptree_fill('PROCEDURE', 'sqluser35', 'new_emp');
EXECUTE deptree_fill('FUNCTION', 'sqluser35', 'valid_deptid');

-- Display output:
SELECT * FROM ideptree;

-----

----- 3. Dynamically validate invalid objects.
--- a. Make a copy of your EMPLOYEES table, called EMP_COP.
CREATE TABLE emp_cop AS (SELECT * FROM employees);

--- b. Alter your EMPLOYEES table and add the column TOTSAL with data type
--- NUMBER(9,2).
ALTER TABLE emp_cop
ADD totsal NUMBER(9,2);

--- c. Create a script file to print the name, type, and status of all objects
--- that are invalid.
SELECT object_name, object_type, status
FROM user_objects 
WHERE status = 'INVALID'
ORDER BY object_type;

--- d. Create a procedure called COMPILE_OBJ that recompiles all invalid
--- procedures, functions, and packages in your schema. 
--- Make use of the ALTER_COMPILE procedure in the DBMS_DDL package.
--- Execute the COMPILE_OBJ procedure.
CREATE OR REPLACE PROCEDURE compile_obj IS
-- v_schema should be a parameter but, in this case, it's hard-coded in
  v_schema VARCHAR2(10) := 'sqluser35';
  CURSOR c_invalid_objects IS
    SELECT object_type, object_name
    FROM user_objects 
    WHERE status = 'INVALID';
BEGIN
  FOR inv_obj IN c_invalid_objects LOOP
    DBMS_DDL.ALTER_COMPILE(inv_obj.object_type,
                           v_schema,
                           inv_obj.object_name);
  END LOOP;
END compile_obj;
/

EXECUTE compile_obj();

--& e. Run the script file that you created in question 3c again and check the
--- status column value. Do you still have INVALID objects? If you do, why are
--- they INVALID?
/*
Yes, there are still invalid objects. These objects are still invalid because
they use bad bind variables. These bind variables are probably considered "bad"
by the compiler because of a referencing error (i.e. the bind variables no
longer exist because they were probably only created around the session that
the procedure was last updated/compiled successfully).
*/
