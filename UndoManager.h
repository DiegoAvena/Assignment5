#ifndef UNDO_MANAGER_H
#define UNDO_MANAGER_H

#include "ListBasedStack.h"
#include "DoubleLinkedList.h"
#include <iostream>

template <typename dataTypeOfItemsToSave>

/*

-UndoManager allows the program to save changes made to the database by using a stack.
The class saves a specified number of snapshots or instances of the database. For this assignment, this is 5.

*/
class UndoManager {

private:
  ListBasedStack<dataTypeOfItemsToSave*> stackToSaveItems; //the stack that will save the snapshots of the database prior to a command changing it
  int amountOfItemsThatCanBePushedOntoStack; //the amount of items the stack should save up to before it pops older instances of the database to make room for the saving of new instances
  DoubleLinkedList<dataTypeOfItemsToSave*> itemsToDeleteLater; //used to delete allocated memory for the items to be pushed onto the stack from here

public:

  //Default constructor, makes it so that only 1 snapshot can be saved onto the stack, so that the user can only undo up to 1 command that changed the database
  UndoManager() {
    
    amountOfItemsThatCanBePushedOntoStack = 1;

  }

  //overloaded constructor: allows for the setting of a custom number of snapshots that can be saved before older changes start being popped off to make room for new changes
  UndoManager(int amountOfItemsThatCanBePushedOntoStack) {

    this->amountOfItemsThatCanBePushedOntoStack = amountOfItemsThatCanBePushedOntoStack;

  }

  //Destructor: free memory that was allocated to save the items being pushed onto the stack
  ~UndoManager() {

    for (int i = 0; i < itemsToDeleteLater.getSize(); i++) {

      delete itemsToDeleteLater.findAt(i);

    }

  }

  //pushes a snapshot onto the stack, making sure to do the appropriate shifts if the stack is already holding the max amount of snapshots that should be saved
  void saveSnapShot(dataTypeOfItemsToSave* itemToSave) {

    dataTypeOfItemsToSave* item = new dataTypeOfItemsToSave(itemToSave);

    if (stackToSaveItems.getSize() >= amountOfItemsThatCanBePushedOntoStack) {

      /*

      the stack saving the instances of the database is already holding the max amount of snapshots
      that the user can rollback to, so room needs to be made to save this new snapshot by removing the oldest instance in this
      stack. This is done by the following process due to the LIFO principle of stacks:

      */

      //1: Reverse the current stack:
      ListBasedStack<dataTypeOfItemsToSave*> reverseOfOriginalStack;
      while (stackToSaveItems.isEmpty() == false) {

        reverseOfOriginalStack.push(stackToSaveItems.top());
        stackToSaveItems.pop();

      }

      //2.) The item at the top of the reversed stack is the oldest snapshot of the database, remove it:
      reverseOfOriginalStack.pop();

      //3.) Put everything back into original stack:
      while (reverseOfOriginalStack.isEmpty() == false) {

        stackToSaveItems.push(reverseOfOriginalStack.top());
        reverseOfOriginalStack.pop();

      }

      //4.) now that room has been made, push the recent item to save onto the stack:
      stackToSaveItems.push(item);

    }
    else {

      //the stack size is currently less than the amount of items permitted to be saved, safe to push:
      stackToSaveItems.push(item);

    }

    itemsToDeleteLater.addFront(item); //Done so that when the program ends, the memory allocated for each item here is deallocated to prevent memory leaks

  }

  //Checks if the user can rollback to anything, and if they cannot, tells them why
  bool CheckIfUserCanRollback() {

    if (stackToSaveItems.isEmpty()) {

      std::cout<<"Cannot undo any more changes"<<std::endl;
      return false;

    }
    else {

      return true;

    }

  }

  /*

  -Actually performs the rollback by removing the most
  recent snapshot of the database from the stack and returning it. This
  method should only be called after CheckIfUserCanRollback has returned true, in order
  to prevent the throwing of a StackEmptyException.

  */
  dataTypeOfItemsToSave* rollback() {

    dataTypeOfItemsToSave* itemToSetBackTo = stackToSaveItems.top();
    stackToSaveItems.pop();
    return itemToSetBackTo;

  }

};

#endif
