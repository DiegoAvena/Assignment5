#include "SinglyLinkedListEmptyException.h"

using namespace std;

SinglyLinkedListEmptyException::SinglyLinkedListEmptyException():RunTimeException(){}

SinglyLinkedListEmptyException::SinglyLinkedListEmptyException(string customMessage):RunTimeException(customMessage){}

SinglyLinkedListEmptyException::~SinglyLinkedListEmptyException() {


}
