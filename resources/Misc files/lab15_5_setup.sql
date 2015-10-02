-- Purpose: Set up the DIRECTORY object for this lesson.
-- This script MUST be executed before you can demo the BFILENAME function 
-- and before the students can complete the practice.
-- Steps:   Execute this script
--  ***   You must login to the Oracle host machine and 
-- detemine the home directory path of the instructor account.
--  ***  You must fill in the location of the COUNTRY_PIC directory on the SERVER
--  ***  using the path detemined from the previous step.
--  ***  You must fill in the location of the LOG_FILES directory on the SERVER
--  ***  using the path detemined from the previous step.
--  ***  connect as system/manager@    

--fill in database connection
CREATE OR REPLACE DIRECTORY LOG_FILES AS '$HOME/LOG_FILES'; 

-- fill in file location on the server between the quotes
CREATE OR REPLACE DIRECTORY COUNTRY_PIC AS '$HOME/COUNTRY_PIC'; 

GRANT READ ON DIRECTORY LOG_FILES TO PUBLIC;
GRANT READ ON DIRECTORY COUNTRY_PIC TO PUBLIC;
