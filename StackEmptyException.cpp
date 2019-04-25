#include "StackEmptyException.h"
using namespace std;

StackEmptyException::StackEmptyException(): RunTimeException() {}

StackEmptyException::StackEmptyException(string customMessage): RunTimeException(customMessage){}

StackEmptyException::~StackEmptyException() {

}
