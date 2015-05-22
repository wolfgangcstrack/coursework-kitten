#!/usr/bin/perl
#
# Author: Wolfgang C. Strack

use CGI qw( :standard );
use CGI::Carp qw(warningsToBrowser fatalsToBrowser);

print header;
print start_html("CS149 Final Project");
print h1("CS149 Final Project Online Presentation");
print h2("Author: Wolfgang C. Strack<br>
	Topic: New Module for Multimedia Festival Project");

print <<endBody;

<p>
I decided on completing the class project given mostly because I could not really come up with anything<br>
worthwhile that required use of databases. With that said, I did find the given class project to be <br>
worthwhile and interesting despite not being my own idea. For those who did not do the class project and/or <br>
do not know what it is about, I quote the project background:<br>

<blockquote><i>
Ohlone's Multimedia Festival, which runs every Spring, has been using a program,<br>
mostly written by students from the perl class, over the years.<br>
<br>
There has been a request from those running the festival to make available an<br>
option to allow the system admin choosing what fields are displayed on the screen.<br>
<br>
Right now, all the fields show up under the options 'Generic list of projects<br>
(show all)' and 'Sort and view all records', except for one option, called<br>
'Simple View', which only shows 4 fields.<br>
<br>
<b>The task for this final project is to</b> add code to this program, which will allow<br>
a system admin to design their own view of the database by allowing selecting<br>
which fields will print.<br>
</i></blockquote>

With that said, I will now explain the program and code, both of which I've provided links here:<br>
<br>
<a href="http://projects.cs.ohlone.edu/~gen57/final_project/mm_projects.cgi">Multimedia Festival Database</a><br>
<br>
<a href="http://projects.cs.ohlone.edu/~gen57/final_project/mm_projects.cgi.txt">Link to code</a><br>
<br>
<h3>sub make_modifiedView_form</h3>
<blockquote><font face="courier" size="2">
See code with link above. Use Ctrl-F to search for "sub make_modifiedView_form"
</font></blockquote>
This subroutine is called when the user chooses "Modified View" from the main menu. As its name implies, it<br>
prints a form for "Modified View," the new module in this project, that gives you a list of fields represented<br>
as checkboxes. The user can choose the fields they want printed out by checking their respective checkboxes.<br>
This subroutine takes advantage of the CGI function checkbox_group to print the group of checkboxes for the<br>
fields. This group input type takes a name for getting its values with param(), and it also takes values and<br>
labels parameters which must be references to hashes that hold the respective values. I've passed the reference<br>
to the global mview_menu hash defined near the top of the file and you can see that this hash holds both the<br>
keys (which correspond to the actual columns in the database) and strings to be printed for the checkboxes.<br>
<br>
<h3>sub modifiedView</h3>
<blockquote><font face="courier" size="2">
See code with link above. Use Ctrl-F to search for "sub modifiedView"
</font></blockquote>
This subroutine is called in main after the user presses the "Display Selected Fields" button that <br>
make_modifiedView_form prints out. It uses param() to retrieve the checked fields from the previous screen.<br>
The very first thing it does after that is checking whether or not the user checked any fields at all. If no<br>
fields were chosen, a message prints to notify the user.<br>
<br>
The next section of this code involves taking the array of checked_fields and appending all its values to the<br>
string variable strCheckedFields. This is done so that strCheckedFields can be passed to the existing<br>
subroutines &load_all_records and &load_partial_records as well as the new subroutine &modified_insertRecord.<br>
<br>
After this, all the records in the table "mm" are loaded for getting other records from "mm_projects" right<br>
after. &load_partial_records is called for "mm_projects" to get all the checked fields in strCheckedFields.<br>
Once these records are loaded into the global rows array, they are then pushed as array references onto the<br>
full_rows array. Once full_rows has been filled with all the retrieved records, they are then inserted into<br>
the table "sort_criteria_full" (not "sort_criteria" which is used by &simpleView).<br>
<br>
The rest of this subroutine then involves loading the records in "sort_criteria_full" and then printing them<br>
out into a table. The very last step truncates sort_criteria_full, meaning that the data just loaded is then<br>
wiped clean.<br>
<br>
<h3>sub modified_insertRecord</h3>
<blockquote><font face="courier" size="2">
See code with link above. Use Ctrl-F to search for "sub modified_insertRecord"
</font></blockquote>
This subroutine, as mentioned previously, simply involves inserting the user-checked fields into the table<br>
"sort_criteria_full". Briefly put, all that happens is an SQL statement is prepared from the parameters and<br>
then executed. This subroutine was based mostly off of simple_insertRecord, which inserts into<br>
"sort_criteria" instead.<br>
<br>
<h3>Changes to main</h3>
<blockquote><font face="courier" size="2">
See code with link above, main is located near the top of the file.
</font></blockquote>
Changes to main include modifying the first if statement, which checks the value of param("LAST") to see what<br>
option the user has chosen in the main menu. I also changed the global menu array located near the top of the<br>
file to include "Modified View" in the menu; all accesses to this array's values were updated as well.<br>
<br>
Finally, in the same if statement, I added a subsequent elsif statement to check if param("LAST") equals<br>
"Modified View" and, if it does, call &modifiedView. In other words, param("LAST") can only equal<br>
"Modified View" when the user is currently on the menu for "Modified View", created by<br>
make_modifiedView_form.<br>
</p>

endBody

print end_html;