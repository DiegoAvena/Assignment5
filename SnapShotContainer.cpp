#include "SnapShotContainer.h"
using namespace std;

SnapShotContainer::SnapShotContainer() {

  previousStudentTable = NULL;
  previousFacultyTable = NULL;

}

SnapShotContainer::SnapShotContainer(StudentTable* previousStudentTable, FacultyTable* previousFacultyTable) {

  this->previousStudentTable = new StudentTable(*previousStudentTable);//previousStudentTable;
  this->previousFacultyTable = new FacultyTable(*previousFacultyTable);//previousFacultyTable;

}

SnapShotContainer::SnapShotContainer(SnapShotContainer* snapShotContainerToCopy) {

  this->previousStudentTable = new StudentTable(*snapShotContainerToCopy->getPreviousStudentTable());
  this->previousFacultyTable = new FacultyTable(*snapShotContainerToCopy->getPreviousFacultyTable());

}

SnapShotContainer::~SnapShotContainer() {

  if (previousStudentTable != NULL) {

    delete previousStudentTable;
    previousStudentTable = NULL;

  }

  if (previousFacultyTable != NULL) {

    delete previousFacultyTable;
    previousFacultyTable = NULL;

  }

}

StudentTable* SnapShotContainer::getPreviousStudentTable() {

  return previousStudentTable;

}

FacultyTable* SnapShotContainer::getPreviousFacultyTable() {

  return previousFacultyTable;

}
