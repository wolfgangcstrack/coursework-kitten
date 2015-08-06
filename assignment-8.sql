-- Oracle SQL
-- Lab Assignment 8
-- Wolfgang C. Strack
-- Student ID#: ****7355
-- Due Date: 5 August 2015
-- Date Handed In: 5 August 2015

--------------------------------------------------

-- 1. Setup a department, course within a department with 2 sections.
-- Section must have a location assigned. Produce a report showing the
-- department, its course and sections (with complete section information.)

-- For setting up Member:
INSERT INTO FeeSchedule VALUES (7777, NULL, NULL, NULL, NULL);
INSERT INTO Resident VALUES (9876, 'Valley Suites', 7777);
INSERT INTO Member VALUES (
  1987654320,
  'Sukhjit', 'Singh',
  '7777 Good Luck Avenue',
  'cislabs05@gmail.com',
  '510 123 4567',
  1,
  9876
);

-- For setting up Department/Course/Sections
INSERT INTO Location VALUES (77777, 'Cupertino, CA');
INSERT INTO Location VALUES (88888, 'ONLINE DISTANCE LEARNING');
INSERT INTO College VALUES (1234, 'De Anza College', '21250 Stevens Creek Blvd', '4088645300');
INSERT INTO Department VALUES (4321, 'Computer Information Systems', 77777, 1234);
INSERT INTO Course VALUES (5678, 64, 'Intro to SQL', NULL, 4321);
INSERT INTO Section VALUES (
  1025, 1, 5678, 77777,
  1800, 2000, '29-JUNE-2015', '05-AUG-2015',
  1987654320
);
INSERT INTO Section VALUES (
  1026, 2, 5678, 88888,
  NULL, NULL, '29-JUNE-2015', '05-AUG-2015',
  1987654320
);

-- Report:
SELECT d.name, c.name, s.*
FROM Department d, Course c, Section s
WHERE d.ID = c.Department_ID AND c.ID = s.Course_ID;

--------------------------------------------------

-- 2. Now register a student to a section and process student payment.
-- Produce a report showing student registration information, including
-- payment information.
INSERT INTO FeeSchedule VALUES (8888, '29-JUNE-2015', '05-AUG-2015', 25, 150.00);
INSERT INTO Member VALUES (
  201973557,
  'Lucky' 'Guy',
  '7777 Good Luck Avenue',
  'lucky@gmail.com',
  '510 987 6543',
  2,
  9876
);
INSERT INTO Payment VALUES (9765, 'CIS64B', 'REGISTRATION');
INSERT INTO StudentFee VALUES (
  1234567890,
  'N',
  201973557,
  1026,
  9765
);

-- Report:
SELECT m.ID, m.last_name, sf.*, p.*
FROM Member m, StudentFee sf, Payment p
WHERE m.ID = sf.Student_ID AND (p.ID = sf.Payment_ID);

--------------------------------------------------

-- 3. How can you improve your DB Schema further. Make at least 2
-- suggestions. 
/*
I expect that it's very likely that this database would hold multiple
colleges in multiple different locations. With that said, it's also very
likely that many queries to this database will regard those particular
fields. With all of that said, I think it would be a good idea to set
indexes for these fields, particularly location since it is a foreign key
for multiple other tables and will most likely be used in query conditions
frequently (IE select all the colleges located in a certain location, etc.).

Another proposal I might add to improve this DB schema would be to change
the data types for the Member table to more appropriate data types. By change,
I mean not only to possibly change the data type's actual type but to also
impose stricter restrictions when inserting values into the Member table. For
example, changing the Member.type field to NUMBER(1) and then adding a CHECK
clause to make sure that the number is either 1 or 2 (or any added types in the future).
*/