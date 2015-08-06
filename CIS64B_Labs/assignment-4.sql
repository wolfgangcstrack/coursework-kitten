-- Oracle SQL
-- Lab Assignment 4
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 16 July 2015
-- Date Handed In: 16 July 2015

----------

-- #1. Display the manager number and the salary of the lowest paid
-- employee for that manager. Exclude anyone whose manager is not known.
-- Exclude any groups where the minimum salary is less than $1000. Sort
-- the output in descending order of salary.
SELECT DISTINCT e.mgr AS "Manager #", e1.sal AS "Lowest Salary"
FROM emp e INNER JOIN emp e1 ON (e.mgr = e1.mgr)
WHERE e1.sal = (SELECT MIN(e2.sal) FROM emp e2 WHERE e2.mgr = e1.mgr)
AND e1.sal > 1000
AND e.mgr IS NOT NULL
ORDER BY e.mgr;
-- Instructor Note: condition should be HAVING MIN(sal) >= 1000

-- SELECT DISTINCT e.mgr AS "Manager #", MIN(e1.sal) AS "Lowest Salary"
-- FROM emp e INNER JOIN emp e1
-- ON (e.mgr = e1.mgr)
-- WHERE e1.sal > 1000
-- AND e.mgr IS NOT NULL
-- GROUP BY e.mgr
-- ORDER BY e.mgr;

----------

-- #2. Write a query to display the department name, location name, number
-- of employees, and the average salary for all employees in that
-- department. Label the columns dname, loc, Number of People, and Salary, respectively. 
SELECT d.dname AS "Dept. Name",
       d.loc AS "LOC",
       COUNT(e.deptno) AS "# of people",
       TRUNC(AVG(e.sal), 2) AS "Avg. Salary"
FROM dept d INNER JOIN emp e ON (d.deptno = e.deptno)
GROUP BY d.dname, d.loc;

----------

-- #3. Write a query to display department names with salary grade,
-- minimum salary and average commission. For departments with null
-- commission, you should display 0. (salgrade table can be used for
-- getting salary grade). 

-- select empno, ename, deptno, sal, comm from emp;
SELECT d.dname AS "Dept. Name",
       sg.grade AS "Salary Grade",
       e.sal AS "Lowest Salary",
       TRUNC(AVG(NVL(e2.comm, 0)), 2) AS "Average Commission"
FROM salgrade sg
    INNER JOIN emp e
        ON (e.sal BETWEEN sg.losal AND sg.hisal)
    INNER JOIN dept d
        ON (d.deptno = e.deptno)
    INNER JOIN emp e2
        ON (d.deptno = e2.deptno)
WHERE e.sal = (select MIN(e1.sal) from emp e1 WHERE e1.deptno = e.deptno)
GROUP BY d.deptno, d.dname, sg.grade, e.sal;

----------

-- #4. What is difference between COUNT(*), COUNT(col_name),
-- COUNT(DISTINCT(col_name)), COUNT(ALL(col_name))? Explain with examples.
/*
The difference is that COUNT(*) can count all the rows in a table whereas,
for example, COUNT(emp.comm) will only count the number of rows where
emp.comm is not null. In other words, the count will be less than COUNT(*)
if there are any null values in the emp.comm column.
*/ -- For example:
SELECT COUNT(*) FROM emp; -- counts all rows
SELECT COUNT(comm) FROM emp; -- counts only non-null rows
/* #4 cont...
The same concept applies to COUNT(DISTINCT(col_name)) and COUNT(ALL(col_name)).
By default, COUNT(emp.job) is the same as COUNT(ALL(emp.job)) and so the count
returned would be the same. COUNT(DISTINCT(emp.job)) will return a number less than
or equal to the number returned by COUNT(ALL(emp.job)) because the DISTINCT
function omits any duplicate values.
*/ -- For example:
SELECT COUNT(job) FROM emp;
SELECT COUNT(ALL(job)) FROM emp; -- same as the previous query
SELECT COUNT(DISTINCT(job)) FROM emp;
-- ^omits duplicates; therefore the returned result will
-- be less than or equal to the previous query's result

----------

-- #5. Display the employee number, name, salary, and salary increase by
-- 15% expressed as a whole number. Label the column New Salary. 
SELECT empno AS "Emp. #",
       ename AS "Emp. Name",
       sal AS "Salary",
       TRUNC(sal+sal*0.15) AS "New Salary (15% increase)"
FROM emp;
