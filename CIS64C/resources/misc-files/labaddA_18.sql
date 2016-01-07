ALTER TABLE employees
  ADD (sal_limit_indicate  VARCHAR2(3) DEFAULT 'NO'
       CONSTRAINT emp_sallimit_ck CHECK
      (sal_limit_indicate IN ('YES', 'NO')));
