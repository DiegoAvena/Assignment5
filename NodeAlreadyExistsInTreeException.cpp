#include "NodeAlreadyExistsInTreeException.h"
using namespace std;

//constructor
NodeAlreadyExistsInTreeException::NodeAlreadyExistsInTreeException():RunTimeException() {}

//overloaded constructor, allows for the setting of a custom error message
NodeAlreadyExistsInTreeException::NodeAlreadyExistsInTreeException(string customErrorMessage):RunTimeException(customErrorMessage){}

//destructor
NodeAlreadyExistsInTreeException::~NodeAlreadyExistsInTreeException(){

}
