#include "SinglyLinkedList.h"
#include "StackEmptyException.h"
#include <iostream>

template <typename dataType>

class ListBasedStack {

private:
  SinglyLinkedList<dataType> list;
  unsigned int stackSize;

public:
  ListBasedStack(): list(), stackSize(0){

  }

  ~ListBasedStack() {

    std::cout<<"DELETING STACK"<<std::endl;

  }

  bool isEmpty() {

    return (list.isEmpty());

  }

  dataType top() throw(StackEmptyException){

    if (isEmpty()) {

      throw StackEmptyException("Stack is empty");

    }

    return list.front();

  }

  void push(dataType item) {

    list.AddFront(item);
    stackSize++;

  }

  void pop() throw(StackEmptyException){

    if (isEmpty()) {

      throw StackEmptyException("Stack is empty");

    }

    list.RemoveFront();
    stackSize--;

  }

  unsigned int getSize() {

    return stackSize;

  }

};
