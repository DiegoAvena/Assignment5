#include "RunTimeException.h"
#include <iostream>

//an exception thrown when a stack datastructure is found to be empty but the program is treating it as if it is not.
class StackEmptyException: public RunTimeException {

public:
  StackEmptyException(); //default constructor

  StackEmptyException(std::string customMessage); //overloaded constructor, allows for the setting of a custom error message

  ~StackEmptyException(); //destructor

};
