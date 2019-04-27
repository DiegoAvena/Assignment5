#include "SinglyLinkedListEmptyException.h"

using namespace std;

//default constructor
SinglyLinkedListEmptyException::SinglyLinkedListEmptyException():RunTimeException(){}

//overloaded constructor, allows for the setting of a custom error message
SinglyLinkedListEmptyException::SinglyLinkedListEmptyException(string customMessage):RunTimeException(customMessage){}

//destructor
SinglyLinkedListEmptyException::~SinglyLinkedListEmptyException() {


}
