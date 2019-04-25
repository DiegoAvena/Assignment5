#include "RunTimeException.h"
#include <iostream>

class SinglyLinkedListEmptyException: public RunTimeException {

public:
  SinglyLinkedListEmptyException();
  SinglyLinkedListEmptyException(std::string customMessage);
  ~SinglyLinkedListEmptyException();

};
