-- Oracle SQL
-- Lab Assignment 2
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 8 July 2015
-- Date Handed In: 8 July 2015

----------

-- 1a. Write a simple query to display the name, job, hire date and
-- employee number of each employee from the emp table.
SELECT ename, job, hiredate, empno FROM emp;

-- 1b. Now, display all employees in the emp table including all columns.
SELECT * FROM emp;

-- 1c. Now rewrite the query to display names of all employees, making
-- sure that two employees with same name don't appear twice in the result set.
SELECT DISTINCT ename FROM emp;

----------

-- 2. Write a query to add a record to the emp table:
-- EMPNO: 1456  ENAME: John Smith  JOB: Analyst  SAL: 2000  HIREDATE: 1/1/02  COMM:  DEPTNO: 20  MGR: 7566
INSERT INTO emp VALUES (1456, 'John Smith', 'Analyst', 7566, '1-JAN-2002', 2000, NULL, 20);

----------

-- 3. Show how will you modify the above record to reflect SAL = 3000
UPDATE emp
SET sal = 3000
WHERE empno = 1456;

----------

-- 4. Write a SQL statement to show the employee number, employee name,
-- hiredate of employees where name has 2 L's.  Now from the above result
-- set, display the same fields, for employees whose names end with "N".
SELECT empno, ename, hiredate
FROM emp
WHERE trim(upper(ename)) LIKE upper('%L%L%');

SELECT empno, ename, hiredate
FROM emp
WHERE trim(upper(ename)) LIKE upper('%N');

----------

-- 5. Display all the fields of dept table, where location is BOSTON.
SELECT * FROM dept WHERE loc='BOSTON';

----------

-- 6. Display employee number, employee name, department number, job for
-- an employee who is not a manager and is not a clerk in department number 10.
SELECT empno, ename, deptno, job
FROM emp
WHERE empno NOT IN (SELECT mgr FROM emp WHERE mgr IS NOT NULL)
AND
NOT(job = 'CLERK' AND deptno = 10);

----------

-- 7a. Display all employees whose commission is greater than zero and salary is between 1000 and 3000.
SELECT empno, ename, sal, comm
FROM emp
WHERE comm > 0 AND sal BETWEEN 1000 AND 3000;

----------

-- 8a. Write a SQL statement to show employees, who don't have any managers.
SELECT empno, ename, mgr
FROM emp
WHERE mgr IS NULL;

-- 8b. Write a SQL statement to display employee number, employee name,
-- salary, manager for all employees, whose managers have employee numbers 7566, 7788
SELECT empno, ename, sal, mgr
FROM emp
WHERE mgr IN (7566, 7788);
