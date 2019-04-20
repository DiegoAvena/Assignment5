#include "DoubleLinkedListEmptyException.h"

using namespace std;

//default constructor
DoubleLinkedListEmptyException::DoubleLinkedListEmptyException():RunTimeException(){}

//overloaded constructor, allows for a more detailed message to be set up for this exception by invoking the overloaded constructor of RunTimeException
DoubleLinkedListEmptyException::DoubleLinkedListEmptyException(string customMessage):RunTimeException(customMessage){}

//destructor
DoubleLinkedListEmptyException::~DoubleLinkedListEmptyException() {

}
