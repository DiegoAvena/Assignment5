#include "SinglyLinkedList.h"
#include "StackEmptyException.h"
#include <iostream>

template <typename dataType>

/*

-A LIFO data structure that uses a singly linked list, meaning it
can dynamically resize itself.

*/
class ListBasedStack {

private:
  SinglyLinkedList<dataType> list; //the list that will store the information pushed onto the stack
  unsigned int stackSize; //the size of the stack, or how many elements are in the stack

public:

  //default constructor, initializes stackSize to 0
  ListBasedStack() {

    stackSize = 0;

  }

  //destructor
  ~ListBasedStack() {

  }

  //checks if the stack is empty
  bool isEmpty() {

    return (list.isEmpty());

  }

  //returns a copy of the element at the top of the stack
  dataType top() throw(StackEmptyException){

    if (isEmpty()) {

      throw StackEmptyException("Stack is empty");

    }

    return list.front();

  }

  //puts a new element at the top of the stack
  void push(dataType item) {

    list.AddFront(item);
    stackSize++;

  }

  //removes the element at the top of the stack
  void pop() throw(StackEmptyException){

    if (isEmpty()) {

      throw StackEmptyException("Stack is empty");

    }

    list.RemoveFront();
    stackSize--;

  }

  //returns the size of the stack
  unsigned int getSize() {

    return stackSize;

  }

};
