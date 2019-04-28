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
#include <stdlib.h> // for access to the rand method
#include <iostream>
//#include "SnapShotContainer.h"
#include "UndoManager.h"

class FacultyTable: public BinarySearchTree<int, Faculty>, public FileInputManager<FacultyTable>, public FileOutputManager<FacultyTable> {

private:

  Faculty* facultyToAddToTable;
  DoubleLinkedList< DoubleLinkedList<unsigned int>* >* listOfAdviseeListsToDeleteLater;
  
  //for filling this table up from a text file:
  int currentLineNumber;
  int numberOfFirstLineForDataSet;
  int numberOfAdvisees;

  bool commandModifiedTableSuccessfully;

  void traverseTreeToCopyIt(TreeNode<int, Faculty>* node);

public:
  DoubleLinkedList<int>* listOfIDSThatExistInTree;

  FacultyTable();
  FacultyTable(int rootKey, Faculty rootValue);
  FacultyTable(const FacultyTable& tableToCopy);
  ~FacultyTable();

  bool getCommandModifiedTableSuccessfully();
  void setCommandModifiedTableSuccessfully(bool commandModifiedTableSuccessfully);

  void setUpTable(FacultyTable& objectToBuildUsingTheTextFile);

  void deleteListOfAdviseesForEachFaculty(TreeNode<int, Faculty>* node);

  void readFromFileWithSpecificRules(std::string line);

  void printFaculty(TreeNode<int, Faculty>* node, BinarySearchTree<int, Student>& tree);
  void printASpecificFacultyMember(BinarySearchTree<int, Student>& tree);
  void printAdviseeInfoForSpecificFacultyMember(BinarySearchTree<int, Student>& tree);

  void initializeReferentialIntegrityOfTable(TreeNode<int, Faculty>* node, BinarySearchTree<int, Student>& treeToBaseReferenceOffOf);

  void AddAFacultyMember(BinarySearchTree<int, Student>& studentTreeReference);
  void removeAFacultyMember(BinarySearchTree<int, Student>& studentTreeReference);
  void removeAnAdvisee(BinarySearchTree<int, Student>& studentTreeReference);

  void writeToFileUsingSpecficRules(std::ofstream* fileToWriteTo, TreeNode<int, Faculty>* node);

};

#endif
