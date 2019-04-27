#ifndef TREE_EMPTY_EXCEPTION_H
#define TREE_EMPTY_EXCEPTION_H

#include "RunTimeException.h"
#include <iostream>

//An exception thrown if the binary search tree is empty and the program is treating it as if there are nodes in it
class TreeEmptyException: public RunTimeException {

public:
  TreeEmptyException(); //Default constructor
  TreeEmptyException(std::string customErrorMessage); //overloaded constructor, allows for a custom message to be set
  ~TreeEmptyException(); //destructor

};

#endif
