#include<iostream>
#include "SinglyLinkedListNode.h"
#include "SinglyLinkedListEmptyException.h"
#include <iostream>

template <typename dataType>

class SinglyLinkedList {

public:

  SinglyLinkedList() {

    head = NULL;

  }

  ~SinglyLinkedList() {

    while (isEmpty() == false) {

      std::cout<<"Deleting list nodes"<<std::endl;
      RemoveFront();

    }

  }

  void AddFront(dataType newElement) {

    SinglyLinkedListNode<dataType>* newNode = new SinglyLinkedListNode<dataType>;

    /*
    NOTE:

    the first element we add here will
    always have a next value of NULL because the head is set to NULL by default,
    so the first element will get a next of NULL when we do newNode->next = head. This
    means that when we remove and get to the final element, the head will be set to NULL since head->next will be null for this
    final element. So we can check if the list is empty by doing head == NULL.

    */
    newNode->next = head;
    newNode->element = newElement;
    head = newNode;

  }

  dataType front() throw(SinglyLinkedListEmptyException) {

    if (isEmpty()) {

      //throw an empty exception
      throw SinglyLinkedListEmptyException("List empty exception");

    }
    return head->element;


  }

  void RemoveFront() throw(SinglyLinkedListEmptyException){

    if (isEmpty()) {

      //throw an exception!
      throw SinglyLinkedListEmptyException("List empty exception");

    }

    SinglyLinkedListNode<dataType>* oldHead = head;
    head = head->next;
    delete oldHead;

  }

  bool isEmpty() {

    return (head == NULL);

  }

private:
  SinglyLinkedListNode<dataType>* head;

};
