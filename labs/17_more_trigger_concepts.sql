-- Intro to PL/SQL
-- Lab Assignment 15, Practice 17
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 24 November 2015
-- Date Handed In: 26 November 2015

-----

----- A number of business rules that apply to the EMPLOYEES and DEPARTMENTS
----- tables are listed below. Decide how to implement each of these business
----- rules, by means of declarative constraints or by using triggers. Which
----- constraints or triggers are needed and are there any problems to be
----- expected? Implement the business rules by defining the triggers or
----- constraints that you decided to create. A partial package is provided in
----- file lab17_1.sql to which you should add any necessary procedures or
----- functions that are to be called from triggers that you may create for the
----- following rules. (The triggers should execute procedures or functions
----- that you have defined in the package.)
----- (See lesson notes for the rest of the assignment specification)

-----
---------- PACKAGE DEFINITIONS:
-----
CREATE OR REPLACE PACKAGE mgr_constraints_pkg
IS
  PROCEDURE check_president;
  PROCEDURE check_mgr(p_mgr_id IN employees.employee_id%TYPE);
  PROCEDURE new_location(p_deptid IN departments.department_id%TYPE);
END mgr_constraints_pkg;
/

CREATE OR REPLACE PACKAGE BODY mgr_constraints_pkg 
IS
  -- Business Rule 2:
  PROCEDURE check_president IS
    v_count NUMBER;
  BEGIN
    SELECT COUNT(employee_id)
    INTO v_count
    FROM employees
    WHERE job_id = 'AD_PRES';

    IF v_count != 1 THEN
      RAISE_APPLICATION_ERROR(-20004, 'There can only be one president.');
    END IF;
  END check_president;

  -- Business Rule 3:
  PROCEDURE check_mgr(p_mgr_id IN employees.employee_id%TYPE)
  IS
    v_count NUMBER;
  BEGIN 
    SELECT COUNT(employee_id)
    INTO v_count
    FROM employees
    WHERE manager_id = p_mgr_id;

    IF v_count >= 15 THEN
      RAISE_APPLICATION_ERROR(-20003,
        'One employee cannot manage more than 15 employees.');
    END IF;
  END check_mgr;

  -- Business Rule 5:
  PROCEDURE new_location(p_deptid IN departments.department_id%TYPE)
  IS
    CURSOR c_emp IS
      SELECT salary FROM employees
      WHERE department_id = p_deptid
      FOR UPDATE OF salary NOWAIT;
  BEGIN
    FOR v_emp IN c_emp LOOP
      UPDATE employees
      SET salary = (salary * 0.02) + salary
      WHERE CURRENT OF c_emp;
    END LOOP;
  END new_location;
END mgr_constraints_pkg;
/

-----
---------- BUSINESS RULE IMPLEMENTATIONS (with tests):
-----
----- Business Rule 1:
CREATE OR REPLACE TRIGGER check_commissions
  BEFORE INSERT OR UPDATE OF job_id, commission_pct
  ON employees FOR EACH ROW
BEGIN
  IF :NEW.job_id IN ('SA_MAN', 'SA_REP') AND
     :NEW.commission_pct IS NULL
  THEN
    RAISE_APPLICATION_ERROR(-20002,
      'SA_MAN OR SA_REP must have commission_pct.');
  ELSIF :NEW.job_id NOT IN ('SA_MAN', 'SA_REP') AND
        :NEW.commission_pct IS NOT NULL
  THEN
    RAISE_APPLICATION_ERROR(-20003,
      'Employees neither SA_MAN OR SA_REP cannot have commission_pct.');
  END IF;
END check_commissions;
/

----- Business Rule 2:
CREATE OR REPLACE TRIGGER check_pres
  AFTER INSERT OR UPDATE OR DELETE ON employees
BEGIN
  -- defined below
  mgr_constraints_pkg.check_president();
END check_pres;
/

-- throws error
INSERT INTO
  employees(employee_id, first_name, last_name, email,
            job_id, hire_date, salary, department_id)
  VALUES(400, 'Alice', 'Harris', 'AHARRIS@example.com',
         'AD_PRES', SYSDATE, 20000, 20);


----- Business Rule 3:
CREATE OR REPLACE TRIGGER check_manager
  BEFORE INSERT OR UPDATE
  OF manager_id
  ON employees
  FOR EACH ROW
BEGIN
  mgr_constraints_pkg.check_mgr(:NEW.manager_id);
END check_manager;
/

-- 3i. (successful)
INSERT INTO
  employees(employee_id, first_name, last_name, email, job_id, salary,
            hire_date, manager_id, department_id, commission_pct)
  VALUES(401, 'Brian', 'Johnson', 'BJOHNSON@example.com', 'SA_MAN', 11000,
         SYSDATE, 100, 80, 0.5);
COMMIT;

-- 3ii. (throws error)
INSERT INTO
  employees(employee_id, first_name, last_name, email, job_id,
            salary, hire_date, manager_id, department_id)
  VALUES(402, 'Tony', 'Kellog', 'TKELLOG@example.com', 'ST_MAN',
         7500, SYSDATE, 100, 50);

----- Business Rule 4:
CREATE OR REPLACE TRIGGER check_salary
  BEFORE UPDATE ON employees FOR EACH ROW
BEGIN
  IF :NEW.salary < :OLD.salary THEN
    RAISE_APPLICATION_ERROR(-20005, 'Salary can only be increased.');
  END IF;
END check_salary;
/

-- throws error
UPDATE employees
SET salary = 4500
WHERE employee_id = 105;

----- Business Rule 5:
CREATE OR REPLACE TRIGGER update_salaries
  AFTER UPDATE
  OF location_id
  ON departments
  FOR EACH ROW
BEGIN
  mgr_constraints_pkg.new_location(:NEW.department_id);
END update_salaries;
/

-- tests:
SELECT department_id, salary
FROM employees WHERE department_id = 90
ORDER BY salary;

UPDATE departments
SET location_id = 1600
WHERE department_id = 90;
COMMIT;

SELECT department_id, salary
FROM employees WHERE department_id = 90
ORDER BY salary;
