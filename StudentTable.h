#ifndef STUDENT_TABLE_H
#define STUDENT_TABLE_H

#include "BinarySearchTree.h"
#include "Student.h"
#include "FileOutputManager.h"
#include "FileInputManager.h"
#include "Faculty.h"
#include <stdlib.h> // for access to the rand method
#include <cstdlib> //for access to RAND_MAX constant
#include "DoubleLinkedList.h"
#include "FacultyTable.h"
#include <iostream>

class StudentTable: public BinarySearchTree<int, Student>, public FileInputManager<StudentTable> {

private:
  FileOutputManager fileOutputer;
  int currentLineNumber;
  int numberOfFirstLineForDataSet;
  Student studentToAddToTable;

public:

  //DoubleLinkedList<int> facultyIDs;

  StudentTable();
  StudentTable(int rootKey, Student rootValue);
  ~StudentTable();

  void setUpTable(StudentTable& studentTableToBuild);
  void printStudents(TreeNode<int, Student>* node, BinarySearchTree<int, Faculty>& tree);

  void printASpecificStudent(BinarySearchTree<int, Faculty>& tree);
  void printFacultyInformationForASpecificStudent(BinarySearchTree<int, Faculty>& tree);

  void initializeReferentialIntegrityOfTable(TreeNode<int, Student>* node, FacultyTable& treeToBaseReferenceOffOf);

  void readFromFileWithSpecificRules(std::string line);

  void addAStudent(FacultyTable&  facultyTree);

};

#endif
