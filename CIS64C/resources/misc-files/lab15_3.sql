CREATE TABLE review_table
(employee_id number,
 ann_review VARCHAR2(2000));

INSERT INTO review_table
VALUES(2034,'Very good performance this year. Recommended to increase salary by $500');

INSERT INTO review_table
VALUES(2035,'Excellent performance this year. Recommended to increase salary by $1000');

commit;
