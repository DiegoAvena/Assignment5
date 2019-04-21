#include "StudentTable.h"

StudentTable::StudentTable():BinarySearchTree(){}

StudentTable::StudentTable(int rootKey, Student rootValue):BinarySearchTree(rootKey, rootValue){}

StudentTable::~StudentTable() {

  //output the contents of each node in this table to the text file, and than allow the base constructor to delete the tree:
  

}
