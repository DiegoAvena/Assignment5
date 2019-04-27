#include "StackEmptyException.h"
using namespace std;

//default constructor
StackEmptyException::StackEmptyException(): RunTimeException() {}

//overloaded constructor, allows for the setting of a custom error message
StackEmptyException::StackEmptyException(string customMessage): RunTimeException(customMessage){}

//destructor
StackEmptyException::~StackEmptyException() {

}
