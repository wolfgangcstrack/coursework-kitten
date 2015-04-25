# CIS29-Lab1-Bitsets
CIS29 Spring Quarter 2015 - Lab 1, Bitsets

## Assignment Description
The data file (Morse.bin) in the Lab Materials folder is a binary data file. The data file is encoded using the first data encryption scheme called "Morse Code".  See Morse Code encoding scheme listed below.  The Morse Code data has been doubly encrypted to map to the ANSI Standard.  This assignment is to decrypt the Morse.bin data.

Encryption Scheme:<br>
00 = space<br>
01 = dash<br>
10 = dot<br>
11 = word separator<br>
<br>
Example<br>
Text:  "Morse Code"<br>
Morse Code:	"-- --- ._. ... . /-.-. --- -.. -/"<br>
Ascii Encryption:	"QRb¢6a"<br>
<br>
Encryption Excerpt:  QR<br>
<br>
Q = 81 = 01010001<br>
01 = -<br>
01 = -<br>
00 = space<br>
01 = -<br>
<br>
R = 82 = 01010010<br>
01 = -<br>
01 = -<br>
00 = space<br>
10 = .<br>
<br>
The Morse Codes<br>
A	· −<br>
B	− · · ·<br>
C	− · − · <br>
D	− · · <br>
E	· <br>
F	· · − · <br>
G	− − · <br>
H	· · · · <br>
I	· · <br>
J	· − − − <br>
K	− · − <br>
L	· − · · <br>
M	− − <br>
N	− · <br>
O	− − − <br>
P	· − − · <br>
Q	− − · − <br>
R	· − · <br>
S	· · · <br>
T	− <br>
U	· · − <br>
V	· · · − <br>
W	 − − <br>
X	− · · − <br>
Y	− · − − <br>
Z	− − · · <br>
0	− − − − − <br>
1	· − − − − <br>
2	· · − − − <br>
3	· · · − − <br>
4	· · · · − <br>
5	· · · · · <br>
6	− · · · · <br>
7	− − · · · <br>
8	− − − · · <br>
9	− − − − · <br>
[']	· − − − − ·  <br>
[@]	· − − · − ·  <br>
[:]	− − − · · ·  <br>
[,]	− − · · − − <br>
[$]	· · · − · · −  <br>
[=]	− · · · −  <br>
[!]	− · − · − −  <br>
[.] · − · − · − <br>
[?] · · − − · ·  <br>
["] · − · · − ·  <br>
<br>
Use Bitsets and Vectors as your primary data structures for this assignment.
<br>

**Author:** Wolfgang C. Strack

**Compiler:** Windows 8 Visual C++ 2013
