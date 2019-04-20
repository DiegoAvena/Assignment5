#ifndef NODE_DOES_NOT_EXIST_IN_LIST_EXCEPTION_H
#define NODE_DOES_NOT_EXIST_IN_LIST_EXCEPTION_H

#include "RunTimeException.h"

class NodeDoesNotExistInListException:public RunTimeException {

public:
  NodeDoesNotExistInListException();
  NodeDoesNotExistInListException(std::string message);
  ~NodeDoesNotExistInListException();

};

#endif
