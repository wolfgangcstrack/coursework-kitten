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