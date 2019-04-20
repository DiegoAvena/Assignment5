#include "RunTimeException.h"
#include <iostream>

/*

An exception that is thrown if a DoubleLinkedList is found to be empty

*/
class DoubleLinkedListEmptyException: public RunTimeException {

public:
  DoubleLinkedListEmptyException(); //default constructor
  DoubleLinkedListEmptyException(std::string customMessage); //overloaded constructor, allows for a more detailed message to be set up for this exception
  ~DoubleLinkedListEmptyException(); //destructor

};
