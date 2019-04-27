#include <iostream>

template <typename dataType>

/*

-Contains all of the components that make up a node
in a singly linked list

*/
class SinglyLinkedListNode {

public:

  //Default constructor
  SinglyLinkedListNode() {

  }

  //destructor
  ~SinglyLinkedListNode() {

  }

  dataType element; //the value this node stores
  SinglyLinkedListNode* next; //a pointer to the next node 

};
