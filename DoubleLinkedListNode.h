#ifndef DOUBLE_LINKED_LIST_NODE_H
#define DOUBLE_LINKED_LIST_NODE_H

template <typename dataType>

/*

A node that stores an element inside a double linked list data structure

*/
class DoubleLinkedListNode {

public:
  dataType element; //the item this node will store
  DoubleLinkedListNode<dataType>* next; //the successor of this node
  DoubleLinkedListNode<dataType>* previous; //the predecessor of this node

  //default constructor
  DoubleLinkedListNode() {

    next = NULL;
    previous = NULL;

  }

  //overloaded constructor, allows for an item to be placed into this node
  DoubleLinkedListNode(dataType e) {

    element = e;
    next = NULL;
    previous = NULL;

  }

  //destructor
  ~DoubleLinkedListNode() {

  }

};

#endif
