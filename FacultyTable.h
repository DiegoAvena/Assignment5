#ifndef FACULTY_TABLE_H
#define FACULTY_TABLE_H

#include "BinarySearchTree.h"
#include "Faculty.h"
#include "FileOutputManager.h"
#include "FileInputManager.h"
#include "DoubleLinkedList.h"
#include "Student.h"
#include "DoubleLinkedList.h"

class FacultyTable: public BinarySearchTree<int, Faculty>, public FileInputManager<FacultyTable> {

private:
  FileOutputManager fileOutputer;
  Faculty* facultyToAddToTable;

  //for filling this table up from a text file:
  int currentLineNumber;
  int numberOfFirstLineForDataSet;
  int numberOfLineWhereNumberOfAdviseesWasAt;
  int numberOfAdvisees;


public:

  DoubleLinkedList<int> listOfIDSThatExistInTree;

  FacultyTable();
  FacultyTable(int rootKey, Faculty rootValue);
  ~FacultyTable();

  void setUpTable(FacultyTable& objectToBuildUsingTheTextFile);

  int getCurrentLineNumber();
  int getNumberOfFirstLineForDataSet();
  int getNumberOfLineWhereNumberOfAdviseesWasAt();
  int getNumberOfAdvisees();

  void deleteListOfAdviseesForEachFaculty(TreeNode<int, Faculty>* node);

  void readFromFileWithSpecificRules(std::string line);

  void setCurrentLineNumber(int currentLineNumber);
  void setNumberOfFirstLineForDataSet(int numberOfFirstLineForDataSet);
  void setNunberOfLineWhereNumberOfAdviseesWasAt(int numberOfLineWhereNumberOfAdviseesWasAt);
  void setNumberOfAdvisees(int numberOfAdvisees);

  void printFaculty(TreeNode<int, Faculty>* node, BinarySearchTree<int, Student>& tree);
  void printASpecificFacultyMember(BinarySearchTree<int, Student>& tree);
  void printAdviseeInfoForSpecificFacultyMember(BinarySearchTree<int, Student>& tree);

  void initializeReferentialIntegrityOfTable(TreeNode<int, Faculty>* node, BinarySearchTree<int, Student>& treeToBaseReferenceOffOf);

  void AddAFacultyMember(BinarySearchTree<int, Student>& studentTreeReference);

};

#endif