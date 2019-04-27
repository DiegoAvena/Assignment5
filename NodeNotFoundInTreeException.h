#ifndef NODE_NOT_FOUND_IN_TREE_EXCEPTION_H
#define NODE_NOT_FOUND_IN_TREE_EXCEPTION_H

#include <iostream>
#include "RunTimeException.h"

/*

-An exception thrown if a node does not exist in a tree but the program is treating the tree as if it
contains this node.

*/
class NodeNotFoundInTreeException: public RunTimeException {

public:
  NodeNotFoundInTreeException(); //default constructor

  NodeNotFoundInTreeException(std::string customErrorMessage); //overloaded constructor, allows for the setting of a custom message

  ~NodeNotFoundInTreeException(); //destructor

};

#endif
