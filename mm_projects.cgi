#!/usr/bin/perl
# Exercise for Chapter 15
# Database: SQL and Perl Database Interface
# 
# Adapted for the multimedia festival
# 
# Author:  Jon Degallier
# Spring  2005
#
# Modified by Wolfgang Christian Strack
# - Perl Final Project, Winter 2015

#use warnings;
#use strict;
use DBI;
use DBD::mysql;
use CGI qw( :standard );
use CGI::Carp qw(warningsToBrowser fatalsToBrowser);

#BEGIN {
# use CGI::Carp qw(carpout);
# open(LOG, ">>final_project_error.log") or
# die("Unable to open mycgi-log: $!\n");
# carpout('LOG');
#}

######################################################################
#### initialize a few things              ####################
######################################################################

my $DSN = "DBI:mysql:mm_festival";
$mailprog = "/usr/sbin/sendmail";

$| = 1;   #clear buffers  
my $url = "";
our $menu = [     'Modified View',
                  'Generic list of projects (show all)',
                  'Sort and View All Records',
                  'Simple View',
                  'View scores (show accepted only)',
                  'Enter (create) a project record',
                  'Delete a project',
                  'Edit/Score a project (Judge)',
                  'Make Backup',
                  'Email to Accepted Projects',
                  'Email to Not Accepted Projects',
                  'Email Comments to Everyone' ,
                  'Test Email' ];  
our @menu = @$menu;
our $weight = 2;  #weight of criteria: below average 0*weight, average 1*weight, above 2*weight
@rubric = qw(0 1 2 3 4 5 6 7 8 9 10);
our @classes = qw(None mm102A mm102B mm103A mm103B mm104 mm105 mm106 mm107 mm110 mm114 mm115 mm116 
mm117 mm118 mm119 mm121A mm121B mm121C mm160 mm162 mm195 mm210);
our %class_name = ();
foreach (@classes) {
    $class_name{$_} = $_;
}
our @semester = qw(Fall Spring Summer);
our %semester_name = ();
foreach (@semester) {
    $semester_name{$_} = $_;
}
our @year = qw(2020 2019 2018 2017 2016 2015 2014 2013 2012 2011);
our %year_name = ();
foreach (@year) {
    $year_name{$_} = $_;
}
$mm_fields = "last, first, email, phone, ID_number";
$simple_mm_fields = "last, first, email";

$projects_fields = "category, title, softwware, class, semester, year, notes, accepted, criteria, ". 
    "tech_merit, creative, groups, group_names, description, " .
                "instructor, proj_permission, proj_url, ohlone_degree, proj_purpose, " .
                "proj_personal, proj_client, proj_non_prof, proj_donate, involvement, " .
    "highschool";
$simple_projects_fields = "category, title";

%mview_menu =(
        title => "title",
        category => "category",
        accepted => "accepted",
        notes => "notes",
        class => "class",
        groups => "groups",
        softwware => "software",
        semester => "semester",
        year => "year",
        criteria => "criteria",
        tech_merit => "technical merit",
        creative => "creative",
        email => "email",
        group_names => "group names",
        description => "description",
        instructor => "instructor",
        proj_permission => "project permission",
        proj_url => "project url",
        ohlone_degree => "ohlone degree",
        proj_purpose => "project purpose",
        proj_personal => "project personal",
        proj_client => "project client",
        proj_non_prof => "project non-profit",
        proj_donate => "project donate",
        involvement => "involvement",
        highschool => "highschool"
);

@yes_no = qw(Yes No);

######################################################################
#### main begin here                ####################
######################################################################

&print_header;

unless ( param ) {
    print h1( "Multimedia Festival Database" );
  &print_options;
        &print_link;
}
else {
    my $dbh = DBI->connect( $DSN, "mgs_user", "pa55word", { RaiseError => 1 } );
        #print "debug: LAST: ", param('LAST'), "\n";
        
    if ( param( "LAST" ) eq "MAIN" ) {
          my $selection = param( "selection" );
                #print "debug: selection is $selection\n";
                
                make_modifiedView_form( $dbh ) if ( $selection eq $menu[0] );
                view( $dbh ) if ( $selection eq $menu[1] );
                make_sort_form( $dbh ) if ( $selection eq $menu[2] );
                simpleView( $dbh ) if ( $selection eq $menu[3] );
                viewScores( $dbh ) if ( $selection eq $menu[4] );
                displayInsert( $dbh ) if ( $selection eq $menu[5] );  
                displayDelete( $dbh ) if ( $selection eq $menu[6] );  
                displayUpdate( $dbh ) if ( $selection eq $menu[7] );
                make_backup_form( $dbh ) if ( $selection eq $menu[8] );
                displayEmailForm( $dbh, "Yes" ) if ( $selection eq $menu[9] );  #accepted
                displayEmailForm( $dbh, "No" ) if ( $selection eq $menu[10] );   #not accepted
                displayEmailCommentsForm() if ( $selection eq $menu[11] );       #goes to all
                displayEmailTestForm() if ( $selection eq $menu[12] );
        }
        elsif ( param( "LAST" ) eq "SORT_ORDER" ) {
                view_sorted( $dbh);
    }
    elsif ( param( "LAST" ) eq "INSERT" ) {
          new_and_edit( $dbh );
          view( $dbh );
    #print "<p><a href=\"mm_projects.cgi?LAST=MAIN&selection=Insert a Record\">Add another record</a>";
    }
    elsif ( param( "LAST" ) eq "DELETE" ) {
          deleteRecord( $dbh );
          displayDelete( $dbh );
    #print "<p><a href=\"mm_projects.cgi?LAST=MAIN&selection=Delete a Record\">Delete another record</a>";
    }
    elsif ( param( "LAST" ) eq "UPDATE1" ) {
                $from = param( FROM);
    #print "debug: about to updateRecord\n";
          updateRecordForm( $dbh );
    }
        elsif ( param( "LAST" ) eq "UPDATE2" ) {
          updateRecord( $dbh );
                #print "debug after updateRecord with FROM: ", param( FROM ), "<br>\n";
                if (param( FROM ) eq "insert"){
                    displayInsert( $dbh );
                }else {
                    displayUpdate( $dbh );
                }
    #print "<p><a href=\"mm_projects.cgi?LAST=MAIN&selection=Edit a Record\">Edit another record</a>";
    }
        elsif ( param( "LAST" ) eq "UPLOAD1" ) {
          appendRecords( $dbh );
          view( $dbh );
    }
        elsif ( param( "LAST" ) eq "UPLOAD2" ) {
          uploadAllRecordsForm( $dbh );
    }
        elsif ( param( "LAST" ) eq "UPLOAD3" ) {
          view( $dbh );
    }
        elsif ( param( "LAST" ) eq "UPLOAD4" ) {
                &doUpload($dbh);
          view( $dbh );
    }
        elsif ( param( "LAST" ) eq "UPLOAD5" ) {
                &doAppend($dbh);
          view( $dbh );
    }
        elsif ( param( "LAST" ) eq "BACKUP" ) {
                &do_backup($dbh);
          print "<font color=red>Database Saved</font><br>\n";
    }
         elsif ( param( "LAST" ) eq "EMAIL" ) {
                &do_mail($dbh);
          print "<font color=red>Students Emailed</font><br>\n";
    }
        elsif ( param( "LAST" ) eq "EMAIL_COMMENTS" ) {
                &do_mail_comments($dbh);
          print "<font color=red>Group Mailing Done</font><br>\n";
    }
         elsif ( param( "LAST" ) eq "EMAIL_TEST" ) {
                &do_mail_test($dbh);
          print "<font color=red>Email Test Done</font><br>\n";
    }
    elsif (param( "LAST" ) eq "MODIFIED_VIEW" ) {
        &modifiedView($dbh);
    }


    $dbh->disconnect();
  &print_link;
}

print end_html();

######################################################################
#### view      display the database               ####################
######################################################################

sub view 
{
    my $dbh = shift(); 
   
    &load_all_records($dbh, "last, first ASC", "mm", $mm_fields);     #into @rows
    @students = @{$rows};
    #Enter and Score Projects in view: students array: @students\n<br>";
    
    foreach $student (@students){
        ($last, $first, $email, $phone, $ID_number) = @{$student};
          #print "debug before calling parial_records: last: $last, email: $email, ID_number: $ID_number\n<br>";
    #exit;
        &load_partial_records($dbh, "mm_projects", $projects_fields, $email);   #into @rows
        foreach $row (@{$rows}) {
            push( @{$full_rows  }, [ $last, $first, $email, $phone, $ID_number, @{$row} ] );
        }
    }
    #print "debug in view: full_rows array: @{$full_rows}\n<br>";

   
    my $tablerows = 
        Tr( th( { -bgcolor => "#dddddd", -align=>'left' }, 
                [ "Last", "First", "Email","Phone", "Student ID"  ] ),
            th( { -bgcolor => "#dddddd" }, 
                [ "category", "title", "softwware", "class", "semester", "year", "notes", "accepted", "criteria", 
                "tech_merit", "creative", "groups", "group_names", "description",
    "instructor", "proj_permission", "proj_url", "ohlone_degree", "proj_purpose",
                "proj_personal", "proj_client", "proj_non_prof", "proj_donate", "involvement",
    "highschool" ] ) );
          
    foreach my $row ( @$full_rows ) {
        $tablerows .= Tr( td( { -bgcolor => "#dddddd" }, $row ) );
    }
   
    print   h1( "MM Festival Projects Database" );
    &print_link;
    print table( { -border => 1, -cellpadding => 5, 
                  -cellspacing => 0 }, $tablerows ),
                br(), br(),
                "Database contains ", b( scalar( @$full_rows ) ), 
                " records.",br(), br();
}

######################################################################
#### simpleView      display the database in a few fields      #####
######################################################################

sub simpleView 
{
    my $dbh = shift(); 
   
    &load_all_records($dbh, "last, first ASC", "mm", $simple_mm_fields);      #into @rows
    @students = @{$rows};
    #Enter and Score Projects in view: students array: @students\n<br>";
    
    foreach $student (@students){
        ($last, $first, $email) = @{$student};
          #print "debug before calling parial_records: last: $last, email: $email, ID_number: $ID_number\n<br>";
    #exit;
        &load_partial_records($dbh, "mm_projects", $simple_projects_fields, $email);    #into @rows
        foreach $row (@{$rows}) {
          my($category, $title) = @{$row};
            push( @{$full_rows  }, [ $category, $last, $first,  $title ] );
        }
    }
    @full_rows = @{$full_rows};
    foreach my $row ( @full_rows ) {
      my ($category, $last, $first,  $title) = @$row;
      &simple_insertRecord ($dbh, $category, $last, $first, $title );
    }
    &load_all_records($dbh, "category, last, first, title ASC", "sort_criteria", "category, last, first, title" );      #into @rows
    @full_rows = @{$rows};
    
    
    #@full_rows = sort {(split /_/, lc $a)[0] cmp (split /_/, lc $b)[0]} @full_rows;
    #print "debug in simple_view: full_rows array: @full_rows\n<br>";
  #exit;
   
    my $tablerows = 
        Tr( th( { -bgcolor => "#dddddd", -align=>'left' }, 
                [ "category", "Last", "First", "title" ] ) );
          
    foreach my $row ( @full_rows ) {
        $tablerows .= Tr( td( { -bgcolor => "#dddddd" }, $row ) );
    }
   
    print   h1( "MM Festival Projects Database" );
    &print_link;
    print table( { -border => 1, -cellpadding => 5, 
                  -cellspacing => 0 }, $tablerows ),
                br(), br(),
                "Database contains ", b( scalar( @$full_rows ) ), 
                " records.",br(), br();
    my $string = "TRUNCATE TABLE sort_criteria";
  $dbh->do( $string); 
}

######################################################################
#### modifiedView      display selected fields in the database   #####
######################################################################

sub modifiedView 
{
    my $dbh = shift(); 
    my @checked_fields = param("mviewfields"); # get user-checked fields

    if (scalar(@checked_fields) == 0) {
        print h1( "MM Festival Projects Database: Modified View" );
        print("<h3>No options were selected!</h3>\n");
        return;
    }

    my $strCheckedFields = ""; # will hold fields to retrieve in sql statement

    # append each checked field to the string
    #if ($checked_fields[0] eq "email") {
    #    $checked_fields[0] = "mm_projects.email";
    #}
    $strCheckedFields .= $checked_fields[0];
    for (my $i = 1; $i < scalar(@checked_fields); $i++) {
    #    if ($checked_fields[$i] eq "email") {
    #        $checked_fields[$i] = "mm_projects.email";
    #    }
        $strCheckedFields .= ", $checked_fields[$i]";
    }

    &load_all_records($dbh, "last, first ASC", "mm", "*");      #into @rows
    @students = @{$rows};

    foreach $student (@students){
        my ($first, $last, $email, $phone, $id) = @{$student};
        &load_partial_records($dbh, "mm_projects", $strCheckedFields, $email);    #into @rows

        foreach $row (@{$rows}) {
            push( @{$full_rows}, [@{$row}] );
        }
    }

    @full_rows = @{$full_rows};

    foreach my $row ( @full_rows ) {
        #my $string = "INSERT INTO sort_criteria_full ($strCheckedFields) VALUES ( " .
        #  ("?, " x (scalar(@$row)-1)) . "? );";
        #print h1($string);
        #  $sth = $dbh->prepare($string) or die("Can't prepare string $mySQLString: ", $dbh->errstr);

        #$sth->execute(@$row) || 
        #  die "Could not execute query to insert data.<br>";
        #my ($category, $last, $first,  $title) = @$row;
        &modified_insertRecord($dbh, $strCheckedFields, $row);
    }

    &load_all_records($dbh, "$strCheckedFields ASC", "sort_criteria_full", "$strCheckedFields" );      #into @rows
    @full_rows = @{$rows};

=comment
    # get the sql command by adding the compiled string of fields
    my $SQLString = "SELECT " . $strCheckedFields .
            " FROM mm, mm_projects";

    # get the records/rows with the compiled sql command
    #&load_all_records($dbh, "$strCheckedFields ASC", "mm, mm_projects", "$strCheckedFields" );
    #my $full_rows = @{$rows};
    my $full_rows = &getRecords($dbh, $SQLString);
=cut

    # make the top row of the table to be printed
    my $tablerows = Tr(
            th(
                { -bgcolor => "#dddddd", -align=>'left' },
                \@checked_fields
            )
    );

    # add the rest of the rows to the variable for the table to be printed
    foreach my $row ( @$full_rows ) {
        $tablerows .= Tr( td( { -bgcolor => "#dddddd" }, $row ) );
    }

    # print the results to screen
    print "<h1>MM Festival Projects Database: Modified View</h1>";
    print("<br /><br />");
    print table( { -border => 1, -cellpadding => 5,
                -cellspacing => 0 }, $tablerows ),
              br(), br(),
              "Database contains ", b( scalar( @$full_rows ) ),
              " records.",br(), br();

    my $string = "TRUNCATE TABLE sort_criteria_full";
    $dbh->do( $string); 
}

######################################################################
#### display sorted dataset                                 ##########
######################################################################
                        
sub view_sorted {
        my $dbh = shift();
                        
  my $strAllFieldnames = "first, last, mm.email, phone, ID_number, " .
    "title, category, accepted, notes, class, groups, " .
    "softwware, semester, year, criteria, tech_merit, creative, group_names, description, " .
    "instructor, proj_permission, proj_url, ohlone_degree, proj_purpose, " .
                "proj_personal, proj_client, proj_non_prof, proj_donate, involvement, highschool";


                        
        # get the variables from the sort form
        my $sort1 = param("sort1");
        my $order1 = param("order1");
        
        my $sort2 = param("sort2");
        my $order2 = param("order2");
    
        my $sort3 = param("sort3");
        my $order3 = param("order3");
  #print ("debug with sort1: $sort1 and $order1, sort2: $sort2 and $order2, sort3: $sort3 and $order3<br>");
        
    # build order by string for sort sequence obtain from sort form
        if ($sort1 or $sort2 or $sort3) {
                #print("<p>The sort clause for the SQL query is:</p>\n");
          #print("<p>ORDER BY " . $sort1 . " " . $order1 .
      #($sort1 and $sort2 ? ", " : "") .
      #($sort2 ? $sort2 . " " . $order2 : "") .
      #((($sort2 and $sort3) or ($sort1 and $sort3)) ? ", " : "") .
      #($sort3 ? $sort3 . " " . $order3 : "") . "</p>\n");

          # display of the sort string for user
                my $OrderMessage = "Sorted by " . $sort1 . " " .  $order1 .
              ($sort1 and $sort2 ? " by " : "") .
      ($sort2 ? $sort2 . " " . $order2 : "") .
              ((($sort2 and $sort3) or ($sort1 and $sort3)) ? " by " : "") .
      ($sort3 ? $sort3 . " " . $order3 : "");
        
          # sort string for SQL query statement
          my $strOrderby = "ORDER BY " . $sort1 . " " . $order1 .
              ($sort1 and $sort2 ? ", " : "") .
      ($sort2 ? $sort2 . " " . $order2 : "") .
                    ((($sort2 and $sort3) or ($sort1 and $sort3)) ? ", " : "") .
                      ($sort3 ? $sort3 . " " . $order3 : "");
        
          # building SQL query string
          my $SQLString = "SELECT " .  $strAllFieldnames .
            " FROM mm, mm_projects" .
            " WHERE mm.email = mm_projects.email " . 
          $strOrderby ;
                
          #print("<p>The SQL query string is: $SQLString </p>\n");
           
          # extract dataset from database
          $full_rows = &getRecords($dbh, $SQLString);
          #print("<p>In view_sorted routine value of full_row array is: @{$full_rows}</p>\n");
                          
          # print records retrieved
          my $tablerows =
            Tr( th( { -bgcolor => "#dddddd", -align=>'left' },
                    [ "First Name", "Last Name", "Email", "Phone", "Student ID" ] ),
                th( { -bgcolor => "#dddddd" },
                    [ "Title", "Category", "Accepted", "Notes", "Class",
                      "Groups", "Software", "Semester", "Year",
                      "Criteria", "Technical Merit", "Creative", "Group Names", "Description",
        "Instructor", "Proj Permission", "Proj URL", "Ohlone Degree", "Proj Purpose",
                    "Proj Personal", "Proj Client", "Proj Non Prof", "Proj Donate", "Involvement",
        "highschool" ] ) );
          
          foreach my $row ( @$full_rows ) {
                $tablerows .= Tr( td( { -bgcolor => "#dddddd" }, $row ) );
          }
        
          print h1( "MM Festival Projects Database" );
          # &print_link;
          print("<br /><br />");
          print("<p>$OrderMessage</p>");
          print table( { -border => 1, -cellpadding => 5,
                    -cellspacing => 0 }, $tablerows ),
                  br(), br(),
                  "Database contains ", b( scalar( @$full_rows ) ),
                  " records.",br(), br();
      
      
        } else {          
    print h1( "MM Festival Projects Database" );
          print("<h3>Sorry, no sort options were selected!</h3>\n");
         
        } # end if testing for sort1 thru sort3
            
} # end view_sorted routine
                  




######################################################################
#### viewScores                       ####################
######################################################################

sub viewScores {

    my $dbh = shift(); 
    $scores_fields = "category, title, email, notes, criteria, ". 
                "tech_merit, creative, groups, accepted, group_names, description";
    $student_fields = "last, first, email";
                
    &load_accepted_records($dbh, "category ASC", "mm_projects", $scores_fields, "Yes"); #into @rows
    @projects = @{$rows};
    #print "debug in view: projects array: @projects\n<br>";
    
    foreach $projects (@projects){
        ($category, $title, $email, $notes, $criteria, $tech_merit, $creative, $groups, $accepted, 
    $group_names, $description ) = @{$projects};
        #print "debug before calling partial_records: category: $category, title: $title", "email: $email\n<br>";

        &load_partial_records($dbh, "mm", $student_fields, $email);   #into @rows
        foreach $row (@{$rows}) {
            push( @{$full_rows  }, [ $category, $title, @{$row}, $accepted, 
                            $criteria, $tech_merit, $creative, $groups, $group_names, $description] );
        }
    }
    
    #print "debug in view: full_rows array: @{$full_rows}\n<br>";
   
    my $tablerows = 
        Tr( th( { -bgcolor => "#dddddd", -align=>'left' }, 
                [  "Score", "Category", "Title", "Last", "First", "Email", ] ),
            th( { -bgcolor => "#dddddd" }, 
                [  "Accepted", "Criteria", "Tech_Merit", "Creative", "Group", 
"group_names", "description" ] ) );
          
    foreach my $row ( @$full_rows ) {
        #print "debug in viewScores with row: @$row<br>\n";

    ######## get criteria scores for for project
        
        my @test = @$row;
        #print "debug in viewScores with test array: @test<br>\n";
        #print "debug in viewScores with test array[6]: $test[6]<br>\n";
        
        my @criteria_values = ();
        @criteria_values = split(/\|/, $test[6]);
        #print "debug in get_criteria_values with new criteria_values array: @criteria_values<br>\n";
        #print "debug in get_criteria_values with \$row =>[6]: $row =>[6])\n<br>";
        
    ######## add up the scores
        my $total = 0;
        foreach (@criteria_values) {
            $total += $_;
        }
        $total +=  $test[7];
        $total +=  $test[8];
        #print "debug in viewScores with total: $total<br>\n";
        
    ######## add total to the end of the row of data
        unshift ( @{$row}, $total);
        #$tablerows .= Tr( td( { -bgcolor => "#dddddd" }, $row ) );
    }
    ######## sort by score (list is already sorted by category)
   $sorted =  [sort byscore @$full_rows]; 
   #print "debug with sorted array: @sorted<p>";
   $full_rows = $sorted;
   
    ######## show by score (list is already sorted by category)
    foreach (  @$full_rows ) {
    #foreach (  @$sorted ) {
        #print "debug in viewScores with sort byscore: @{$_}<p>\n";
    }
    #exit;
    ######## show by score (list is already sorted by category)
    #foreach (  sort byscore @$full_rows ) {
    #    print "debug in viewScores with sort byscore: @{$_}<p>\n";
    #}
    #exit;
    ####### relocate score to the end of the record
    # foreach $row(   @$full_rows ) {
    #    $score = shift (@{$row});
    #    push (@{$row}, $score);
    #    print "debug in viewScores with score at the end: @{$row}<p>\n";
    #}
    #exit;
    ###### sort list ascending by category
    $sorted = [sort  bycategory @$full_rows];
    $full_rows = $sorted;
    ###### show list ascending by category
    foreach (  @$full_rows ) {
        #print "debug in viewScores with sort by category ascending: @{$_}<p>\n";
    }
    #exit;

    ####### relocate score to the front of the record
    #foreach $row(   @$full_rows ) {
    #    $score = pop (@{$row});
    #   unshift (@{$row}, $score);
    #    print "debug in viewScores with score in front sorted by category: @{$row}<p>\n";
    #}
    ####### finish putting the array in $tablerows string
     foreach my $row ( @$full_rows ) {
        $tablerows .= Tr( td( { -bgcolor => "#dddddd" }, $row ) );
     }
       
    print   h1( "MM Festival Projects Database" );
    &print_link;
    print  table( { -border => 1, -cellpadding => 5, 
                  -cellspacing => 0 }, $tablerows ),
         br(), br(),
         "Database contains ", b( scalar( @$full_rows ) ), 
         " records.",br(), br();
}
sub byscore {
    ${$b}[0] <=> ${$a}[0];
}
sub bycategory {
    ${$b}[1] cmp ${$a}[1];
}
######################################################################
#### displayInsert                      ####################
######################################################################

sub displayInsert
{
    my $dbh = shift();
    
#### get mm records
    my $sth = $dbh->prepare(  
    "SELECT last, first, email FROM mm ORDER by last, first ASC" );   
    $sth->execute();
    my ( %mm_names, @mm_ids );
    while ( my @row = $sth->fetchrow_array ) {
        push( @mm_ids, $row[ 2 ] );
        $mm_names{ $row[ 2 ] } = $row[ 0 ] . ", " . $row[ 1 ];
    }
    
######## get categories info
    my $sth = $dbh->prepare(  
        "SELECT category FROM mm_criteria order by category" );
    $sth->execute();
    @cat_ids = ();
    while ( my @row = $sth->fetchrow_array ) {
        push( @cat_ids, $row[ 0 ] );
    }
####### Draw the form
    print h3( "Enter a new project." ), br(),
    start_form(),
                "<table>",  
                    "<tr><td>Select a student", 
                        "<td>",  popup_menu( -name => 'UPDATE_ID', 
                                -value => \@mm_ids, 
                                -labels => \%mm_names ),
                    "<tr><td>Title of the project (typed correctly, <br>it will be a key to retrieve the record)", 
                    "<td>", textfield( -name => 'title', size => '35'),
                    
                    "<tr><td valign=top>Category", 
                    "<td><select name=\"category\">";
                    
                    foreach (@cat_ids) {
                        if($_ ne $category) {
                            print "<option value=\"$_\">$_</option>";
                        }
                        else {
                            print "<option value=\"$_\" selected>$_</option>";
                        }
                    }

    print   "</table>",
  
                    hidden( { -name => "LAST", -value => "INSERT",
                        -override => "1" } ),
              br(), br(), submit( -value => "Add New Project" ), 
          end_form(), br(), br();
}

######################################################################
#### new_and_edit               ####################
######################################################################

sub new_and_edit {
   my $dbh = shift();
    
  my $id = param( UPDATE_ID );
  my $category = param( category );
      our $title = param( 'title' );
        
######## get projects values for project
        
    my $statement = "SELECT email FROM mm_projects " .
                   "WHERE email = '$id' AND title =  ? AND category = '$category';";                
  my $sth = $dbh->prepare( $statement );
  $sth->execute($title);
    my @projects_values = $sth->fetchrow_array;
    $sth->finish();
        
        if($projects_values[0] ne "") {
            #print "debug in new_and_edit with duplicate in project_value array:", 
              #join('*', @projects_values), "\n<br>";
            print "Project record:<font color=red> $id",
                        "<font color=red>$category</font> already exists.<br>";
            &print_link;
            exit;
            
        }elsif ($title eq "") {
                print "<font color=red>The title may not be left blank</font><br>",
                        "Ok to press \"BACK\" to try again";
                &print_link;
                exit;
                
        }else {

    
            #print "debug in new_and_edit: id: $id\n<br>";
            &insertRecord ($dbh, $id, $category);
            $from = "insert";
            &updateRecordForm ($dbh);
        }
}


######################################################################
#### displayDelete                    ####################
######################################################################


sub displayDelete
{
   my $dbh = shift();
   
   my $sth = $dbh->prepare(  
      "SELECT email, title FROM mm_projects order by title" );
   
   $sth->execute();
   
   my ( %names, @ids );

   while ( my @row = $sth->fetchrow_array ) {
        my $key = "$row[0]" . "|" . "$row[1]";
        push( @ids, $key );
        $names{ $row[ 0 ] } = $row[ 1 ] . " - " . $row[ 0 ];
   }

   $sth->finish;
   
   print h3( "Delete a record from the database" ), br(),
      start_form(),
         "Select a project to delete ",
         popup_menu( -name => 'DELETE_ID', 
                     -value => \@ids, 
                     -labels => \%names ), br(), br(), br(),
         hidden( { -name => "LAST", -value => "DELETE", 
                   -override => 1 } ),
         submit( -value => "Delete a project" ), br(), br(),
      end_form(), 
      font( { -color => "red" }, 
            "This action removes the record permanently." );
}
######################################################################
#### displayUpdate                    ####################
######################################################################


sub displayUpdate
{
   my $dbh = shift();
   #print "debug in displayUpdate<br>\n";
   my $sth = $dbh->prepare(  
      "SELECT email, title, category FROM mm_projects order by category" );
   
   $sth->execute();
   
   my ( %names, @ids );

   while ( my @row = $sth->fetchrow_array ) {
        my $key = $row[0] .  "|" . "$row[1]" . "|" . "$row[2]"  ;
        push( @ids, $key );
        #push( @names, $row[1]);
        $names{ $row[ 0 ] } = $row[ 1 ] . " - " . $row[ 0 ];
   }
   
   $sth->finish;
   
   print h3( "Update (edit) a record" ), br(),
      start_form(),
         "Select a record to update ",
         popup_menu( -name => 'UPDATE_ID2', 
                     -value => \@ids, 
                     -labels => \%names ), br(), br(), br(),
         hidden( { -name => "LAST", -value => "UPDATE1", 
                   -override => 1 } ), 
        hidden( { -name => "FROM", -value => "update", 
                   -override => 1 } ), 
         submit( -value => "Edit the Record" ), br(), br(),
      end_form();
}
######################################################################
#### updateRecordForm                     ####################
######################################################################


sub updateRecordForm 
{
    my $dbh = shift();
        my $id = param( UPDATE_ID );
        #print "debug in updateRecordForm with id: $id<br>\n";
        
        #my $title = param( 'title' );  #already initialized in updateRecord
        if (param('UPDATE_ID2')) {    #coming from 'displayUpdate'
            my $key = param( 'UPDATE_ID2' );
            ($id, $title) = split(/\|/, $key);
        }
        # $from is assigned either in new_and_edit or LAST = UPDATE2 if statement
        #print "debug in updateRecordFrom with from: $from<br>\n";  #assigned either in new_and_edit
                                                    # or LAST = UPDATE2 if statement
        
  #print "debug in updateRecordForm with id: $id and title: $title\n<br>";

######## get mm record for student 
    my $statement = "SELECT $mm_fields FROM mm " .
                   "WHERE email = '$id' ;";                
  my $sth = $dbh->prepare( $statement );
  $sth->execute();
    my @mm_values = $sth->fetchrow_array;
        #print "debug in updateRecordForm with mm_values array:  @mm_values\n</br>";

######## get projects_values for project
        
    my $statement = "SELECT email, $projects_fields FROM mm_projects " .
                   "WHERE email = '$id' AND title = ? ;";                
  my $sth = $dbh->prepare( $statement );
  $sth->execute($title);
    my @projects_values = $sth->fetchrow_array;
  #print "debug in updateRecordForm with project_value array:", join("\n<br>", @projects_values), "\n<br>";
    $sth->finish();

        ##print "debug print every value of projects_values:<br>\n";
        foreach (@projects_values) {
            ##print "debug: ", $j++, "$_\n<br>";
        }

######## get criteria for category
        $category = $projects_values[1];
        #print "debug in get_criteria_for_categories with category: $category<br>\n";
        
         my $sth = $dbh->prepare(  
            "SELECT criteria FROM mm_criteria WHERE category = '$category'" );
  $sth->execute();
        my @criteria_ids = ();
  @criteria_ids = $sth->fetchrow_array;
        ##print "debug in get_criteria with criteria_ids array: $criteria_ids[0]<br>\n";

        @criteria_ids = split(/\|/, $criteria_ids[0]);

######## get criteria for for project
        
        my @criteria_values = ();
        @criteria_values = split(/\|/, $projects_values[9]);
        ##print "debug in get_criteria_values with new criteria_values array: @criteria_values<br>\n";
        for($x=0; $x<@criteria_values; $x++) {
            ##print "debug in get criteria with criteria_values[$x]: $criteria_values[$x]<br>\n";
        }
        #print "debug in get_criteria_values with projects_values[9]: $projects_values[9])\n<br>";
        
######## get categories info  - for pull down menu
        my $sth = $dbh->prepare(  
            "SELECT category, criteria FROM mm_criteria order by category" );
  $sth->execute();
        @cat_ids = ();
  while ( my @row = $sth->fetchrow_array ) {
            push( @cat_ids, $row[ 0 ] );
  }
        
######## Starting the form
        my $i = 0;  #used later in displaying criteria (can't be initialized inside table)
    print h3( "Editing project $title." ),
          start_form();
                
######## print left columns
######## project fields: category, title, softwware, class, semester, year, notes, accepted, criteria", 
######## "tech_merit, creative, groups, group_names, description, highschool
  print "<br><table><tr><td valign=top>",
                        "<table>",
                            "<tr><td>Name: <td> $mm_values[1] $mm_values[0]</tr>",
                            "<tr><td>email: <td>$mm_values[2]</tr>";
          "<tr><td>Student_ID: <td>$mm_values[3]</tr>";
                            
                    ######## accepted
        print   "<tr><td valign=top>Accepted: <td>";
                            foreach (@yes_no) {
                                print "<input type=\"radio\" name=\"accepted\" value=\"$_\" ";
                                if($_ ne $projects_values[8]) {
                                    print " >$_</input>";
                                }
                                else {
                                    print " checked='yes'>$_</input>";
                                }
                            }
                            
                    ######## class
         print              "<tr><td>Class", 
                            "<td><select name=\"class\">";
                            foreach (@classes) {
                                if($_ ne $projects_values[4]) {
                                    print "<option value=\"$_\">$_</option>";
                                }
                                else {
                                    print "<option value=\"$_\" selected='yes'>$_</option>";
                                }
                            }

                    ######## semester
          print             "<tr><td valign=top>Semester: <td>",
                            "<select name=\"semester\">";
                            foreach (@semester) {
                                if($_ ne $projects_values[5]) {
                                    print "<option value=\"$_\">$_</option>";
                                }
                                else {
                                    print "<option value=\"$_\" selected='yes'>$_</option>";
                                }
                            }
                            
                    ##### year
        print   "<tr><td>Year", 
                        "<td><select name=\"year\">";
                        foreach (@year) {
                            if($_ ne $projects_values[6]) {
                                print "<option value=\"$_\">$_</option>";
                            }
                            else {
                                print "<option value=\"$_\" selected='yes'>$_</option>";
                            }
                        }

                    ##### instructor
        print   "<tr><td>Instructor",
               #"<td><font color=red>$projects_values[15] ",
                "<td>", textfield( -name => 'instructor', size => '20', -value => "$projects_values[15]");
              
                        
                    ##### software
        print   "<tr><td>Software",
                        #"<td><font color=red>$title ",
                        "<td>", textfield( -name => 'software', size => '20', -value => "$projects_values[3]");

                        
                    ##### notes
        print             "<tr><td valign=top>Judges Notes: <td>" , 
                            textarea( -name=>'notes', -value => "$projects_values[7]", 
                                        -rows => 8, -cols => 40, override => 1);
                    ######## groups
        print   "<tr><td valign=top>Group: <td>";
                            foreach (@yes_no) {
                                print "<input type=\"radio\" name=\"groups\" value=\"$_\" ";
                                if($_ ne $projects_values[12]) {
                                    print " >$_</input>";
                                }
                                else {
                                    print " checked='yes'>$_</input>\n";
                                }
                            }

                    ##### group_names
        print   "<tr><td>Group Names <td>",
                        textarea( -name=>'group_names', -value => "$projects_values[13]", 
                                        -rows => 4, -cols => 25, override => 1);
                                        
                    ##### highschool
        print   "<tr><td colspan=2>High School <font size=-1>(if High School Entry was selected)</font>",
               #"<tr><td>&nbsp;</td><td><font color=red>$highschool ",
                "<tr><td>&nbsp;</td><td>", textfield( -name => 'highschool', size => '25',
     -value => "$projects_values[25]" );

        print   "</table>";

              

######## print right column

                    ######## category
        print   "<td valign=top><table>",
                            "<tr><td valign=top>Category", 
                            "<td><select name=\"category\">";
                            foreach (@cat_ids) {
                                if($_ ne $projects_values[1]) {
                                    print "<option value=\"$_\">$_</option>";
                                }
                                else {
                                    print "<option value=\"$_\" selected>$_</option>\n";
                                }
                            }
                    #### title
        print   #"<tr><td><font color=red>Title",
                        "<tr><td>Title:",
                        "<td><font color=red>$title\n ";
                        #"<td>", textfield( -name => 'title2', size => '35', -value => "$title");
                        
                    ##### description
        print             "<tr><td valign=top>Description: <td>" , 
                            textarea( -name=>'description', -value => "$projects_values[14]", 
                                        -rows => 4, -cols => 40, override => 1);
                            
                    #### criteria
                        foreach (@criteria_ids) {
                                my $name = "crit" . $i;
                                print "<tr><td>$_:<td><table><tr>";
                                foreach (0 .. 10) {
                                    print "<td><input type=\"radio\" name=\"$name\" value=\"$_\" ";
                                    if($_ ne $criteria_values[$i]) {
                                        print " >$rubric[$_]</input>\n";
                                    }
                                    else {
                                        print " checked='yes'>$rubric[$_]</input>\n";
                                    }
                                 
                                }
                                print "</table>\n";
                                $i++;
                        }
      print ("</tr><tr><td><p><p></td></tr>");

=comment until cut
                    #### Technical Merit
                        print "<tr><td>&nbsp;<td><table><tr><td><br>From Low to High</table>";
                        print "<tr><td>Technical Merit:<td><table><tr>";
                        foreach (0 .. 10) {
                                print "<td><input type=\"radio\" name=\"tech_merit\" value=\"$_\" ";
                                if($_ ne $projects_values[10]) {
                                    print " >$_</input>";
                                }
                                else {
                                    print " checked='yes'>$_</input>";
                                }
                                 
                        }
                        print "</table>";
                        
                    #### Creativity
                        print "<tr><td>Creativity:<td><table><tr>";
                        foreach (0 .. 10) {
                                print "<td><input type=\"radio\" name=\"creative\" value=\"$_\" ";
                                if($_ ne $projects_values[11]) {
                                    print " >$_</input>";
                                }
                                else {
                                    print " checked='yes'>$_</input>";
                                }
                                 
                        }
                        print "</table>";
=cut
  
                    ######## proj_client
          print "<tr><td colspan=2valign=top>Is this project produced for a client?
                  </tr><tr><td>&nbsp;</td><td>";
          foreach (@yes_no) {
                print "<input type=\"radio\" name=\"proj_client\" value=\"$_\" ";
                if($_ ne $projects_values[21]) {
                #if($_ ne $proj_client) {
                    print " >$_</input>";
                }
                else {
                    print " checked='yes'>$_</input>\n";
                }
          }
                   ######## proj_non_prof
          print "<tr><td colspan=2valign=top>Is this project created for a non- profit organization?
                </tr><tr><td>&nbsp;</td><td>";
          foreach (@yes_no) {
                print "<input type=\"radio\" name=\"proj_non_prof\" value=\"$_\" ";
                if($_ ne $projects_values[22]) {
                #if($_ ne $proj_non_prof) {
                    print " >$_</input>";   
                }
                else {
                    print " checked='yes'>$_</input>\n";
                }
          }
                    ######## proj_donate 
          print "<tr><td colspan=2valign=top>Did you donate your services to complete the project?
                  </tr><tr><td>&nbsp;</td><td>";
          foreach (@yes_no) {
                print "<input type=\"radio\" name=\"proj_donate\" value=\"$_\" ";
                if($_ ne $projects_values[12]) {
                #if($_ ne $proj_donate) {
                    print " >$_</input>";
                }
                else {
                    print " checked='yes'>$_</input>\n";
                }
          }
                   ######## proj_permission
          print "<tr><td colspan=2 valign=top>Do you grant the right to the Multimedia
                  Department<font size=-1> to include your entries in promotional
                  <br>materials such as the department's web site and brochures?
                  You will be given full credit for your work.</font>
              
                  </tr><tr><td>&nbsp;</td><td>";
            foreach (@yes_no) {
                  print "<input type=\"radio\" name=\"proj_permission\" value=\"$_\" ";
                  #if($_ ne $projects_values[16]) {
                  if($_ ne $projects_values[16]) {  #$proj_permission
                    print " >$_</input>";
                  }
                  else {
                      print " checked='yes'>$_</input>\n";
                  }
            }
                    #### proj_url
          print"<tr><td colspan=2 valign=top>" ,
          "Enter the URL if the project is online. If submitting on CD or DVD, " ,
      "or through any other means, enter the exact filename or folder - file " ,
      "or folder names must include your initials and last names." ,
             "<tr><td><td>", textfield( -name => 'proj_url', size => '35', 
          -value => "$projects_values[17]");



                     
  print     "</table><p>",
                    "</table>";
   
    print submit( -value => "Update the Record" ),
          hidden( { -name => "LAST", -value => "UPDATE2", 
                   -override => 1 }),
                hidden( { -name => "KEY", -value => "$id", 
                   -override => 1 }),
                hidden( { -name => "title2", -value => "$title", 
                   -override => 1 }),
                hidden( { -name => "FROM", -value => "$from", 
                   -override => 1 }),

          end_form();
                exit;
}

######################################################################
#### insertRecord                     ####################
######################################################################

sub insertRecord
{
  my $dbh = shift;
  my $email = shift;
  my $category = shift;
   
  #print "debug in insertRecord with email: $email and title: $title\n<br>";
  my $string = "INSERT INTO mm_projects (email, title, category)  
    VALUES ( ?, ?, ? );";
  $sth = $dbh->prepare($string) or die("Can't prepare string $mySQLString: ", $dbh->errstr);

    $sth->execute($email, $title, $category) || 
          die "Could not execute query to insert data.<br>";
}

######################################################################
#### simple_insertRecord                    ####################
######################################################################

sub simple_insertRecord
{
  my $dbh = shift;
  my $category = shift;
  my $last = shift;
  my $first = shift;
  my $title = shift;
   
  #print "debug in simple_insertRecord with category: $category and title: $title\n<br>";
  #exit;
  
  my $string = "INSERT INTO sort_criteria (category, last, first, title)  
    VALUES ( ?, ?, ?, ? );";
  $sth = $dbh->prepare($string) or die("Can't prepare string $mySQLString: ", $dbh->errstr);

    $sth->execute( $category, $last, $first, $title) || 
          die "Could not execute query to insert data.<br>";
}

######################################################################
#### modified_insertRecord                    ####################
######################################################################

sub modified_insertRecord
{
    my $dbh = shift;
    my $fields = shift;
    my @row = @{+shift};
        
    my $string = "INSERT INTO sort_criteria_full ($fields) VALUES ( " . ("?, " x (scalar(@row)-1)) . "? );";
    $sth = $dbh->prepare($string) or die("Can't prepare string $mySQLString: ", $dbh->errstr);

    $sth->execute(@fieldsarr) || 
          die "Could not execute query to insert data.<br>";
}

######################################################################
#### deleteRecord                     ####################
######################################################################


sub deleteRecord 
{
    my $dbh = shift();
        my $key = param( 'DELETE_ID' );
        my ($email, $title) = split(/\|/, $key);
        #print "debug in deleteRecord with email: $email and title: $title\n<br>";
        
    my $string = "DELETE FROM mm_projects ".
                "WHERE email = '$email' AND title = '$title' ";
   
    $dbh->do( $string );
    print "Record <font color=red>", param( 'DELETE_ID' ), 
          " </font>deleted.",  br();
}
######################################################################
#### updateRecord                     ####################
######################################################################


sub updateRecord
{
    my $dbh = shift();
  $key = param('KEY');
        our $title2 = param( 'title2' );
        #print "debug in updateRecord with title2: $title2\n<br>";

    ######## project fields: category, title, softwware, class, semester, year, notes, accepted, criteria", 
    ######## "tech_merit, creative, groups
  ##print "debug: key: $key\n<br>";
        my $category =  param( category );
        my $software =  param( software );
        my $class =  param( 'class');
        my $semester =  param(semester);
        my $year = param(year);
        my $notes = param(notes);
        my $accepted = param(accepted);
        my $tech_merit = param(tech_merit);
        my $creative = param(creative);
        my $groups = param(groups);
        my $group_names = param(group_names);
  my $description = param(description);
        my $instructor = param(instructor);
        my $proj_permission = param(proj_permission);
        my $proj_url = param(proj_url);
        my $ohlone_degree = param(ohlone_degree);
        my $proj_purpose = param(proj_purpose);
        my $proj_personal = param(proj_personal);
        my $proj_client = param(proj_client);
        my $proj_non_prof = param(proj_non_prof);
        my $proj_donate = param(proj_donate);
        my $involvement = param(involvement);  
        my $highschool = param(highschool);  

        #print "debug in updateRecord with highschool: $highschool<br>\n";
        #print "debug in updateRecord with group_names: $group_names<br>\n";
        #print "debug in updateRecord with description: $description<br>\n";

    ######## get criteria for category
        my $sth = $dbh->prepare(  
            "SELECT criteria FROM mm_criteria WHERE category = '$category'" );
  $sth->execute();
        my @criteria_ids = ();
  @criteria_ids = $sth->fetchrow_array;
        #print "debug in get_criteria_values with criteria_values array: $criteria_ids[0]<br>\n";

        @criteria_ids = split(/\|/, $criteria_ids[0]);
        #print "debug in get_criteria_values with new criteria_values array: @criteria_values<br>\n";

    ####### set criteria
        $i = 0;
        foreach (@criteria_ids) {
                my $number = 0;
                my $name = "crit" . $i++;
                $number = param( $name );
                #print "debug in updateRecord with name: $name and number: $number\n<br>";
                #$number *= $weight;

                $criteria .= $number . "|";
        }

    
  #print "debug: category: $category, accepted: $accepted, notes: $notes\n<br>";
        #print "debug: key: $key, title2: $title2\n<br>";
        
    my $string = "UPDATE mm_projects  SET category = ?, softwware = ?, " .
                "semester  = ?, year = ?, notes = ?, accepted = ?, " . 
                "tech_merit = ?, creative = ?, groups = ?, criteria= ?, ".
                "class = ?, group_names = ?, description = ?, ".
    "instructor = ?, proj_permission = ?, proj_url = ?, " .
    "ohlone_degree = ?, proj_purpose = ?, " .
    "proj_personal = ?, proj_client = ?, " .
    "proj_non_prof = ?, proj_donate = ?, " .
    "involvement = ?, highschool = ? " .
                "WHERE email = ? AND title = ? ";
  
  #print "$SQLstring <br>";
  $sth = $dbh->prepare($string) or die("Can't prepare string $string: ", $dbh->errstr);

    $sth->execute($category, $software, $semester, $year, $notes, $accepted, 
  $tech_merit, $creative, $groups, $criteria, $class, $group_names, $description,
  $instructor, $proj_permission, $proj_url, $ohlone_degree, $proj_purpose, 
  $proj_personal, $proj_client, $proj_non_prof, $proj_donate, $involvement, $highschool,
  $key, $title2) || 
      die "Could not execute query to insert data.<br>";
  
}                   
################################################################
###     print_header          ####
################################################################

sub print_header {
  print header();
  print <<end; 
    <head> <title>Multimedia Festival Database </title>
  <style type="text/css">
  <!--
  BODY {font-family: arial, helvetica, sans serif; color: #330066; background-color: white;}
  A {text-decoration:none; cursor:hand; font-family: Arial, Helvetica, sans-serif}
  A:link {color: #0000FF; text-decoration: underline; font-family: Arial, Helvetica, sans-serif}
  A:visited {color: #660000; text-decoration: underline; font-family: Arial, Helvetica, sans-serif}
  A:active {color: #ff0000; text-decoration: none; font-family: Arial, Helvetica, sans-serif}
  A:hover {color: #666666; text-decoration: none; font-family: Arial, Helvetica, sans-serif}
  td {font-family: arial, helvetica, sans serif; color: #330066;}
  b {font-family: arial, helvetica, sans serif; color: #330066;}
  p {font-family: arial, helvetica, sans serif; color: #330066;}
  -->
  </style>
  </head>
  <body>
end
}

######################################################################
#### print_options                 #######
######################################################################


sub print_options {
  print 
         start_form(),
         popup_menu( -name => 'selection',
                     -value => $menu ),
         hidden( { -name => "LAST", -value => "MAIN" } ),
         br(), br(), br(), br(), br(),
         submit( -value => "Click to Proceed" ),
         end_form();
}

######################################################################
#### print_link                  #######
######################################################################

sub print_link {
  print p(),
                a( { -href => "mm_projects.cgi" }, 
            "Back to the MM Project Database Options" ),
                p(),
          a( { -href => "index.cgi" }, 
            "Back to the Main MM Festival Database Page" );

}

######################################################################
#### upload_choices       menu for uploading from spreadsheet  #######
######################################################################

sub upload_choices {

print (<<EndHTML);
<form action="mm.cgi" method=post>
  <center><table bgcolor="powderblue" border=0 width=500>
  <tr height=50><td colspan=2><center><b><font size=+1>Upload records from text file:</font></b>
  
  </tr><tr><td colspan=2 align=center><b><font color=990033>Careful, action cannot be 'undone'</font></b>
  </tr><tr height=50><td width=100 >&nbsp;</td>
  <td align=left><b>Select one of the following options:</b>
  </tr><tr><td width=100 >&nbsp;</td>
  <td align=left>
  <input type=radio name="LAST" value="UPLOAD1">Add new records to existing database
    </input>
  </tr><tr><td width=100 >&nbsp;</td>
  <td align=left>
      <input type=radio name="LAST" value="UPLOAD2">Replace all existing records by new upload
    </input>
  </tr><tr><td width=100 >&nbsp;</td>
  <td align=left>
  <input type=radio name="LAST" value="UPLOAD3">Cancel upload.</b></input>

  </tr><tr><td colspan=2 align=center height=50>
        <input type=submit value="Submit Selection">
        </td>
  </tr>
  </table>

  <input type=hidden name="" value="">
  
</form>
EndHTML

}

######################################################################
#### appendRecords       add recoreds to exsiting database  ##########
######################################################################

sub appendRecords {
    #print "debug: ready to upload all records\n";
    #This form will import a copy and paste quiz bank in text format

    print ( '<form action="mm.cgi" method=post>'. "\n" );
  
    print ( '<center><h3>Replace all existing records by new ones</h3></center>'. "\n" );
          
    #Start of Item input
    print ( "<ul><b> Paste copied selection from spreadseet:<b>"
                . "<p>Fields should be in following order:"
                . "<ul type=disk><li>Last Name"
                . "<li>First Name"
                . "<li>Category"
                . "<li>Title"
                . "<li>Email" 
                . "<li>Accepted"
                . "<li>Notes"
                . "<p></ul>Ways to make upload more compatible with database:"
                . "<br><ul type=disk><li>All 'category', 'title', and 'email' fields must have data"
                . "<li>no blank rows"
                . "<li>Projects with same name will be considered group projects"
                . "<li>If Last name, First name columns don't exist, just add an extra blank "
                . "column in between the present NAME and CATEGORIES fields" );
                
    print ( "<p></ul><textarea rows=15 cols=70 name=\"DATA\"></textarea>"
                . "</ul>\n" );

  print ( "<input type=hidden name=\"LAST\" value=\"UPLOAD5\">"
    . "<p><center><b><input type=submit value=\"Upload new records\">"
    . "&nbsp;<input type=reset value=\"Clear Entries\"></b></center><p>" );
}

######################################################################
#### uploadAllRecordsForm       replace exsiting records with new  #######
######################################################################

sub uploadAllRecordsForm {
    #print "debug: ready to upload all records\n";
    #This form will import a copy and paste quiz bank in text format

    print ( '<form action="mm.cgi" method=post>'. "\n" );
  
    print ( '<center><h3>Replace all existing records by new ones</h3></center>'. "\n" );
          
    #Start of Item input
    print ( "<ul><b> Paste copied selection from spreadseet:<b>"
                . "<p>Fields should be in following order:"
                . "<ul type=disk><li>Last Name"
                . "<li>First Name"
                . "<li>Category"
                . "<li>Title"
                . "<li>Email" 
                . "<li>Accepted"
                . "<li>Notes"
                . "<p></ul>Ways to make upload more compatible with database:"
                . "<br><ul type=disk><li>All 'category', 'title', and 'email' fields must have data"
                . "<li>no blank rows"
                . "<li>Projects with same name will be considered group projects"
                . "<li>If Last name, First name columns don't exist, just add an extra blank "
                . "column in between the present NAME and CATEGORIES fields" );
                
    print ( "<p></ul><textarea rows=15 cols=70 name=\"DATA\"></textarea>"
                . "</ul>\n" );

  print ( "<input type=hidden name=\"LAST\" value=\"UPLOAD4\">"
    . "<p><center><b><input type=submit value=\"Upload new records\">"
    . "&nbsp;<input type=reset value=\"Clear Entries\"></b></center><p>" );
}

######################################################################
#### doUpload       do the replace existing records with new  ########
######################################################################

sub doUpload {
    $dbh = shift();
    my $data = param('DATA');
    &delete_all($dbh);
    #print ("debug: in 'doUpload'\n");
    #print ("debug with data: " . $data . "\n");
    my @data_array = split ('\n', $data);
    foreach my $line (@data_array) {
        (@db_line) = split ('\t', $line);
        add_record($dbh, @db_line); 
    }
}

######################################################################
#### doAppend       do the appends records with new         ########
######################################################################

sub doAppend {
    $dbh = shift();
    my $data = param('DATA');
    #print ("debug: in 'doUpload'\n");
    #print ("debug with data: " . $data . "\n");
    my @data_array = split ('\n', $data);
    foreach my $line (@data_array) {
        (@db_line) = split ('\t', $line);
        add_record($dbh, @db_line); 
    }
} 

######################################################################
#### add_record       add a new record from upload option  ###########
######################################################################

sub add_record {
    ($dbh, @db_line) = @_;
    ($last, $first, $category, $title, $email, $accepted, $notes) = @db_line;
    #print "debug: add record: @db_line in database\n<br>";
       my $string ="INSERT INTO mm (first, last, email, phone, title, category, notes, accepted)  
        VALUES ( ?, ?, ?, ?, ?, ?, ?, ?);";

  my $sth = $dbh->prepare($string) or die("Can't prepare string $string: ", $dbh->errstr);

    $sth->execute( $first, $last, $email, $phone, $title, $category, $notes, $accepted ) || 
  die "Could not execute query to insert data.<br>";
  
}

######################################################################
#### delete_all      delete all records from upload option  ##########
######################################################################

sub delete_all 
{
    my $dbh = shift();
    my $string = "DELETE  FROM mm";
   
    $dbh->do( $string );
}


######################################################################
#### load_all_records             ##########
######################################################################

sub load_all_records {
    my($dbh, $sort, $table, $field_names, $accept_flag) = @_;
    #print "debug in load_all_records: sort: $sort, table: $table, field_names: $field_names", " accept_flag: $accept_flag\n<br>";
    #exit;
    
    #if($accept_flag == 1) {
        #print "debug in accept flag<br>";
        #my $sth = $dbh->prepare( 
        #    "SELECT $field_names FROM $table WHERE accepted='Yes' ORDER BY $sort " );
    #}else {
        #print "debug in accept flag<br>";
        #exit;
        my $sth = $dbh->prepare( 
             "SELECT $field_names FROM $table ORDER BY $sort" );
        #my $sth = $dbh->prepare( 
            #"SELECT $field_names FROM $table WHERE last like '%Deg%' " );
    #}
    $sth->execute();
    #print "debug in s all_records: done executing\n<br>";
    
    $rows = $sth->fetchall_arrayref();
    $sth->finish();
    #@test = @{$rows};
    #foreach (@test){
        #print "debug in load_all_records: rows: @{$_}\n<br>";
    #}
}

######################################################################
#### load_accepted_records            ##########
######################################################################

sub load_accepted_records {
    my($dbh, $sort, $table, $field_names, $accept_flag) = @_;
    #print "debug in load_all_records: sort: $sort, table: $table, field_names: $field_names", " accept_flag: $accept_flag\n<br>";
    #exit;
    
    #if($accept_flag == 1) {
        #print "debug in accept flag<br>";
        #my $sth = $dbh->prepare( 
        #    "SELECT $field_names FROM $table WHERE accepted='Yes' ORDER BY $sort " );
    #}else {
        #print "debug in accept flag<br>";
        #exit;
        my $sth = $dbh->prepare( 
            "SELECT $field_names FROM $table WHERE accepted='$accept_flag' ORDER BY $sort" );
        #my $sth = $dbh->prepare( 
            #"SELECT $field_names FROM $table WHERE title like '%test%' " );
    #}
    $sth->execute();
    #print "debug in s all_records: done executing\n<br>";
    
    $rows = $sth->fetchall_arrayref();
    $sth->finish();
    @test = @{$rows};
    foreach (@test){
        #print "debug in load_all_records: rows: @{$_}\n<br>";
    }
}
######################################################################
#### load_partial_records           ##########
######################################################################

sub load_partial_records {
    my($dbh, $table, $field_names, $where) = @_;
    #print "\n<br>debug in load_partial_records: table: $table, field_names: $field_names, where: $where\n<br>";
    #print "debug in load_partial_records with field_names: $fieldnames<br>\n";
    
    my $sth = $dbh->prepare("SELECT $field_names FROM $table WHERE email='$where'");
        
    $sth->execute();
    #print "debug in partial_records: done executing\n<br>";
   
    $rows = $sth->fetchall_arrayref();
    #@rows_values = $sth->fetchrow_array;
    $sth->finish();
    #@test = @{$rows};
    #foreach (@test){
        #print "debug in load_partial_records: rows: @{$_}\n<br>";
    #}
}

######################################################################
#### make_backup_form                     ####################
######################################################################

sub make_backup_form 
{
    print "<center><h2>Back up the students and projects database</h2></center>",
                "<h3>Present Backed up Files</h3>",
                "<ul>";
                    
   @files = `ls *.txt`;
   
   foreach (@files) {
        $_ =~ s/\.txt//;
        print "<li>$_";
   }
   
    print   "<form action=\"mm_projects.cgi\" method=\"post\" ",
                "<p></ul>Enter a name of the file to back up (no spaces, start with letter, no special ",
                        "charaters like '/'):<p> ",
                textfield( -name => 'backup_file', size => '20'),
                submit( -value => "Back up the file" ),
          hidden( { -name => "LAST", -value => "BACKUP", 
                   -override => 1 }),
                end_form();
                exit;
}

######################################################################
#### do_backup                          ####################
######################################################################

sub do_backup 
{
    my $dbh = shift(); 
    my $file = param( backup_file );
    $file .= ".txt";
   
    &load_all_records($dbh, "last, first ASC", "mm", $mm_fields);     #into @rows
    @students = @{$rows};
    #print "debug in make_backup: students array: @students\n<br>";
    
    foreach $student (@students){
        ($last, $first, $email, $phone) = @{$student};
        #print "debug before calling parial_records: last: $last, email: $email\n<br>";
        &load_partial_records($dbh, "mm_projects", $projects_fields, $email);   #into @rows
        foreach $row (@{$rows}) {
            push( @{$full_rows  }, [ $last, $first, $email, $phone, @{$row} ] );
        }
    }
    #print "debug in view: full_rows array: @{$full_rows}\n<br>";
          
    foreach my $row ( @$full_rows ) { #for each row (projects) of the database
        my $row_string = "";
        foreach (@$row) {   #for each field
                $_ =~ s/\n/%25/gm;
                $_ =~ s/\cM/%23/gm;
            $row_string .= $_ . "|";
        }
        $row_string .= "\n";
        #print "debug in make_backup with row_string: $row_string<br>\b";
        push ( @backup, $row_string );
    }
    open (IN, ">$file") or die("problem writing to file: $file<br>\n");
    foreach (@backup) {
        print IN $_;
    }
}


######################################################################
#### do_mail                ##########
######################################################################
# this routine no complete
sub do_mail {
    my $subject = param('subject');
    my $message = param('message');
    my $accepted = param('ACCEPTED');
    
    print "debug in do_mail with accepted: $accepted\n<br>";
    #exit;
    
    my $dbh = shift(); 
    my $project_fields = "category, title, email";
    my $student_fields = "last, first, email";
    
    &load_accepted_records($dbh, "category ASC", "mm_projects", $project_fields, $accepted);  #into @rows
    @projects = @{$rows};
    #print "debug in view: projects array: @projects\n<br>";
    
    foreach $projects (@projects){
        ($category, $title, $email) = @{$projects};
        #print "debug before calling partial_records: category: $category, title: $title", "email: $email\n<br>";

        &load_partial_records($dbh, "mm", $student_fields, $email);   #into @rows
        foreach $row (@{$rows}) {
            push( @{$full_rows  }, [ $category, $title, @{$row} ] );
        }
    }
     
    foreach my $row ( @$full_rows ) {
        open (MAIL, "|$mailprog -t") or dienice("Can't access $mailprog!\n"); 
        
        #print "debug in do_mail last foreach with message: $message\n<br>";
        my @test = @$row;
        #print "debug in do_mail with test array: @test<br>\n";
        #print "debug in do_mail with test array[4]: $test[4]<br>\n";
        $category = $test[0];
        $title = $test[1];
        $last = $test[2];
        $first = $test[3];
        $email = $test[4];
        my $temp_message = $message;
        $temp_message =~ s/\|last\|/$last/g;
        $temp_message =~ s/\|first\|/$first/g;
        $temp_message =~ s/\|title\|/$title/g;
        #print "debug in do_mail with temp_message:\n<br>$temp_message<br>\n";
  print "mail to: $first $last $email\n<br>";
  $email =~ s/@/\@/;
  print MAIL "To: $email\n";
  print MAIL "From: Multimedia\n";
  print MAIL "Reply-to: Multimedia <ajauco\@ohlone.edu>\n";
  print MAIL "Subject: $subject\n\n";
        print MAIL "$temp_message";
        print MAIL "\n.\n";
        close (MAIL);
    }
    
}


######################################################################
#### displayEmailForm             ##########
######################################################################
# this routine no complete
sub displayEmailForm  {
    my($dbh, $accepted) = (shift, shift);
    
    if($accepted eq "Yes") {
        $message = "Dear |first| |last|\n\n" .

                "Congratulations! Your project titled '|title|'\n".
                "has been accepted into the Multimedia Festival and\n".
                "your work will be displayed in HH116 on May 12, 2010.\n\n".

                "Please come and enjoy the nice day we have planned for you. You may\n".
                "invite others who would enjoy the show and share your accomplishments.\n\n" .

        "Festival Schedule\n" .
        "4:00 to 7:00 PM | Exhibit of Student Work\n" .
        "5:00 to 5:30 PM | Remembering Pilar Lewis\n" .
        "5:30 to 6:30 PM | Reception\n" .
        "6:30 to 7:00 PM | Awards Ceremony\n\n" .
        
        "Thanks again for your dedication and hard work.\n\n".

                "Sincerely,\n".
                "Alejandro Jauco\n".
                "Multimedia Faculty\n\n".
        
                "Ohlone College\n".
                "43600 Mission Boulevard\n".
                "Fremont, CA 94539-0390\n\n".

        "Email: ajauco\@ohlone.edu\n" .
                "http://www2.ohlone.cc.ca.us/instr/multimedia" ;
         $subject = "Multimedia Acceptance Letter";
    }else {
        $message = "Dear |first| |last|\n\n" .
                
                "We regret to inform you that \n".
                "your submission '|title|' was not accepted \n".
                "by the juror of our show, but we hope you will know that your work is of merit, \n".
                "and we encourage you to try again next year.\n\n".

                "Please come to support your fellow students, and enjoy the nice day we have planned \n".
                "for you and your guests.\n\n".
                    
        "Festival Schedule\n" .
        "4:00 to 7:00 PM | Exhibit of Student Work\n" .
        "5:00 to 5:30 PM | Remembering Pilar Lewis\n" .
        "5:30 to 6:30 PM | Reception\n" .
        "6:30 to 7:00 PM | Awards Ceremony\n\n" .
        
        "Thanks again for your dedication and hard work.\n\n".

                "Sincerely,\n".
                "Alejandro Jauco\n".
                "Multimedia Faculty\n\n".
        
                "Ohlone College\n".
                "43600 Mission Boulevard\n".
                "Fremont, CA 94539-0390\n\n".

        "Email: ajauco\@ohlone.edu\n" .
                "http://www2.ohlone.cc.ca.us/instr/multimedia" ;

      $subject = "Multimedia Letter";
    }
   #print "debug in displayEmailForm with message: $message<br>\n";
   
   print <<end_html;
   <form action="mm_projects.cgi" method="post">
    <table summary="Form to enter an email message into (for sending to students)" width="590">
    <tr>
      <td width="150">
        <font face="Arial, Helvetica, sans-serif">Subject :</font>
      </td>
      <td width="490">
        <input type="text" name="subject" size="70" value="$subject" maxlength=200>
      </td>
    </tr>
    <tr>
      <td width="100">
        <font face="Arial, Helvetica, sans-serif">Message:</font>
      </td>
      <td width="490">
        <textarea name="message" rows="20" cols="80" wrap="on">$message</textarea>
      </td>
    </tr>
    <tr>
      <td>&nbsp;</td>
      <td>
        <input type="submit" value="Submit">
      </td>
    </tr>
  </table>
  <input type="hidden" name="LAST" value="EMAIL">
  <input type="hidden" name="ACCEPTED" value="$accepted">
</form>
  
end_html
   
    $scores_fields = "category, title, email, notes, criteria, ". 
                "tech_merit, creative, groups, accepted, group_names, description";
    $student_fields = "last, first, email";
    if ($accepted eq "Yes" ) {            
        &load_accepted_records($dbh, "category ASC", "mm_projects", $scores_fields, "Yes"); #into @rows
    }else {
         &load_accepted_records($dbh, "category ASC", "mm_projects", $scores_fields, "No");
    }
    @projects = @{$rows};
    #print "debug in view: projects array: @projects\n<br>";
    
    foreach $projects (@projects){
        ($category, $title, $email, $notes, $criteria, $tech_merit, $creative, $groups, 
    $accepted, $group_names, $description) = @{$projects};
        #print "debug before calling partial_records: category: $category, title: $title", "email: $email\n<br>";

        &load_partial_records($dbh, "mm", $student_fields, $email);   #into @rows
        foreach $row (@{$rows}) {
            push( @{$full_rows  }, [ $category, $title, @{$row}, $accepted ] );
        }
    }
  my $tablerows = 
  Tr( th( { -bgcolor => "#dddddd", -align=>'left' }, 
              [ "Category", "Title" ] ),
          th( { -bgcolor => "#dddddd" }, 
    [  "Last", "First", "Email", "Accepted" ] ) );
          
   foreach my $row ( @$full_rows ) {
        #print "debug in viewScores with row: @$row<br>\n";

    ######## get criteria scores for for project
        
        my @test = @$row;
        #print "debug in viewScores with test array: @test<br>\n";
        #print "debug in viewScores with test array[6]: $test[6]<br>\n";
        
        my @criteria_values = ();
        @criteria_values = split(/\|/, $test[6]);
        #print "debug in get_criteria_values with new criteria_values array: @criteria_values<br>\n";
        #print "debug in get_criteria_values with \$row =>[6]: $row =>[6])\n<br>";
        
    ######## add up the scores
        my $total = 0;
        foreach (@criteria_values) {
            $total += $_;
        }
        $total +=  $test[7];
        $total +=  $test[8];
        #print "debug in viewScores with total: $total<br>\n";
        
    ######## add total to the end of the row of data
        unshift ( @{$row}, $total);
        #$tablerows .= Tr( td( { -bgcolor => "#dddddd" }, $row ) );
    }
    ######## sort by score (list is already sorted by category)
   $sorted =  [sort byscore @$full_rows]; 
   #print "debug with sorted array: @sorted<p>";
   $full_rows = $sorted;
   
    ###### sort list ascending by category
    $sorted = [sort  bycategory @$full_rows];
    $full_rows = $sorted;

     foreach my $row ( @$full_rows ) {
        shift ( @{$row});
        $tablerows .= Tr( td( { -bgcolor => "#dddddd" }, $row ) );
     }
       
    print   h3( "Email goes to the following students" );
    &print_link;
    print  table( { -border => 1, -cellpadding => 5, 
                  -cellspacing => 0 }, $tablerows ),
         br(), br(),
         "Query contains ", b( scalar( @$full_rows ) ), 
         " records.",br(), br();
}

######################################################################
#### do_mail_comments             ##########
######################################################################
sub do_mail_comments  
{
    my $dbh = shift(); 
    my $subject = param('subject');
    my $message = param('message');
    #print "debug in do_mail_comments with subject: $subject and message: $message<br>\n";

    &load_all_records($dbh, "last, first ASC", "mm", $mm_fields);     #into @rows
    @students = @{$rows};
    #Enter and Score Projects in view: students array: @students\n<br>";
    
    foreach $student (@students){
        ($last, $first, $email, $phone) = @{$student};
        #print "debug before calling parial_records: last: $last, email: $email\n<br>";
        &load_partial_records($dbh, "mm_projects", $projects_fields, $email);   #into @rows
        foreach $row (@{$rows}) {
            push( @{$full_rows  }, [ $last, $first, $email, $phone, @{$row} ] );
        }
    }
    #print "debug in do_mail_comments with full_rows array: @{$full_rows}\n<br>";
    foreach $project (@$full_rows) {
        @projects_values = @$project;
        my $i = 0;
        foreach (@projects_values) {
            
            #print "debug in do_mail_comments with projects_values[$i] array: $_<br>\n";
            $i++;
        }

  #if ($projects_values[5] eq "test3") {  #use this if to test email one project

######## get criteria for category
        my $category = $projects_values[4];
        #print "debug in get_criteria_for_categories with category: $category<br>\n";
        
         my $sth = $dbh->prepare(  
            "SELECT criteria FROM mm_criteria WHERE category = '$category'" );
  $sth->execute();
        my @criteria_ids = ();
  @criteria_ids = $sth->fetchrow_array;
        #print "debug in get_criteria with criteria_ids array: $criteria_ids[0]<br>\n";

        @criteria_ids = split(/\|/, $criteria_ids[0]);
        
######## get criteria for for project
        
        my @criteria_values = ();
        @criteria_values = split(/\|/, $projects_values[12]);
        ##print "debug in get_criteria_values with new criteria_values array: @criteria_values<br>\n";
        for($x=0; $x<@criteria_values; $x++) {
            #print "debug in get criteria with criteria_values[$x]: $criteria_values[$x]<br>\n";
        }
        #print "debug in get_criteria_values with projects_values[12]: $projects_values[12])\n<br>";

    
######## get categories info  - for pull down menu
        my $sth = $dbh->prepare(  
            "SELECT category, criteria FROM mm_criteria order by category" );
  $sth->execute();
        @cat_ids = ();
  while ( my @row = $sth->fetchrow_array ) {
            push( @cat_ids, $row[ 0 ] );
  }
        
######## Starting the email
        my $i = 0;  #used later in displaying criteria (can't be initialized inside table)
        
        open (MAIL, "|$mailprog -t") or dienice("Can't access $mailprog!\n"); 
        
        #print "debug in do_mail last foreach with message: $message\n<br>";
        #print "debug in do_mail with test array: @test<br>\n";
        #print "debug in do_mail with test array[4]: $test[4]<br>\n";
        $category = $projects_values[4];
        $title = $projects_values[5];
  $description = $projects_values[17];
        $last = $projects_values[0];
        $first = $projects_values[1];
        $email = $projects_values[2];
        $group = $projects_values[15];
        $group_names = $projects_values[16];
        if ($group eq "Yes") {
            $group = "Yes\n";
            $group .= "Group Members:\n" . $group_names . "\n";
        }else {
            $group = "No";
        }
        my $criteria = ();
        #### criteria
                        foreach (@criteria_ids) {
                                $criteria .= $_ . ": ";
                                foreach (0 .. 10) {
                                    if($_ ne $criteria_values[$i]) {
                                    }
                                    else {
                                        $criteria .= $rubric[$_] . "\n";
                                    }
                                }
                                $i++;
                        }



        my $notes = $projects_values[10];
        my $temp_message = $message;
        $temp_message =~ s/\|last\|/$last/g;
        $temp_message =~ s/\|first\|/$first/g;
        $temp_message =~ s/\|title\|/$title/g;
        $temp_message =~ s/\|description\|/$description/g;
        $temp_message =~ s/\|group\|/$group/g;
        $temp_message =~ s/\|category\|/$category/g;
        $temp_message =~ s/\|criteria\|/$criteria/g;
        $temp_message =~ s/\|notes\|/$notes/g;
  #print "debug in do_mail with temp_message:\n<br>$temp_message<br>\n";

  #print "mail to: $first $last $email\n<br>";
  $email =~ s/@/\@/;
  
  print MAIL "To: $email\n";
  print MAIL "From: Multimedia\n";
  print MAIL "Reply-to: Multimedia <ajauco\@ohlone.edu>\n";
  print MAIL "Subject: $subject\n\n";
        print MAIL "$temp_message";
        print MAIL "\n.\n";
        close (MAIL);
        print "Emailed: $first $last at $email\n<br>";
    }
  #}  #end of if statement to test one project
}

######################################################################
#### displayEmailCommentsForm           ##########
######################################################################
# this routine no complete
sub displayEmailCommentsForm  {
        $message = "Dear |first| |last|\n\n" .

               "Here are the results of your project entry '|title|':\n" .
               
               "Group: |group|\n".
               "Category: |category|\n" .
               
               "The following criteria were graded as 0-Lowest to 10-Highest:\n" .
               "|criteria|\n".
               
               "Juror's Notes:\n".
               "|notes|\n".
               "________________________________________________________\n\n" . 
               
               "Thank you for all of your work, see you next year!\n\n" .
               
                "Sincerely,\n".
                "Alejandro Jauco\n\n".
                "Multimedia Department\n".

                "Ohlone College\n".
                "43600 Mission Boulevard\n".
                "Fremont, CA 94539-0390\n\n".

        "Email: ajauco\@ohlone.edu\n" .
                "http://www2.ohlone.cc.ca.us/instr/multimedia" ;

        $subject = "Multimedia Judging Scores and Comments";
    
   #print "debug in displayEmailForm with message: $message<br>\n";
   
   print <<end_html;
   <form action="mm_projects.cgi" method="post">
    <table summary="Form to enter an email message into (for sending to students)" width="590">
    <tr>
      <td width="150">
        <font face="Arial, Helvetica, sans-serif">Subject :</font>
      </td>
      <td width="490">
        <input type="text" name="subject" size="70" value="$subject" maxlength=200>
      </td>
    </tr>
    <tr>
      <td width="100">
        <font face="Arial, Helvetica, sans-serif">Message:</font>
      </td>
      <td width="490">
        <textarea name="message" rows="20" cols="80" wrap="on">$message</textarea>
      </td>
    </tr>
    <tr>
      <td>&nbsp;</td>
      <td>
        <input type="submit" value="Submit">
      </td>
    </tr>
  </table>
  <input type="hidden" name="LAST" value="EMAIL_COMMENTS">
 </form>
  
end_html
}

######################################################################
#### do_mail_test                       ##########
######################################################################
sub do_mail_test  
{
    my $dbh = shift(); 
    my $subject = param('subject');
    my $message = param('message');
    my $email = param('email');
    #print "debug in do_mail_comments with subject: $subject and message: $message<br>\n";
 
######## Starting the email
        
        open (MAIL, "|$mailprog -t") or dienice("Can't access $mailprog!\n"); 
        
  
  print MAIL "To: $email\n";
  print MAIL "From: Multimedia\n";
  print MAIL "Reply-to: Multimedia <ajauco\@ohlone.edu>\n";
  print MAIL "Subject: $subject\n\n";
        print MAIL "$message";
        print MAIL "\n.\n";
        close (MAIL);
        print "Emailed: to $email\n<br>";
  #}  #end of if statement to test one project
}



######################################################################
#### displayEmailTestForm                   ##########
######################################################################
#
sub displayEmailTestForm  {
    $message = "if you receive this message, mm email must be working";
        $subject = "Multimedia program email test";
    
   #print "debug in displayEmailTestForm with message: $message<br>\n";
   
   print <<end_html;
   <form action="mm_projects.cgi" method="post">
    <table summary="Enter an email to test mm email program" width="590">
  <tr>
      <td width="150">
        <font face="Arial, Helvetica, sans-serif">email :</font>
      </td>
      <td width="490">
        <input type="text" name="email" size="70" maxlength=200>
      </td>
    </tr>
 
    <tr>
      <td width="150">
        <font face="Arial, Helvetica, sans-serif">Subject :</font>
      </td>
      <td width="490">
        <input type="text" name="subject" size="70" value="$subject" maxlength=200>
      </td>
    </tr>
    <tr>
      <td width="100">
        <font face="Arial, Helvetica, sans-serif">Message:</font>
      </td>
      <td width="490">
        <textarea name="message" rows="20" cols="80" wrap="on">$message</textarea>
      </td>
    </tr>
    <tr>
      <td>&nbsp;</td>
      <td>
        <input type="submit" value="Submit">
      </td>
    </tr>
  </table>
  <input type="hidden" name="LAST" value="EMAIL_TEST">
 </form>
  
end_html

}

######################################################################
#### create form to obtain sort up to three fields                 ##########
######################################################################
                        
sub make_sort_form {
        
        # populate the values in the dropdown menu for sort form
        %sort_menu =(                   
                                        "" => "Select a field, please",
                      first => "first name",
                                        last => "last name",
                                        email => "email",
                                        phone => "phone number",
                                        title => "title",
                                        category => "category",
                                        accepted => "accepted",
                                        notes => "notes",
                                        class => "class",
          highschool => "highschool",
                                        groups => "groups",
                                        softwware => "software",
                                        semester => "semester",
                                        year => "year",
                                        criteria => "criteria",
                                        tech_merit => "technical merit",
                                        group_names => "group names",
          description => "description"
                                        );
                                        
        # generate html code to build form
                        
         print <<"    EndHTML";
        <h1>MM Festival Projects</h1>
        <h3>Choose a sort order for viewing:</h3>
                                        
<SCRIPT>                
<!-- javascript function to verify form data
// Warn user if no fields were selected from dropdown menu. 
        function isFilled(form) {
        if (form.sort1.value=="" && form.sort2.value=="" && form.sort3.value=="" ) {
        alert("Sorry, you did not select a field.\\nPlease select at least one field!")
      return false
      }
   }
//-->
</SCRIPT>
                                        
                                        
        <form method='post' onSubmit='return isFilled(this)' action=mm_projects.cgi>
        <table border rules='rows' width='50%' cellpadding='8'>
        <tr>
                <td>
                        Sort by &nbsp;
                                        
    EndHTML
                        
    # building the pulldown selection menu
        print popup_menu( -name => 'sort1',
                                        -value => \%sort_menu,
                                        -labels => \%sort_menu );

         print <<"    EndHTML2";
                </td>
                <td>
                        <input type='radio' name='order1' value='ASC' />Ascending   
                        <br>
                        <input type='radio' name='order1' value='DESC' />Descending
                </td>
        </tr>

        <tr>
                <td>                    
                        Then by &nbsp;  
        
    EndHTML2
        
    # building the downdown selection menu
        print popup_menu( -name => 'sort2',
                                        -value => \%sort_menu,
                                        -labels => \%sort_menu );
                        
    
         print <<"    EndHTML3";
                </td>
                <td>
                        <input type='radio' name='order2' value='ASC' />Ascending
                        <br>
                        <input type='radio' name='order2' value='DESC' />Descending
                </td>
        </tr>
                        
        <tr>
                <td>
                        Then by &nbsp;

    EndHTML3
                
    # building the downdown selection menu
        print popup_menu( -name => 'sort3',
                                        -value => \%sort_menu,
                                        -labels => \%sort_menu );
    
         print <<"    EndHTML4";
                </td>
                <td>
                        <input type='radio' name='order3' value='ASC' />Ascending
                        <br>
                        <input type='radio' name='order3' value='DESC' />Descending
                </td>
        </tr>
                        
    <tr>
                <td colspan='2' align='center'>
         <input type="hidden" name="LAST" value="SORT_ORDER" />
                        <input type='submit' value='View Sorted Projects' /> &nbsp;&nbsp;
                        <input type='reset' type='Reset' />
                </td>
        </tr>
        </table>
        </form>
    
    EndHTML4
    
        
        return;
                                        
} #end make_sort_form

sub make_modifiedView_form {
    print <<"    EndHTML";
        <h1>MM Festival Projects Database: Modified View</h1>
        <h3>Select fields to view:</h3>
                                        
                                        
        <form method='post' action=mm_projects.cgi>
        <table border rules='rows' cellpadding='5'>
        <tr>
                <td>
                        Fields:<br />
    EndHTML

    print checkbox_group(
        -name=>'mviewfields',
        -values=>\%mview_menu,
        -labels=>\%mview_menu,
        -linebreak=>'true');

    print <<"    EndHTML";
                </td>
                <td></td> <!--cries-->
        </tr>
        <tr>
                <td colspan='2' align='center'>
         <input type="hidden" name="LAST" value="MODIFIED_VIEW" />
                        <input type='submit' value='Display Selected Fields' /> &nbsp;&nbsp;
                        <input type='reset' type='Reset' />
                </td>
        </tr>
        </table>
        </form>
    EndHTML

    return;
} # end make_modifiedView_form

######################################################################
#### generic query to pull data from the database           ##########
######################################################################
        
sub getRecords{
        my ($dbh, $mySQLString) =  @_;
    #print("<p>Here in getRecords value of SQL string is $mySQLString</p>\n");
       
        my $sth = $dbh->prepare($mySQLString);
    $sth->execute();
                  
    my $rows = $sth->fetchall_arrayref();
    #print("debug:<p>Here in getRecords value of full_row array is: @{$rows}</p>\n");
        $sth->finish();
    return $rows;
} # end getRecords
        
