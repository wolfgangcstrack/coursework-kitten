-- Intro to PL/SQL
-- Lab Assignment 13, Practice 15
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 17 November 2015
-- Date Handed In: 17 November 2015

-----

----- 1. Create a table called PERSONNEL by executing the script file
----- lab15_1.sql. The table contains the [attributes and data types listed in
----- the assignment specification].

-- run lab15_1.sql here

-----

----- 2. Insert two rows into the PERSONNEL table, one each for employees 2034
----- and 2035. Use the empty function for the CLOB, and provide NULL as the
----- value for the BLOB.
INSERT INTO personnel VALUES(2034, 'Strack', EMPTY_CLOB(), NULL);
INSERT INTO personnel VALUES(2035, 'Singh',  EMPTY_CLOB(), NULL);
COMMIT;

-----

----- 3. Examine and execute the script lab15_3.sql. The script creates a table
----- named REVIEW_TABLE. This table contains annual review information for
----- each employee. The script also contains two statements to insert review
----- details for two employees.

-- run lab15_3.sql here

-----

----- 4. Update the PERSONNEL table.
--- a. Populate the CLOB for the first row, using the following subquery in a
--- SQL UPDATE statement:
/*
SELECT ann_review 
FROM review_table
WHERE employee_id = 2034;
*/
UPDATE personnel
  SET review = (
    SELECT ann_review
    FROM review_table
    WHERE employee_id = 2034
  )
  WHERE id = 2034;
COMMIT;

--& b. Populate the CLOB for the second row, using PL/SQL and the DBMS_LOB
--- package. Use the following SELECT statement to provide a value. 
/*
SELECT ann_review 
FROM review_table
WHERE employee_id = 2035;
*/
DECLARE
  v_clob personnel.review%TYPE;
  v_value review_table.ann_review%TYPE;
  v_length NUMBER;
BEGIN
  SELECT review
  INTO v_clob
  FROM personnel
  WHERE id = 2035
  FOR UPDATE;

  SELECT ann_review
  INTO v_value
  FROM review_table
  WHERE employee_id = 2035;

  v_length := LENGTH(v_value);
  DBMS_LOB.WRITE(v_clob, v_length, 1, v_value);
  COMMIT;
END;
/

-----

----- 5. Create a procedure that adds a locator to a binary file into the
----- PICTURE column of the COUNTRIES table. The binary file is a picture of
----- the country. The image files are named after the country IDs. You need to
----- load an image file locator into all rows in Europe region (REGION_ID = 1)
----- in the COUNTRIES table. The DIRECTORY object name that stores a pointer
----- to the location of the binary files is called COUNTRY_PIC. This object is
----- already created for you.

-- Cannot locate the LOG_FILES and COUNTRY_PIC directories.
