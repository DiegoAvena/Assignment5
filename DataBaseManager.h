#ifndef DATA_BASE_MANAGER_H
#define DATA_BASE_MANAGER_H

#include "StudentTable.h"
#include "FacultyTable.h"

class DataBaseManager {

private:
  StudentTable masterStudent;
  FacultyTable masterFaculty;

public:
  DataBaseManager();
  ~DataBaseManager();

  //void initializeMasterStudent();
  //void initializeMasterFaculty();

  //void initializeTree(int ID, Student student);
  //void initializeTree(int ID, Faculty faculty);

  void addToTable(int ID, Student student);
  void addToTable(int ID, Faculty faculty);

  void presentMenuToUser();

};

#endif
