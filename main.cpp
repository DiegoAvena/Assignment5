#include <time.h>
#include "DataBaseManager.h"
#include <iostream>
#include "DoubleLinkedList.h"

using namespace std;

int main(int argc, char const *argv[]) {

  srand(time(NULL)); //seeds the random number generator to insure that each time the program is executed, different values are produced: http://www.math.uaa.alaska.edu/~afkjm/csce211/fall2018/handouts/RandomFunctions.pdf

  DataBaseManager dataBaseManager;
  dataBaseManager.presentMenuToUser(); //this launches the program/database

  /*DoubleLinkedList<int>* list = new DoubleLinkedList<int>();
  list->addFront(1);
  list->addFront(2);
  list->printList(); //should be 2, 1

  DoubleLinkedList<int>* copyOfOldList = new DoubleLinkedList<int>();

  for (int i = 0; i < list->getSize(); i++) {

    copyOfOldList->addBack(list->findAt(i));

  }

  delete list;
  copyOfOldList->printList(); //should be 2, 1
  delete copyOfOldList;*/

  return 0;
}
