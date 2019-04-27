#include "SnapShotContainer.h"
using namespace std;

//default constructor
SnapShotContainer::SnapShotContainer() {

  previousStudentTable = NULL;
  previousFacultyTable = NULL;

}

//Overloaded constructor, sets previousFacultyTable and previousStudentTable to the specified parameters
SnapShotContainer::SnapShotContainer(StudentTable* previousStudentTable, FacultyTable* previousFacultyTable) {

  this->previousStudentTable = new StudentTable(*previousStudentTable);//previousStudentTable;
  this->previousFacultyTable = new FacultyTable(*previousFacultyTable);//previousFacultyTable;

}

 //copy constructor
SnapShotContainer::SnapShotContainer(SnapShotContainer* snapShotContainerToCopy) {

  this->previousStudentTable = new StudentTable(*snapShotContainerToCopy->getPreviousStudentTable());
  this->previousFacultyTable = new FacultyTable(*snapShotContainerToCopy->getPreviousFacultyTable());

}

//Destructor
SnapShotContainer::~SnapShotContainer() {

  //insures the memory allocated for previousStudentTable is deallocated to prevent memory leaks
  if (previousStudentTable != NULL) {

    delete previousStudentTable;
    previousStudentTable = NULL;

  }

  //insures the memory allocated for previousFacultyTable is deallocated to prevent memory leaks
  if (previousFacultyTable != NULL) {

    delete previousFacultyTable;
    previousFacultyTable = NULL;

  }

}

//accessor method for getting a reference to the previousStudentTable
StudentTable* SnapShotContainer::getPreviousStudentTable() {

  return previousStudentTable;

}

//accessor method for getting a reference to the previousFacultyTable
FacultyTable* SnapShotContainer::getPreviousFacultyTable() {

  return previousFacultyTable;

}
