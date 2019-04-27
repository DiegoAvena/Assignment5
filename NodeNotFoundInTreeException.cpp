#include "NodeNotFoundInTreeException.h"
using namespace std;

//default constructor
NodeNotFoundInTreeException::NodeNotFoundInTreeException():RunTimeException() {}

//overloaded constructor, allows for the setting of a custom message
NodeNotFoundInTreeException::NodeNotFoundInTreeException(string customErrorMessage):RunTimeException(customErrorMessage){}

//destructor
NodeNotFoundInTreeException::~NodeNotFoundInTreeException() {

}
