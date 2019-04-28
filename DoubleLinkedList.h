#ifndef DOUBLE_LINKED_LIST_H //Guards used since this datastructure can be used multiple times in 1 class
#define DOUBLE_LINKED_LIST_H

#include <iostream>
#include "PositionOutOfBoundsException.h"
#include "DoubleLinkedListEmptyException.h"
#include "DoubleLinkedListNode.h"
#include "NodeDoesNotExistInListException.h"

template <typename dataType> //the list can store any dataType

/*

-A Data structure that is a list of data that can dynamically scale itself and contains nodes which are linked in both forward in backward directions,
and 2 different pointers to keep track of the front and back sides of the list

*/
class DoubleLinkedList {

private:
  DoubleLinkedListNode<dataType>* front; //pointer to the front node of the list
  DoubleLinkedListNode<dataType>* back; //pointer to the back node of the list
  int listSize; //keeps track of the size of the list

public:

  //default constructor:
  DoubleLinkedList() {

    front = NULL;
    back = NULL;
    listSize = 0;

  }

  //destructor
  ~DoubleLinkedList() {

    while (empty() == false) {

      removeFront();

    }

  }

  //finds the node that contains the element given, and returns its position in the list if it was found:
  int find(dataType data) {

    int currentPosition = 0;
    DoubleLinkedListNode<dataType>* currentNode = front;

    while (currentNode != NULL) {

      if (currentNode->element == data) {

        break;

      }

      currentNode = currentNode->next;
      currentPosition++;

    }

    if (currentNode == NULL) {

      //the element was not found:
      return -1;

    }

    //element must have been found, return its position
    return currentPosition;


  }

  //finds the element stored at the provided index/position in the list:
  dataType findAt(int index) const throw(PositionOutOfBoundsException, DoubleLinkedListEmptyException) {

    if ((index < 0) || (index > listSize)) {

      //the given index is invalid:
      throw PositionOutOfBoundsException("Index is out of bounds");

    }
    else if (empty()) {

      //there is nothing to search for:
      throw DoubleLinkedListEmptyException("List is empty");

    }
    else {

      int position = 0; //start at the front of the list, which is position 0
      DoubleLinkedListNode<dataType>* currentNode = front;

      while (position != index) {

        position++;
        currentNode = currentNode->next;

      }

      return currentNode->element;

    }

  }

  //adds a new node to the front of the list with the given element:
  void addFront(dataType data) {

    DoubleLinkedListNode<dataType>* newNode = new DoubleLinkedListNode<dataType>();
    newNode->element = data;

    if (back == NULL) {

      //this is the first element being placed, so both front and back need to point to it:
      back = newNode;

    }
    else {

      //the new node will be the new front, so the current front is now the successor of this new node:
      newNode->next = front;
      front->previous = newNode; //link the old front in the backward direction to the new front

    }

    front = newNode; //make the new node the new front of the list
    listSize++;

  }

  //removes the node at the front of the list
  void removeFront() throw(DoubleLinkedListEmptyException){

    if (empty()) {

      //there is nothing to remove:
      throw DoubleLinkedListEmptyException("List is empty.");

    }

    DoubleLinkedListNode<dataType>* oldFront = front;

    if (listSize == 1) {

      back = NULL; //make sure to null out back because if size is 1, then back also points to the node we want to delete, which can give a seg fault error

    }
    else {

      //make sure the pointer to previous for the successor of the front about to be deleted is NULLED out to prevent seg faults
      oldFront->next->previous = NULL;

    }

    //update front to point to its successor:
    front = front->next;

    //remove the old front of the list
    delete oldFront;

    listSize--;

  }

  //adds a new back node with the given element to the list
  void addBack(dataType data) {

    DoubleLinkedListNode<dataType>* newNode = new DoubleLinkedListNode<dataType>();
    newNode->element = data;

    if (front == NULL) {

      //this is the first element being put into the list, so front should also point to it:
      front = newNode;

    }
    else {

      //since the new node is the new back, then the previous node will be the old back:
      newNode->previous = back;

      //successor of the old back is now the new back:
      back->next = newNode;

    }

    back = newNode; //move back to point to the new back:
    listSize++;

  }

  //removes the back node of the list:
  void removeBack() throw(DoubleLinkedListEmptyException){

    if (empty()) {

      //nothing to remove:
      throw DoubleLinkedListEmptyException("List is empty.");

    }

    DoubleLinkedListNode<dataType>* oldBack = back; //needed so the the old back node of the list can be deleted later

    if (listSize == 1) {

      //if there was only 1 element, then the front of the list is pointing to the back node as well and it needs to be NULLed out to prevent seg faults
      front = NULL;

    }
    else {

      //The back is the successor of its previous node, but since back is about to be deleted, then the predecessor's pointer to a successor needs to be nulled out:
      back->previous->next = NULL;

    }

    back = back->previous; //move back to point to its predecessor
    delete oldBack; //delete the old back
    listSize--;

  }

  //adds element in at any position and pushes everything else to the right
  void addAt(int position, dataType data) throw(PositionOutOfBoundsException){

    if (position < 0 || position > (listSize - 1)) {

      //position is out of bounds:
      throw PositionOutOfBoundsException("Index is out of bounds");

    }
    else if (position == 0) {

      //adding in a new front, use the addfront method:
      addFront(data);

    }
    else if (position == (listSize - 1)) {

      //adding in a new back, use the add back method instead
      addBack(data);

    }
    else {

      DoubleLinkedListNode<dataType>* currentNode = front;
      int currentPosition = 0;

      //begin by iterating to the node at the position where we want to add this new node at:
      while (currentPosition != position) {

        currentPosition++;
        currentNode = currentNode->next;

      }

      //By this point, current node stores the node currently at the position where we want to add the new node at:

      DoubleLinkedListNode<dataType>* newNode = new DoubleLinkedListNode<dataType>();

      newNode->element = data;

      //the new node is inserted at the position of the node currently here, so the node currently here, along with everything else, needs to be pushed 1 spot to the right:
      newNode->next = currentNode;
      newNode->previous = currentNode->previous;
      currentNode->previous->next = newNode;
      currentNode->previous = newNode;

      listSize++;

    }

  }

  void remove(dataType dataToRemoveFromList) throw (NodeDoesNotExistInListException, DoubleLinkedListEmptyException){

    if (empty()) {

      throw DoubleLinkedListEmptyException("List is empty.");

    }
    else if (dataToRemoveFromList == front->element) {

      //the node to be removed is the front node of this list, use remove front instead so that the head pointer is updated correctly
      removeFront();

    }
    else if (dataToRemoveFromList == back->element) {

      //the node to be removed is the back of this list, use the remove back method instead so that the back pointer is updated correctly
      removeBack();

    }
    else {

      DoubleLinkedListNode<dataType>* currentNode = front;

      while (currentNode != NULL) {

        if (currentNode->element == dataToRemoveFromList) {

          break;

        }
        else {

          currentNode = currentNode->next;

        }

      }

      if (currentNode != NULL) {

        currentNode->previous->next = currentNode->next;
        currentNode->next->previous = currentNode->previous;

        delete currentNode;
        listSize--;

      }
      else {

        throw NodeDoesNotExistInListException("Cannot delete a node that does not exist in the list.");

      }

    }

  }

  //removes a node at any position and scoots everything back:
  void removeAt(int position) throw (PositionOutOfBoundsException, DoubleLinkedListEmptyException){

    if (position < 0 || position > (listSize - 1)) {

      //position is out of bounds:
      throw PositionOutOfBoundsException("Index is out of bounds.");

    }
    else if (empty()) {

      //nothing to delete:
      throw DoubleLinkedListEmptyException("List is empty.");

    }
    else if (position == 0) {

      //use the removeFront method so that the front and back pointers are updated correctly:
      removeFront();

    }
    else if (position == (listSize - 1)) {

      //use the removeBack method so that the front and back pointers are updated correctly:
      removeBack();

    }
    else {

      int currentPosition = 0;
      DoubleLinkedListNode<dataType>* currentNode = front;

      //iterate over to the node we want to remove:
      while (currentPosition != position) {

        currentPosition++;
        currentNode = currentNode->next;

      }

      //by this point the current node is the node we want to delete it
      currentNode->next->previous = currentNode->previous;
      currentNode->previous->next = currentNode->next;
      delete currentNode;
      listSize--;

    }

    std::cout<<"Current List size after a deletion:"<<listSize<<std::endl;

  }

  //returns the element at the front of the list:
  dataType getFront() throw(DoubleLinkedListEmptyException){

    if (empty()) {

      //no element to return:
      throw DoubleLinkedListEmptyException("List is empty.");

    }

    return front->element;

  }

  //returns the element at the back of the list
  dataType getBack() throw(DoubleLinkedListEmptyException){

    if (empty()) {

      //no element to return
      throw DoubleLinkedListEmptyException("List is empty");

    }

    return back->element;

  }

  //returns the size of the list:
  const int getSize() const {

    return listSize;

  }

  //checks if the list is empty:
  bool empty() const {

    return (front == NULL);

  }

  //prints out all of the elements currently in the list:
  void printList() const throw(DoubleLinkedListEmptyException) {

    if (empty()) {

      throw DoubleLinkedListEmptyException("List is empty.");

    }
    else {

      DoubleLinkedListNode<dataType>* currentNode = front;
      while (currentNode != NULL) {

        std::cout<<currentNode->element<<std::endl;
        currentNode = currentNode->next;

      }

    }

  }

};

#endif
