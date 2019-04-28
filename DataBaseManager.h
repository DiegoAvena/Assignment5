#ifndef DATA_BASE_MANAGER_H
#define DATA_BASE_MANAGER_H

#include "StudentTable.h"
#include "FacultyTable.h"
#include "TreeNode.h"
#include <iostream>
#include "UndoManager.h"
#include "SnapShotContainer.h"

/*

-Allows the user to interact with a database consisting
of student and faculty BSTs.

*/
class DataBaseManager {

private:
  StudentTable* masterStudent; //The student table/tree
  FacultyTable* masterFaculty; //the faculty table/tree
  UndoManager<SnapShotContainer>* undoer; //allows for rollback to occur by saving snapshots and releasing snapshots of the database

  SnapShotContainer* snapShotContainer; //used to take snapshots or temporarily store instances of the database before a command is issued so that they can be saved for potentiall rollback by undoer in the event a command changes the database

  bool determineWhichCommandToCarryOut(int response); //determines which command to carry out based on the number the user inputed

  void checkIfCommandChangedStructureOfDatabase(); //checks if the command given just changed the database by making use of the flag variables in both the student and faculty tables and, if either is true, saves a snap shot of the database using the undoer

public:
  DataBaseManager(); //default constructor
  ~DataBaseManager(); //destructor

  void presentMenuToUser(); //presents the available list of commands to the user

};

#endif
