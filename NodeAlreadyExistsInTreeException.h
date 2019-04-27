#ifndef NODE_ALREADY_EXISTS_IN_TREE_EXCEPTION_H
#define NODE_ALREADY_EXISTS_IN_TREE_EXCEPTION_H

#include "RunTimeException.h"
#include <iostream>

/*

-An exception thrown if the program attempts to insert a node into a BST data
structure that already exists.

*/
class NodeAlreadyExistsInTreeException:public RunTimeException {

public:
  NodeAlreadyExistsInTreeException(); //constructor

  NodeAlreadyExistsInTreeException(std::string customErrorMessage); //overloaded constructor, allows for the setting of a custom error message

  ~NodeAlreadyExistsInTreeException(); //destructor

};

#endif
