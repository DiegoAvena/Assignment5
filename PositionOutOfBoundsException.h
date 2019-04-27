#include "RunTimeException.h"

/*

-An exception that can be thrown when a given position is invalid
with regards to a list, array, etc.

*/
class PositionOutOfBoundsException:public RunTimeException {

public:
  PositionOutOfBoundsException(); //default constructor

  PositionOutOfBoundsException(std::string message); //overloaded constructor, allows for a more detailed message to be set up for this exception

  ~PositionOutOfBoundsException(); //destructor

};
