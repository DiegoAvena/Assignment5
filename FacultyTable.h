#ifndef FACULTY_TABLE_H
#define FACULTY_TABLE_H

#include "BinarySearchTree.h"
#include "Faculty.h"
#include "FileInputManager.h"
#include "DoubleLinkedList.h"
#include "Student.h"
#include "DoubleLinkedList.h"
#include <fstream>
#include "FileOutputManager.h"
#include <stdlib.h>
#include <iostream>
#include "UndoManager.h"

/*

-Extends from a generic BinarySearchTree datastructure to describe the more specific
components of a tree that stores faculty members, such as methods that can add a faculty member into the tree with the correct
information like their name, level, advisees, etc.

*/
class FacultyTable: public BinarySearchTree<int, Faculty>, public FileInputManager<FacultyTable>, public FileOutputManager<FacultyTable> {

private:

  Faculty* facultyToAddToTable;
  //DoubleLinkedList< DoubleLinkedList<unsigned int>* >* listOfAdviseeListsToDeleteLater;

  //for filling this table up from a text file:
  int currentLineNumber; //the current line number we are on for making a faculty object, at 5 + numberOfAdvisees the faculty object is ready to be made, and this is set back to 1 to build another faculty object
  int numberOfAdvisees; //the number of advisees this faculty member will have

  bool commandModifiedTableSuccessfully; //a flag that signals to the program that the database was changed sucessfully so that a snapshot taken of the database prior to the changes can be saved for potential rollback

  void traverseTreeToCopyIt(TreeNode<int, Faculty>* node); //traverses the tree to copy it, used by the copy constructor

public:
  DoubleLinkedList<int>* listOfIDSThatExistInTree; //keeps track of all of the ids of the faculties that are currently in the tree, mainly to randomly assign students to faculty advisors when need be

  FacultyTable(); //Default constructor

  FacultyTable(int rootKey, Faculty rootValue); //overloaded constructor

  FacultyTable(const FacultyTable& tableToCopy); //copy constructor

  ~FacultyTable(); //destructor

  bool getCommandModifiedTableSuccessfully(); //accessor method for the flag that signals if a command modified this faculty table

  void setCommandModifiedTableSuccessfully(bool commandModifiedTableSuccessfully); //mutator method for setting commandModifiedTableSuccessfully flag

  void setUpTable(FacultyTable& objectToBuildUsingTheTextFile); //sets up the faculty table at the start of the program by reading through the studentTable.txt file

  void deleteListOfAdviseesForEachFaculty(TreeNode<int, Faculty>* node); //deletes the list of advisees that was dynamically allocated for every node in the faculty tree/table

  void readFromFileWithSpecificRules(std::string line); //reads from the file opened by FileInputManager and correctly makes the faculty objects following the rules set for the facultyTable.txt file

  void printFaculty(TreeNode<int, Faculty>* node, BinarySearchTree<int, Student>& tree); //prints all of the faculty members in the current database in ascending ID order

  void printASpecificFacultyMember(BinarySearchTree<int, Student>& tree); //prints the information for a specific faculty member

  void printAdviseeInfoForSpecificFacultyMember(BinarySearchTree<int, Student>& tree); //prints all advisee info for all advisees for a specific faculty member

  void initializeReferentialIntegrityOfTable(TreeNode<int, Faculty>* node, BinarySearchTree<int, Student>& treeToBaseReferenceOffOf); //initializes the referential integrity for this faculty table/tree right when the program starts

  void AddAFacultyMember(BinarySearchTree<int, Student>& studentTreeReference);

  void removeAFacultyMember(BinarySearchTree<int, Student>& studentTreeReference); //removes a faculty member from the database

  void removeAnAdvisee(BinarySearchTree<int, Student>& studentTreeReference); //removes an advisee for a faculty member:

  void writeToFileUsingSpecficRules(std::ofstream* fileToWriteTo, TreeNode<int, Faculty>* node); //the method that contains the more specific rules needed by the file fileOutputer to serialize this faculty table

};

#endif
