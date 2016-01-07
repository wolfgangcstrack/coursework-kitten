# CIS29-Lab3-Threading
CIS29 Spring Quarter 2015 - Lab 3, Threading Techniques
## Assignment Description
Lab 3

### Purpose: 

Use Threading Techniques

### Overview:

Threading is used to solve resource related problems.  In this case four threads are sharing a one simulated Robot.  An XML file (RobotData.XML) defines the commands sent to the Robot for each thread.  Each thread then is given access to the Robot.  The Robot accepts an XML command from the thread and executes it.

#### Robot:

The Robot.h file contains the source code to be included in your program to simulate the Robot.  Do not change the Robot code unless you find a bug.  If you find a bug, document it, and provide a fix.  If, however, you want to enhance the Robot, inherit from it and provide the enhancements.

#### RobotData.XML:

This XML file contains several hundred XML commands to be passed to the Robot to be executed by each thread one at a time.  Here is an XML excerpt:

              <command>

                             <robot>A3</robot>

                             <offon>On</offon>

                             <speed>Low</speed>

                             <horizontal>CounterClockwise</horizontal>

                             <vertical>Up</vertical>

                             <time>92</time>

              </command>            

* A3 = thread 3 of the four threads
* On = Command to turn on the Robot
* Low = Low speed
* CounterClockwise = direction for the Robot to go on the horizontal axis
* Up = direction for the Robot to go on the vertical axis
* 92 = number of milliseconds the Robot needs to perform these actions

#### Thread Process:
A.  Process the XML data file using your XML parsing utility from Lab2.  Distribute each XML node into one of 4 threading containers <robot>A3</robot> where: A1 = thread1, A2 = thread2, A3 = thread3, A4 = thread4.

B.  Start each thread to process the commands from the four XML containers. 

C.  Write a synchronized function to Execute each command.

D.  The Execute function executes the XML command by putting the current thread to sleep for <time>92</time> milliseconds, where 92 represents a value in a range from1 to 255 milliseconds.  This simulates the time necessary for the Robot to execute the command.
