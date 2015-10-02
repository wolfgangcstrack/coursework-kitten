REM   Package specification with sample procedure specifications

CREATE OR REPLACE PACKAGE mgr_constraints_pkg
IS
  PROCEDURE check_president;
  PROCEDURE check_mgr;
  PROCEDURE new_location
    (p_deptid  IN  departments.department_id%TYPE);
  new_mgr   employees.manager_id%TYPE := NULL;
END mgr_constraints_pkg;
/

REM   Package body -- fill in the code for the procedures

CREATE OR REPLACE PACKAGE BODY mgr_constraints_pkg 
IS
  PROCEDURE check_president
    IS
    
  END check_president;

  PROCEDURE check_mgr
  IS
     
  END check_mgr;

  PROCEDURE new_location
  (p_deptid   IN  departments.department_id%TYPE)
  IS
   
  END new_location;

END mgr_constraints_pkg;
/
