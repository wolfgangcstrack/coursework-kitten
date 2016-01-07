CREATE OR REPLACE                                                               
PROCEDURE new_emp                                                               
  (p_lname   employees.last_name%TYPE,                                          
   p_fname   employees.first_name%TYPE,                                         
   p_email   employees.email%TYPE,                                              
   p_job     employees.job_id%TYPE         DEFAULT 'SA_REP',                    
   p_mgr     employees.manager_id%TYPE     DEFAULT 145,                         
   p_sal     employees.salary%TYPE         DEFAULT 1000,                        
   p_comm    employees.commission_pct%TYPE DEFAULT 0,                           
   p_deptid  employees.department_id%TYPE  DEFAULT 30)                          
IS                                                                              
BEGIN                                                                           
 IF valid_deptid(p_deptid) THEN                                                 
    INSERT INTO employees(employee_id, last_name, first_name, email,            
      job_id, manager_id,hire_date, salary, commission_pct, department_id)      
    VALUES (employees_seq.NEXTVAL, p_lname, p_fname, p_email,                   
            p_job, p_mgr, TRUNC (SYSDATE, 'DD'), p_sal, p_comm, p_deptid);      
 ELSE                                                                           
  RAISE_APPLICATION_ERROR (-20204, 'Invalid department ID.  Try again.');       
 END IF;                                                                        
END new_emp; 
/
