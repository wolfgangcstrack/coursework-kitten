-- Oracle SQL
-- Lab Assignment 3
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 12 July 2015
-- Date Handed In: 12 July 2015

----------

-- #1. Write a query to display employee number, employee name, hiredate,
-- manager's name for those employees, whose manager's name starts with K
-- or M or S. Label the columns Employee Number, Employee Name, Hiredate, Mgr Name.
SELECT e1.empno AS "Emp. Number", 
        e1.ename AS "Emp. Name",
        e1.hiredate AS "Hiredate", 
        e2.ename AS "MGR Name"
FROM emp2 e1, emp2 e2
WHERE (e1.mgr IS NOT NULL AND e1.mgr = e2.empno)
  AND
  (
    trim(upper(e2.ename)) LIKE upper('K%') 
    OR
    trim(upper(e2.ename)) LIKE upper('M%')
    OR
    trim(upper(e2.ename)) LIKE upper('S%')
  )
;

----------

-- #2. Create a query that will display the employee name, department
-- number, department name and all the employees that work in the same
-- department as a given employee. Give each column an appropriate label.
-- SELECT e.ename AS "Emp. Name",
--         d.deptno AS "Dept. #",
--         d.dname AS "Dept. Name"
-- FROM emp2 e, dept d
-- WHERE e.deptno = d.deptno(+)
-- ORDER BY d.dname, e.ename;

-- ANSWER:
select e.ename "Emp Name", c.ename "Co-worker", e.deptno "Dept No", d.dname "Dept Name"
from emp e, emp c, dept d
where e.deptno = d.deptno
and e.deptno = c.deptno
and e.empno <> c.empno;

----------

-- #3. Write a query to display the department name, location of all
-- employees who are clerks. 
SELECT e.ename AS "Emp. Name", e.job AS "Emp. Job", d.dname AS "Dept. Name", d.loc AS "Location"
FROM emp2 e, dept d
WHERE trim(upper(e.job)) = 'CLERK' AND e.deptno = d.deptno(+)
ORDER BY d.loc, d.dname;

----------

-- #4. Insert a new row into the department table: department number = 50,
-- department name = training, location = San Francisco. Now create a
-- query to display all the employees in department number 20 and 50.
-- Columns to be displayed are emp number, emp name, dept name, dept location. 
INSERT INTO dept VALUES (50, 'training', 'San Francisco');

-- SELECT e.empno AS "Emp. #", e.ename AS "Emp. Name", e.deptno,
--         d.dname AS "Dept. Name", d.loc AS "Location"
-- FROM emp2 e, dept d
-- WHERE e.deptno(+) = d.deptno AND d.deptno IN (20, 50);

-- ANSWER:
select e.empno "Emp No", e.ename "Emp Name", d.deptno "Dept No", d.loc "Location"
from emp e, dept d 
where e.deptno(+)=d.deptno and (d.deptno=20 or d.deptno=50);

----------

-- #5. Insert a new row into the emp table - you can choose any values for
-- the fields, but department number should be null. Now create a query to
-- display all the employees and all the departments, using joins.
INSERT INTO emp2 VALUES (7777, 'WOLFGANG', 'EMPEROR', NULL, '7-JULY-1977', 77777, NULL, NULL);

-- SELECT e.empno AS "Emp. #", e.ename AS "Emp. Name", e.deptno AS "Dept. #",
--         d.dname AS "Dept. Name", d.loc "Location"
-- FROM emp2 e, dept d
-- WHERE e.deptno = d.deptno(+);

-- ANSWER:
select e.ename "Emp Name", d.dname "Dept Name"
from emp2 e full outer join dept d
on e.deptno=d.deptno;
