#ifndef STUDENT_TABLE_H
#define STUDENT_TABLE_H

#include "BinarySearchTree.h"
#include "Student.h"
#include <fstream>
#include "FileInputManager.h"
#include "Faculty.h"
#include <stdlib.h> 
#include "DoubleLinkedList.h"
#include "FacultyTable.h"
#include <iostream>

/*

-Extends from a generic BinarySearchTree datastructure to define a more specific type of tree
for a student database. Expands from FileInputManager<StudentTable> in order to use its readFile method to read the student
information from the .txt file. Expands from FileOutputManager to use its writeToFile method to serialize the student table when
the program exits.

*/
class StudentTable: public BinarySearchTree<int, Student>, public FileInputManager<StudentTable>, public FileOutputManager<StudentTable> {

private:
  int currentLineNumber; //keeps track of the number of lines read that represent data for 1 student object being made from a .txt file (the max lines is 6, at 6 lines 1 student object is created following my rules for the student.txt file)

  Student studentToAddToTable; //stores all of the data being read from the student.txt file so that when currentLineNumber is at 6, this student object can be added into the student tree with all of the info read from the .txt file

  void traverseTreeToCopyIt(TreeNode<int, Student>* node); //traverses the entire tree in order to copy its nodes into a new tree

  bool commandModifiedTableSuccessfully; //a flag that tells the program if a command issued from this student table or tree changed the data base, so that the snapshot of the database prior to the change can be pushed onto the stack for potential rollback

public:

  bool getCommandModifiedTableSuccessfully(); //accessor method for commandModifiedTableSuccessfully

  void setCommandModifiedTableSuccessfully(bool commandModifiedTableSuccessfully); //Mutator method for commandModifiedTableSuccessfully

  StudentTable(); //default constructor

  StudentTable(int rootKey, Student rootValue); //overloaded constructor, sets the root of the tree using rootKey and rootValue

  StudentTable(StudentTable& tableToCopy); //copy constructor

  ~StudentTable(); //destructor

  void setUpTable(StudentTable& studentTableToBuild); //initializes the table by reading over the setUpTable.txt file so that Student nodes can be made from its data and added into this student tree

  void printStudents(TreeNode<int, Student>* node, BinarySearchTree<int, Faculty>& tree); //prints the information of every student in the studentTable, including the information of their advisor, by ascending student ID

  void printASpecificStudent(BinarySearchTree<int, Faculty>& tree); //prints the information for a specific student

  void printFacultyInformationForASpecificStudent(BinarySearchTree<int, Faculty>& tree); //prints the advisor info for a specific student

  void initializeReferentialIntegrityOfTable(TreeNode<int, Student>* node, FacultyTable& treeToBaseReferenceOffOf); //insures that upon the start of the program, every student is assigned to a faculty member that does exist in the faculty table,

  void readFromFileWithSpecificRules(std::string line); //allows the text read from the file using FileInputManager to be saved into the correct memory slots for the student object, so that it is made correctly:

  void addAStudent(FacultyTable&  facultyTree); //adds a student to the database

  void removeAStudent(FacultyTable& facultyTree); //removes a student from the student table provided the user enters valid Student and faculty IDs

  void changeStudentsAdvisor(FacultyTable& facultyTree); //Changes a students advisor provided the student ID given is valid and the faculty ID given is valid

  void writeToFileUsingSpecficRules(std::ofstream* fileToWriteTo, TreeNode<int, Student>* node); //Allows the FileOutputManager to write back to a file following the rules set for how a studentTable.txt file should be organized.

};

#endif
