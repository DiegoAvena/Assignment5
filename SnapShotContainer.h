#ifndef SNAP_SHOT_CONTAINER_H
#define SNAP_SHOT_CONTAINER_H

#include "StudentTable.h"
#include "FacultyTable.h"
#include <iostream>

class SnapShotContainer {

private:
  StudentTable* previousStudentTable;
  FacultyTable* previousFacultyTable;

public:
  SnapShotContainer();
  SnapShotContainer(StudentTable* previousStudentTable, FacultyTable* previousFacultyTable);
  ~SnapShotContainer();
  SnapShotContainer(SnapShotContainer* snapShotContainerToCopy);

  StudentTable* getPreviousStudentTable();
  FacultyTable* getPreviousFacultyTable();

};

#endif
