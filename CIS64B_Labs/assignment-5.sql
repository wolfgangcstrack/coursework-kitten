-- Oracle SQL
-- Lab Assignment 5
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 22 July 2015
-- Date Handed In: 22 July 2015

--------------------------------------------------

----- Question #1

-- #1a. Create a query that displays the employees names and indicates the
-- amounts of their salaries through asterisks. Each asterisk signifies
-- hundred dollars. Sort the data in descending order of salary. Label the
-- column EMPLOYEE_AND_THEIR_SALARIES. 
SELECT CONCAT(ename, RPAD(' ', (TRUNC(sal, -2) / 100 + 1), '*'))
          AS "EMPLOYEE_AND_THEIR_SALARIES"
FROM emp
ORDER BY sal DESC;

-- #1b. Display the employees name, username, hire date, salary and salary
-- review date, which is the first Monday after six months of service.
-- Label the column REVIEW. Format the dates to appear in the format
-- mm/dd/yy. Salary should be rounded. Username is first two letters of
-- the name in the lower case. 
SELECT ename AS "Name",
       LOWER(SUBSTR(TRIM(ename), 1, 2)) AS "Username",
       TO_CHAR(hiredate, 'MM/DD/YY') AS "Hiredate",
       ROUND(sal, 0) AS "Salary",
       TO_CHAR(NEXT_DAY(ADD_MONTHS(hiredate, 6), 'MONDAY'), 'MM/DD/YY') AS "REVIEW"
FROM emp;

-- #1c. Use subquery to display all employees, in department location
-- 'BOSTON' with a salary of greater than $1000. 
SELECT e.empno AS "Emp. #", e.ename AS "Emp. Name",
       d.deptno AS "Dept. #", d.loc AS "Location"
FROM emp e, dept d
WHERE d.deptno = e.deptno
      AND d.deptno IN (SELECT deptno FROM dept WHERE UPPER(loc) = UPPER('BOSTON'));

--------------------------------------------------

----- Question #2

-- #2a. Write a query to display the employee name, job, and hire date for
-- all employees who started between 01/01/81 to 12/31/81. Concatenate the
-- name and job together, separated by a space and comma, and label the
-- column Employees. 
SELECT (TRIM(ename) || ', ' || job) AS "Employees", hiredate
FROM emp
WHERE hiredate BETWEEN TO_DATE('01/01/1981', 'MM/DD/YYYY') AND TO_DATE('12/31/1981', 'MM/DD/YYYY');

-- #2b. Explain the usage of correlated subqueries, inline views with an example.
/* -- Correlated Subqueries:
Correlated subqueries are simply subqueries that reference the table in
the outer query, such as in the example below. They are best used for when
the subquery needs to answer a problem with multiple parts and that answer
depends on the results of the outer query.
In the example below, the subquery's d2.deptno depends on the outer
query's e.deptno; therefore, the outer query must be executed first in
order to provide values for the correlated subquery.
Note: while the example below demonstrates correlated subqueries, it can
be rewritten to not have to use any correlated subqueries.
*/
SELECT e.empno, e.deptno, e.ename, d1.loc
FROM emp e, dept d1
WHERE d1.loc = (SELECT d2.loc FROM dept d2 WHERE d2.deptno = e.deptno);
/* -- Inline Views:
Inline views are subqueries in the FROM statement rather than in the WHERE
or HAVING statements. It is commonly used to simplify queries that rely on
complex JOIN operations and/or condensing several separate queries into a
single query.
In the example below, notice that the subquery replaces the table name in
the FROM statement as an inline view and the outer query references a
value from the inline view.
Note: again, while the example below demonstrates inline views, it can be
rewritten to not have to use any inline views.
*/
SELECT e.empno, e.ename, dept_info
FROM emp e,
     (
      SELECT UPPER(TRIM(dname) || ' - ' || TRIM(loc))
                AS dept_info,
             deptno
      FROM dept
     ) d
WHERE e.deptno = d.deptno;
