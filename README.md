# Student and Faculty Database

----------------------------------------------------------------------------------------------------------------------------------

-A graph based database system that makes use of Binary Search trees to keep track of
faculty and student records.

----------------------------------------------------------------------------------------------------------------------------------

-IMPORTANT NOTES FOR THIS PROGRAM:

1.) Only values greater then or equal to 0 should be entered for student and faculty ids

2.) These are the rules to follow when writing your own facultyTable.txt file for this program to read through:

    -THE FORMAT FOR EACH LINE:

    LINE 1.) integer ID of faculty member
    LINE 2.) name of the faculty member
    LINE 3.) level of the faculty member
    LINE 4.) department of the faculty member
    LINE 5.) The N number of advisees this faculty member has
    LINES 6 through (N - 1).) Integer ID of advisee

    -As an example:

    2244555
    Dr. A
    Lecturer
    CPSC
    2
    0011444
    2211777
    1188999
    Dr. B
    Lecturer
    Math
    1
    8855111  

    -This file should be saved in the same directory as the executable and source code files and should be named: facultyTable.txt

3.) These are the rules to follow when writing your own studentTable.txt file for this program to read through:

    -THE FORMAT FOR EACH LINE:

    LINE 1.) Integer student ID
    LINE 2.) Name of the student
    LINE 3.) Level of the student
    LINE 4.) Major of the student
    LINE 5.) integer ID of the student's advisor
    LINE 6.) The GPA of the student

    -As an example:

    0011444
    StudentA Name
    Sophomore
    CPSC
    1100222
    3.5
    1122333
    StudentB Name
    Senior
    Math
    1133444
    3.6

    -This text file should be saved in the same directory as the executable and source code files, and named: studentTable.txt

4.) If the student table text file is missing or empty but the faculty table text file is not, then the database loads by setting all of the faculty members to have no advisees. If the faculty table is empty or missing and the student table is present, then every student is set to have no advisor by setting their advisor ID to -1 (this is why -1 should not be used as an ID).

5.) When advisors are added into the database and there are students that do not have an advisor assigned to them, the program will not automatically assign that student to this new advisor, it is up to the inputer to assign this student to that advisor using the correct option.

6.) When referential integrity is set and students are assigned to fake advisors are none and the faculty table is not empty, then these students are randomly assigned to faculty members in the current faculty table.

6.) Referential integrity is first set up for the student table and then for the faculty table, so if the faculty table has faculty members with real advisee IDs, but the student table has those advisees listed as having no advisors, then because these students are randomly assigned to faculty advisors in such cases then these faculty members may end up not being assigned to these students when the database options load.

7.) When a student is removed from and advisor because the inputer has either removed this advisee or this faculty member, this student is randomly assigned to another faculty advisor in the database.

8.) The range for ID's is 0 to 2147483647, anything bigger then 2147483647 will cause cin and stoi to fail. And I say 0 because - IDS should also not be entered. (range of int cited from: https://www.tutorialspoint.com/cplusplus/cpp_data_types.htm)

9.) Once rollback has 5 snapshots of the database, if another snapshot needs to be saved, then the oldest snapshot (the item at the bottom of the stack) is removed in order to make room for the new snapshot.

10.) Changing a student's advisor or removing an advisee from an advisor is a change that can be undone by rollback, in addition to removal and addition of a students and faculty members.

----------------------------------------------------------------------------------------------------------------------------------
REFERENCES:
-For the height of a tree: https://www.geeksforgeeks.org/write-a-c-program-to-find-the-maximum-depth-or-height-of-a-tree/

-For why rand() needs to be seeded at the start of the program: http://www.math.uaa.alaska.edu/~afkjm/csce211/fall2018/handouts/RandomFunctions.pdf

-For how to clear the error state of cin, or how to use cin.clear(): https://stackoverflow.com/questions/12408848/what-does-cin-do-when-there-is-an-error

-For how to prevent cin from skipping input prompts when user presses enter for 1 input: http://www.cplusplus.com/reference/istream/istream/ignore/

-For how to allow the user to enter spaces in between the names of students and faculty members without cin stopping before the space: https://stackoverflow.com/questions/29630513/difference-between-cin-and-cin-get-for-char-array

-For the range of the int datatype, I used: https://www.tutorialspoint.com/cplusplus/cpp_data_types.htm
