#ifndef STUDENT_TABLE_H
#define STUDENT_TABLE_H

#include "BinarySearchTree.h"
#include "Student.h"
#include "FileOutputManager.h"
#include "FileInputManager.h"
#include "Faculty.h"

class StudentTable: public BinarySearchTree<int, Student>, public FileInputManager<StudentTable> {

private:
  FileOutputManager fileOutputer;
  int currentLineNumber;
  int numberOfFirstLineForDataSet;
  Student studentToAddToTable;

public:
  StudentTable();
  StudentTable(int rootKey, Student rootValue);
  ~StudentTable();

  void setUpTable(StudentTable& studentTableToBuild);
  void printStudents(TreeNode<int, Student>* node, BinarySearchTree<int, Faculty>& tree);

  void printASpecificStudent(BinarySearchTree<int, Faculty>& tree);
  void printFacultyInformationForASpecificStudent(BinarySearchTree<int, Faculty>& tree);

  void readFromFileWithSpecificRules(std::string line);

};

#endif
