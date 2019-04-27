#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <iostream>

/*

-templated so that keys and values can be of any type,
though currently for keys it might be best to just use numerical values for it

*/
template <typename K, typename V>

/*

-Contains all of the components that make up a
node in a binary search tree

*/
class TreeNode {

private:
  K key; //the key of this node
  V value; //the value this node holds

public:
  TreeNode<K, V>* left; //Pointer to the left child of this node
  TreeNode<K, V>* right; //Pointer to the right child of this node

  //default constructor
  TreeNode() {

    left = NULL;
    right = NULL;

  }

  //overloaded constructor: sets both key and value of this node to key
  TreeNode(K key) {

    this->key = key;
    this->value = key;
    left = NULL;
    right = NULL;

  }

  //overloaded constructor: sets key and value to seperate values
  TreeNode(K key, V value) {

    this->key = key;
    this->value = value;
    left = NULL;
    right = NULL;

  }

  //destructor
  virtual ~TreeNode() {
  }

  //Mutator method, allows the key of this node to be set
  void setKey(K key) {

    this->key = key;

  }

  //Accessor method for getting the key of this node, made constant so that the reference returned is not modified
  const K& getKey() {

    return this->key;

  }

  //Mutator method, allows the value of this node to be set
  void setValue(V value) {

    this->value = value;

  }

  //Accessor method for getting the value stored in this node
  V& getValue() {

    return this->value;

  }

};

#endif
