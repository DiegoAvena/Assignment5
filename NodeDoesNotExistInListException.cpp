#include "NodeDoesNotExistInListException.h"

NodeDoesNotExistInListException::NodeDoesNotExistInListException():RunTimeException(){}

NodeDoesNotExistInListException::NodeDoesNotExistInListException(std::string message):RunTimeException(message){}

NodeDoesNotExistInListException::~NodeDoesNotExistInListException(){
  
}
