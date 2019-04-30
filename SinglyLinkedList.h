#include<iostream>
#include "SinglyLinkedListNode.h"
#include "SinglyLinkedListEmptyException.h"
#include <iostream>

template <typename dataType>

/*

-A datastructure that stores nodes connected to each other in only
the forward direction. Each node in turn stores a value.

*/
class SinglyLinkedList {

public:

  //Default constructor
  SinglyLinkedList() {

    head = NULL;

  }

  //destructor
  ~SinglyLinkedList() {

    while (isEmpty() == false) {

      RemoveFront();

    }

  }

  //adds a new head/node to the front of the list
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
    head = newNode; //move head to point to this new node at the front of the list

  }

  //returns a copy of the element stored at the front of the list
  dataType front() throw(SinglyLinkedListEmptyException) {

    if (isEmpty()) {

      //throw an empty exception
      throw SinglyLinkedListEmptyException("List empty exception");

    }
    return head->element;


  }

  //removes the head of the list
  void RemoveFront() throw(SinglyLinkedListEmptyException){

    if (isEmpty()) {

      //throw an exception:
      throw SinglyLinkedListEmptyException("List empty exception");

    }

    SinglyLinkedListNode<dataType>* oldHead = head;
    head = head->next;
    delete oldHead;

  }

  //checks if the list is empty
  bool isEmpty() {

    return (head == NULL);

  }

private:
  SinglyLinkedListNode<dataType>* head; //pointer to the front of the list

};
