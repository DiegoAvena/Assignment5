#ifndef DATA_BASE_MANAGER_H
#define DATA_BASE_MANAGER_H

#include "StudentTable.h"
#include "FacultyTable.h"
#include "TreeNode.h"
#include <iostream>
#include "UndoManager.h"
#include "SnapShotContainer.h"
//#include "FileOutputManager.h"

class DataBaseManager {

private:
  StudentTable* masterStudent;
  FacultyTable* masterFaculty;
  UndoManager<SnapShotContainer>* undoer;

  SnapShotContainer* snapShotContainer;

  bool determineWhichCommandToCarryOut(int response);

  void getRestOfInputForOptionThree();
  void getRestOfInputForOptionFour();

  int promptUserForAnID(std::string messageTellingUserWhatInputIsNeeded, bool searchForIDInMasterFaculty);
  void checkIfCommandChangedStructureOfDatabase();

public:
  DataBaseManager();
  ~DataBaseManager();

  void presentMenuToUser();

};

#endif
