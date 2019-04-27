#ifndef NODE_DOES_NOT_EXIST_IN_LIST_EXCEPTION_H
#define NODE_DOES_NOT_EXIST_IN_LIST_EXCEPTION_H

#include "RunTimeException.h"

/*

-An exception thrown if a node is not found
in a list but the program is treating it as if the node does exist
in the list.

*/
class NodeDoesNotExistInListException:public RunTimeException {

public:
  NodeDoesNotExistInListException(); //default constructor

  NodeDoesNotExistInListException(std::string message); //overloaded constructor, allows for the setting of a custom message

  ~NodeDoesNotExistInListException(); //destuctor

};

#endif
