#ifndef FACULTY_TABLE_H
#define FACULTY_TABLE_H

#include "BinarySearchTree.h"
#include "Faculty.h"
#include "FileOutputManager.h"
#include "FileInputManager.h"
#include "DoubleLinkedList.h"

class FacultyTable: public BinarySearchTree<int, Faculty>, public FileInputManager<FacultyTable> {

private:
  FileOutputManager fileOutputer;
  Faculty* facultyToAddToTable;
  //DoubleLinkedList<Faculty*>* listOfFacultyToDelete;

  //for filling this table up from a text file:
  int currentLineNumber;
  int numberOfFirstLineForDataSet;
  int numberOfLineWhereNumberOfAdviseesWasAt;
  int numberOfAdvisees;


public:

  FacultyTable();
  FacultyTable(int rootKey, Faculty rootValue);
  ~FacultyTable();

  void setUpTable(FacultyTable& objectToBuildUsingTheTextFile);
  //void inOrderPrint(TreeNode<int, Faculty>* node);

  int getCurrentLineNumber();
  int getNumberOfFirstLineForDataSet();
  int getNumberOfLineWhereNumberOfAdviseesWasAt();
  int getNumberOfAdvisees();

  //Faculty getFacultyToAddToTable();
  void deleteListOfAdviseesForEachFaculty(TreeNode<int, Faculty>* node);

  void readFromFileWithSpecificRules(std::string line);

  void setCurrentLineNumber(int currentLineNumber);
  void setNumberOfFirstLineForDataSet(int numberOfFirstLineForDataSet);
  void setNunberOfLineWhereNumberOfAdviseesWasAt(int numberOfLineWhereNumberOfAdviseesWasAt);
  void setNumberOfAdvisees(int numberOfAdvisees);

  void printFaculty(TreeNode<int, Faculty>* node);

};

#endif
