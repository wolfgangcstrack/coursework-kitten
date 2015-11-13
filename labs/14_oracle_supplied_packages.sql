-- Intro to PL/SQL
-- Lab Assignment 12, Practice 14
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 13 November 2015
-- Date Handed In: 13 November 2015

-----

----- 1.
--- a. Create a DROP_TABLE procedure that drops the table specified in the
--- input parameter. Use the procedures and functions from the supplied
--- DBMS_SQL package.
CREATE OR REPLACE PROCEDURE drop_table(p_table_name IN VARCHAR2)
IS
  c_dbms_cursor INTEGER;
  v_temp NUMBER;
BEGIN
  c_dbms_cursor := DBMS_SQL.OPEN_CURSOR;
  DBMS_SQL.PARSE(c_dbms_cursor, 'DROP TABLE '||p_table_name, DBMS_SQL.NATIVE);
  v_temp := DBMS_SQL.EXECUTE(c_dbms_cursor);
  DBMS_SQL.CLOSE_CURSOR(c_dbms_cursor);
END drop_table;
/

--- b. To test the DROP_TABLE procedure, first create a new table called
--- EMP_DUP as a copy of the EMPLOYEES table. 
CREATE TABLE emp_dup AS
  SELECT * FROM employees;

--- c. Execute the DROP_TABLE procedure to drop the EMP_DUP table.
EXECUTE drop_table('emp_dup');

-----

----- 2.
--- a. Create another procedure called DROP_TABLE2 that drops the table
--- specified in the input parameter. Use the EXECUTE IMMEDIATE statement.
CREATE OR REPLACE PROCEDURE drop_table2(p_table_name IN VARCHAR2) IS
BEGIN
  EXECUTE IMMEDIATE('DROP TABLE ' || p_table_name);
END drop_table2;

--- b. Repeat the test outlined in steps 1-b and 1-c.
CREATE TABLE emp_dup AS
  SELECT * FROM employees;

EXECUTE drop_table('emp_dup');

-----

----- 3.
--- a. Create a procedure called ANALYZE_OBJECT that analyzes the given object
--- that you specified in the input parameters. Use the DBMS_DDL package, and
--- use the COMPUTE method.
CREATE OR REPLACE PROCEDURE analyze_object
  (p_object_type IN VARCHAR2,
   p_object_owner IN VARCHAR2,
   p_object_name IN VARCHAR2)
IS
  v_last_analyzed_date DATE;
BEGIN
  DBMS_DDL.ANALYZE_OBJECT(p_object_type, p_object_owner, p_object_name, 'COMPUTE');

  SELECT last_analyzed INTO v_last_analyzed_date
  FROM user_tables WHERE table_name = UPPER('EMPLOYEES');

  DBMS_OUTPUT.PUT_LINE(
    'Last analysis date of ' || p_object_name ||
    ' updated to: ' || v_last_analyzed_date
  );
END analyze_object;
/

--- b. Test the procedure using the EMPLOYEES table. Confirm that the
--- ANALYZE_OBJECT procedure has run by querying the LAST_ANALYZED column in
--- the USER_TABLES data dictionary view.
SET SERVEROUTPUT ON;
EXECUTE analyze_object('TABLE', 'sqluser35', 'employees');

-----

----- 4.
--- a. Schedule ANALYZE_OBJECT by using DBMS_JOB. Analyze the DEPARTMENTS table,
--- and schedule the job to run in five minutes time from now. (To start the
--- job in five minutes from now, set the parameter NEXT_DATE = 5/(24*60) = 1/288.)
SET SERVEROUTPUT ON;

VARIABLE v_dbms_job_no NUMBER;

BEGIN
  DBMS_JOB.SUBMIT(
    :v_dbms_job_no,
    'analyze_object(''TABLE'', ''sqluser35'', ''departments'');',
    SYSDATE + (5 / (24 * 60))
  );

  DBMS_OUTPUT.PUT_LINE('Job no.: ' || :v_dbms_job_no);
END;
/

--- b. Confirm that the job has been scheduled by using USER_JOBS.
SELECT job FROM user_jobs WHERE job = :v_dbms_job_no;

-----

----- 5. Create a procedure called CROSS_AVGSAL that generates a text file
----- report of employees who have exceeded the average salary of their
----- department. The partial code is provided for you in the file lab14_5.sql.
--- a. Your program should accept two parameters. The first parameter
--- identifies the output directory. The second parameter identifies the text
--- file name to which your procedure writes. 
--& b. Your instructor will inform you of the directory location. When you
--- invoke the program, name the second parameter sal_rptxx.txt where xx stands
--- for your user number, such as 01, 15, and so on.
--& c. Add an exception handling section to handle errors that may be
--- encountered from using the UTL_FILE package.
---Sample output from this file follows:
/*
EMPLOYEES OVER THE AVERAGE SALARY OF THEIR DEPARTMENT: 

REPORT GENERATED ON 26-FEB-01

Hartstein 20 $13,000.00

Raphaely 30 $11,000.00

Marvis 40 $6,500.00

...

*** END OF REPORT ***
*/

CREATE OR REPLACE PROCEDURE cross_avgsal
 (p_filedir IN VARCHAR2,  p_filename1 IN VARCHAR2)
IS
 v_fh_1 UTL_FILE.FILE_TYPE;
 CURSOR cross_avg IS
   SELECT last_name, department_id, salary
     FROM employees outer
     WHERE salary > (SELECT AVG(salary)
         FROM   employees inner
             GROUP BY outer.department_id)
   ORDER BY department_id;
BEGIN
  v_fh_1 := UTL_FILE.FOPEN(p_filedir, p_filename1,'w');
 
  UTL_FILE.PUTF(v_fh_1, 'Employees who earn more than average salary: \n');
  UTL_FILE.PUTF(v_fh_1, 'REPORT GENERATED ON  %s\n\n', SYSDATE);
  FOR v_emp_info IN cross_avg LOOP
    UTL_FILE.PUTF(v_fh_1, '%s   %s \n', 
    RPAD(v_emp_info.last_name, 30, ' '),
    LPAD(TO_CHAR(v_emp_info.salary, '$99,999.00'), 12, ' '));
  END LOOP;  
  UTL_FILE.NEW_LINE(v_fh_1);
  UTL_FILE.PUT_LINE(v_fh_1, '*** END OF REPORT ***');
  UTL_FILE.FCLOSE(v_fh_1);

EXCEPTION
  WHEN UTL_FILE.INVALID_FILEHANDLE THEN
    RAISE_APPLICATION_ERROR (-20001, 'Invalid File.');
    UTL_FILE.FCLOSE_ALL;
  WHEN UTL_FILE.WRITE_ERROR THEN
    RAISE_APPLICATION_ERROR (-20002,
                             'Unable to write to file');
    UTL_FILE.FCLOSE_ALL;
END cross_avgsal;
/

EXECUTE cross_avgsal('/home/student/vulfgang/doge', 'sal_rpt35.txt');