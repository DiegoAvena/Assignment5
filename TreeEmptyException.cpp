#include "TreeEmptyException.h"
using namespace std;

//Default constructor
TreeEmptyException::TreeEmptyException():RunTimeException(){}

//overloaded constructor, allows for a custom message to be set
TreeEmptyException::TreeEmptyException(string customErrorMessage):RunTimeException(customErrorMessage) {}

//destructor
TreeEmptyException::~TreeEmptyException() {

}
