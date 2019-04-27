#ifndef SNAP_SHOT_CONTAINER_H
#define SNAP_SHOT_CONTAINER_H

#include "StudentTable.h"
#include "FacultyTable.h"
#include <iostream>

/*

-SnapShotContainer is a container class that stores copies of
both the faculty and student table when a change is made to either of them (or to the database). This
is what is pushed onto the stack by the UndoManager, and popped of the stack when a rollback occurs.

*/
class SnapShotContainer {

private:
  StudentTable* previousStudentTable; //stores a copy of the student table prior to a change

  FacultyTable* previousFacultyTable; //stores a copy of the faculty table prior to a change

public:
  SnapShotContainer(); //default constructor

  SnapShotContainer(StudentTable* previousStudentTable, FacultyTable* previousFacultyTable); //Overloaded constructor, sets previousFacultyTable and previousStudentTable to the specified parameters

  ~SnapShotContainer(); //destructor

  SnapShotContainer(SnapShotContainer* snapShotContainerToCopy); //copy constructor

  StudentTable* getPreviousStudentTable(); //accessor method for getting a reference to the previousStudentTable

  FacultyTable* getPreviousFacultyTable(); //accessor method for getting a reference to the previousFacultyTable

};

#endif
