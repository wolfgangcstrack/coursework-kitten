-- Intro to PL/SQL
-- Lab Assignment 1, Question 4
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 02 October 2015
-- Date Handed In: 02 October 2015

VARIABLE vchar VARCHAR2(50);
VARIABLE vnum NUMBER;

DECLARE
  v_char VARCHAR2(50);
  v_num NUMBER;
BEGIN
  :vchar := '42 is the answer';
  :vnum := TO_NUMBER(SUBSTR(:vchar, 1, 2));
  v_char := :vchar;
  v_num := :vnum;
  DBMS_OUTPUT.PUT_LINE(v_char);
  DBMS_OUTPUT.PUT_LINE(v_num);
END;
/
