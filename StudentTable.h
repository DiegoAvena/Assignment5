#ifndef STUDENT_TABLE_H
#define STUDENT_TABLE_H

#include "BinarySearchTree.h"
#include "Student.h"
#include "FileOutputManager.h"

class StudentTable: public BinarySearchTree<int, Student> {

private:
  FileOutputManager fileOutputer;

public:
  StudentTable();
  StudentTable(int rootKey, Student rootValue);
  ~StudentTable();

};

#endif
