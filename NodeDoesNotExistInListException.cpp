#include "NodeDoesNotExistInListException.h"

 //default constructor
NodeDoesNotExistInListException::NodeDoesNotExistInListException():RunTimeException(){}

//overloaded constructor, allows for the setting of a custom message
NodeDoesNotExistInListException::NodeDoesNotExistInListException(std::string message):RunTimeException(message){}

//destuctor
NodeDoesNotExistInListException::~NodeDoesNotExistInListException(){

}
