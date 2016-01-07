-- Intro to PL/SQL
-- Lab Assignment 9, Practice 11
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 2 November 2015
-- Date Handed In: 3 November 2015

-----

----- Suppose you have lost the code for the NEW_EMP procedure and the
----- VALID_DEPTID function that you created in lesson 10. (If you did not
----- complete the practices in lesson 10, you can run the solution scripts to
----- create the procedure and function.) Create an iSQL*Plus spool file to
----- query the appropriate data dictionary view to regenerate the code.
--- Hint:
--- SET -- options ON|OFF
--- SELECT -- statement(s) to extract the code
--- SET -- reset options ON|OFF
----- To spool the output of the file to a .sql file from iSQL*Plus, select the
----- Save option for the Output and execute the code.

SET ECHO OFF HEADING OFF FEEDBACK OFF VERIFY OFF;
COLUMN LINE NOPRINT;
SET PAGESIZE 0;

-- I use the command line instead of a GUI-based client for PL/SQL so I do not
-- have the option of pressing a button to save output to a file. With that said,
-- I believe the SQL SPOOL command does the job albeit the fact that it outputs
-- the query along with the query results.
SPOOL 11_managing_subprograms_OUTPUT.sql
  SELECT text
  FROM user_source
  WHERE name = 'NEW_EMP'
  ORDER BY line;

  SELECT text
  FROM user_source
  WHERE name = 'VALID_DEPTID'
  ORDER BY line;
SPOOL OFF;
