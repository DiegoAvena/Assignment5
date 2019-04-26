#ifndef STUDENT_TABLE_H
#define STUDENT_TABLE_H

#include "BinarySearchTree.h"
#include "Student.h"
#include <fstream>
#include "FileInputManager.h"
#include "Faculty.h"
#include <stdlib.h> // for access to the rand method
#include <cstdlib> //for access to RAND_MAX constant
#include "DoubleLinkedList.h"
#include "FacultyTable.h"
#include <iostream>

class StudentTable: public BinarySearchTree<int, Student>, public FileInputManager<StudentTable>, public FileOutputManager<StudentTable> {

private:
  //FileOutputManager fileOutputer;
  int currentLineNumber;
  int numberOfFirstLineForDataSet;
  Student studentToAddToTable;
  void traverseTreeToCopyIt(TreeNode<int, Student>* node);
  bool commandModifiedTableSuccessfully;

public:

  //DoubleLinkedList<int> facultyIDs;
  bool getCommandModifiedTableSuccessfully();
  void setCommandModifiedTableSuccessfully(bool commandModifiedTableSuccessfully);

  StudentTable();
  StudentTable(int rootKey, Student rootValue);
  StudentTable(StudentTable& tableToCopy);

  ~StudentTable();

  void setUpTable(StudentTable& studentTableToBuild);
  void printStudents(TreeNode<int, Student>* node, BinarySearchTree<int, Faculty>& tree);

  void printASpecificStudent(BinarySearchTree<int, Faculty>& tree);
  void printFacultyInformationForASpecificStudent(BinarySearchTree<int, Faculty>& tree);

  void initializeReferentialIntegrityOfTable(TreeNode<int, Student>* node, FacultyTable& treeToBaseReferenceOffOf);

  void readFromFileWithSpecificRules(std::string line);

  void addAStudent(FacultyTable&  facultyTree);
  void removeAStudent(FacultyTable& facultyTree);
  void changeStudentsAdvisor(FacultyTable& facultyTree);
  void writeToFileUsingSpecficRules(std::ofstream* fileToWriteTo, TreeNode<int, Student>* node);

};

#endif
