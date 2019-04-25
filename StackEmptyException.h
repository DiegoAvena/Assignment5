#include "RunTimeException.h"
#include <iostream>

class StackEmptyException: public RunTimeException {

public:
  StackEmptyException();
  StackEmptyException(std::string customMessage);
  ~StackEmptyException();

};
