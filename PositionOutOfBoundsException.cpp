#include "PositionOutOfBoundsException.h"

using namespace std;

//default constructor
PositionOutOfBoundsException::PositionOutOfBoundsException():RunTimeException(){}

//overloaded constructor, allows for a more detailed message to be set up for this exception
PositionOutOfBoundsException::PositionOutOfBoundsException(string message):RunTimeException(message){}

//destructor
PositionOutOfBoundsException::~PositionOutOfBoundsException(){

}
