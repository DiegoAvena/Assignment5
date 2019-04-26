#ifndef UNDO_MANAGER_H
#define UNDO_MANAGER_H

#include "ListBasedStack.h"
#include "DoubleLinkedList.h"
#include <iostream>

template <typename dataTypeOfItemsToSave>

class UndoManager {

private:
  ListBasedStack<dataTypeOfItemsToSave*> stackToSaveItems;
  int amountOfItemsThatCanBePushedOntoStack;
  DoubleLinkedList<dataTypeOfItemsToSave*> itemsToDeleteLater;

public:
  UndoManager() {

    amountOfItemsThatCanBePushedOntoStack = 1;

  }

  UndoManager(int amountOfItemsThatCanBePushedOntoStack) {

    this->amountOfItemsThatCanBePushedOntoStack = amountOfItemsThatCanBePushedOntoStack;

  }

  ~UndoManager() {

    for (int i = 0; i < itemsToDeleteLater.getSize(); i++) {

      delete itemsToDeleteLater.findAt(i);

    }

  }

  void saveSnapShot(dataTypeOfItemsToSave* itemToSave) {

    dataTypeOfItemsToSave* item = new dataTypeOfItemsToSave(itemToSave);
    std::cout<<"SAVING A SNAPSHOT..."<<std::endl;
    if (stackToSaveItems.getSize() >= amountOfItemsThatCanBePushedOntoStack) {

      //need to remove the oldest snapshot at the bottom of the stack to make room for this new snapshot
      ListBasedStack<dataTypeOfItemsToSave*> reverseOfOriginalStack;
      while (stackToSaveItems.isEmpty() == false) {

        //cout<<"ITEM BEING PUSHED ONTO STACK IS: "<<stackToSaveItems.top()->getPreviousFacultyTable()->getRoot()->getValue()<<endl;
        reverseOfOriginalStack.push(stackToSaveItems.top());
        std::cout<<"Size of reversed stack is: "<<reverseOfOriginalStack.getSize()<<std::endl;
        stackToSaveItems.pop();

      }

      std::cout<<"STACK REVERSED..."<<std::endl;
      //delete reverseOfOriginalStack.top();
      std::cout<<"REVERSE OF STACK IS EMPTY: "<<reverseOfOriginalStack.isEmpty()<<std::endl;
      reverseOfOriginalStack.pop();
      std::cout<<"OLDEST COMMAND REMOVED..."<<std::endl;

      while (reverseOfOriginalStack.isEmpty() == false) {

        stackToSaveItems.push(reverseOfOriginalStack.top());
        reverseOfOriginalStack.pop();

      }

      //now that room has been made, push the recent item to save onto the stack:
      stackToSaveItems.push(item);

    }
    else {

      //the stack size is currently less than the amount of items permitted to be saved, safe to push:
      stackToSaveItems.push(item);

    }

    itemsToDeleteLater.addFront(item);

  }

  bool CheckIfUserCanRollback() {

    if (stackToSaveItems.isEmpty()) {

      std::cout<<"Cannot undo any more changes"<<std::endl;
      return false;

    }
    else {

      return true;

    }

  }

  dataTypeOfItemsToSave* rollback() {

    dataTypeOfItemsToSave* itemToSetBackTo = stackToSaveItems.top();
    stackToSaveItems.pop();
    return itemToSetBackTo;

  }

};

#endif
