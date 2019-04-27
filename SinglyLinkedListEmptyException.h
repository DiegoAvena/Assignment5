#include "RunTimeException.h"
#include <iostream>

//an exception thrown if a SinglyLinkedList datastructure is empty but the program is treating it as if it is not empty
class SinglyLinkedListEmptyException: public RunTimeException {

public:
  SinglyLinkedListEmptyException(); //default constructor

  SinglyLinkedListEmptyException(std::string customMessage); //overloaded constructor, allows for the setting of a custom error message

  ~SinglyLinkedListEmptyException(); //destructor

};
