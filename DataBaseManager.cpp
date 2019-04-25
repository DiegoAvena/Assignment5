#include "DataBaseManager.h"
using namespace std;

DataBaseManager::DataBaseManager() {

  masterStudent = new StudentTable();
  masterFaculty = new FacultyTable();
  undoer = new UndoManager<SnapShotContainer>(5);

}

DataBaseManager::~DataBaseManager() {

  delete masterFaculty;
  delete masterStudent;
  delete undoer;

  if (snapShotContainer != NULL) {

    delete snapShotContainer;

  }
  //delete tempFaculty;

}

void DataBaseManager::presentMenuToUser() {

  masterStudent->setUpTable(*masterStudent);
  masterFaculty->setUpTable(*masterFaculty);

  masterStudent->initializeReferentialIntegrityOfTable(masterStudent->getRoot(), *masterFaculty);
  //masterFaculty.getRoot();
  masterFaculty->initializeReferentialIntegrityOfTable(masterFaculty->getRoot(), *masterStudent);
  //tempFaculty(masterFaculty);
  //FacultyTable* tempFaculty = new FacultyTable(*masterFaculty);
  //tempFaculty =
  //tempFaculty->printFaculty(tempFaculty->getRoot(), masterStudent);
  //delete masterFaculty;
  //masterFaculty = new FacultyTable(*tempFaculty);
  //masterFaculty = tempFaculty;
  //masterFaculty = tempFaculty;

  //StudentTable* tempStudentTable = new StudentTable(*masterStudent);
  //tempStudentTable->printStudents(tempStudentTable->getRoot(), *masterFaculty);
  //delete masterStudent;
  //masterStudent = new StudentTable(*tempStudentTable);
  //delete tempStudentTable;

  while (true) {

    cout<<"DATABASE MAIN MENU"<<endl;
    cout<<"1.) Enter 1 to print all student information sorted by ascending student ID."<<endl;
    cout<<"2.) Enter 2 to print all faculty information sorted by ascending faculty ID."<<endl;
    cout<<"3.) Enter 3 to print information for a specific student."<<endl;
    cout<<"4.) Enter 4 to print information for a specific faculty."<<endl;
    cout<<"5.) Enter 5 to print information for a specific student's faculty advisor."<<endl;
    cout<<"6.) Enter 6 to print all of names and info of a faculties' advisees."<<endl;
    cout<<"7.) Enter 7 to add a new student into the database."<<endl;
    cout<<"8.) Enter 8 to delete a student from the database."<<endl;
    cout<<"9.) Enter 9 to add a new faculty member into the database."<<endl;
    cout<<"10.) Enter 10 to delete a faculty member from the database."<<endl;
    cout<<"11.) Enter 11 to change a students advisor."<<endl;
    cout<<"12.) Enter 12 to remove an advisee from a faculty member"<<endl;
    cout<<"13.) Enter 13 to undo last changes."<<endl;
    cout<<"14.) Enter 14 to exit."<<endl;

    int userResponse;
    cin>>userResponse;

    cout<<masterStudent->empty()<<endl;

    if (cin.fail()) {

      cin.clear();
      cin.ignore();
      cout<<"INVALID INPUT: Please enter an integer value only"<<endl;

    }
    else {

      if (determineWhichCommandToCarryOut(userResponse)) {

        break;

      }

    }

  }

}

void DataBaseManager::checkIfCommandChangedStructureOfDatabase() {

  if (masterStudent->getCommandModifiedTableSuccessfully()) {

    cout<<"The master student tree was changed!"<<endl;
    masterStudent->setCommandModifiedTableSuccessfully(false);
    undoer->saveSnapShot(snapShotContainer);

  }
  else if (masterFaculty->getCommandModifiedTableSuccessfully()) {

    cout<<"The master faculty tree was changed!"<<endl;
    masterFaculty->setCommandModifiedTableSuccessfully(false);
    undoer->saveSnapShot(snapShotContainer);

  }

  delete snapShotContainer;
  snapShotContainer = NULL;

}

bool DataBaseManager::determineWhichCommandToCarryOut(int response) {
  //SnapShotContainer(StudentTable* previousStudentTable, FacultyTable* previousFacultyTable);
  snapShotContainer = new SnapShotContainer(masterStudent, masterFaculty);
  cout<<"Master faculty tree in snapshot container has a list of advisees of size: "<<snapShotContainer->getPreviousFacultyTable()->listOfIDSThatExistInTree->getSize()<<endl;
  if (response == 1) {

    masterStudent->printStudents(masterStudent->getRoot(), *masterFaculty);
    delete snapShotContainer;
    snapShotContainer = NULL;
    return false;

  }
  else if (response == 2) {

    masterFaculty->printFaculty(masterFaculty->getRoot(), *masterStudent);
    delete snapShotContainer;
    snapShotContainer = NULL;
    return false;

  }
  else if (response == 3) {

    masterStudent->printASpecificStudent(*masterFaculty);
    delete snapShotContainer;
    snapShotContainer = NULL;
    return false;

  }
  else if (response == 4) {

    masterFaculty->printASpecificFacultyMember(*masterStudent);
    delete snapShotContainer;
    snapShotContainer = NULL;
    return false;

  }
  else if (response == 5) {

    masterStudent->printFacultyInformationForASpecificStudent(*masterFaculty);
    delete snapShotContainer;
    snapShotContainer = NULL;
    return false;

  }
  else if (response == 6) {

    masterFaculty->printAdviseeInfoForSpecificFacultyMember(*masterStudent);
    delete snapShotContainer;
    snapShotContainer = NULL;
    return false;

  }
  else if (response == 7) {

    masterStudent->addAStudent(*masterFaculty);
    checkIfCommandChangedStructureOfDatabase();
    return false;

  }
  else if (response == 8) {

    //delete a student given the student ID
    masterStudent->removeAStudent(*masterFaculty);
    checkIfCommandChangedStructureOfDatabase();
    return false;

  }
  else if (response == 9) {

    masterFaculty->AddAFacultyMember(*masterStudent);
    checkIfCommandChangedStructureOfDatabase();
    return false;

  }
  else if (response == 10) {

    //delete a faculty given their ID
    masterFaculty->removeAFacultyMember(*masterStudent);
    checkIfCommandChangedStructureOfDatabase();
    return false;

  }
  else if (response == 11) {

    //change a student's advisor given the student ID and the new faculty ID
    masterStudent->changeStudentsAdvisor(*masterFaculty);
    checkIfCommandChangedStructureOfDatabase();
    return false;

  }
  else if (response == 12) {

    //remove an advisee from a faculty member given the IDs
    masterFaculty->removeAnAdvisee(*masterStudent);
    checkIfCommandChangedStructureOfDatabase();
    return false;

  }
  else if (response == 13) {

    //rollback
    delete snapShotContainer;
    snapShotContainer = NULL;


    if (undoer->CheckIfUserCanRollback()) {

      SnapShotContainer* recentSnapShot = undoer->rollback();

      if (recentSnapShot != NULL) {

        cout<<"ROLLBACK STARTING..."<<endl;

        //there was a snapshot that can be set back to:
        FacultyTable* newFacultyTable = new FacultyTable(*recentSnapShot->getPreviousFacultyTable());
        StudentTable* newStudentTable = new StudentTable(*recentSnapShot->getPreviousStudentTable());

        cout<<"PREVIOUS TABLES AQQUIRED!"<<endl;

        //delete the tables that have the changes the user is trying to undo:
        cout<<newFacultyTable->listOfIDSThatExistInTree->getSize()<<endl;

        for (int i = 0; i < masterFaculty->listOfIDSThatExistInTree->getSize(); i++) {

          cout<<masterFaculty->listOfIDSThatExistInTree->findAt(i)<<endl;

        }

        delete masterFaculty; //Calling this right after removing a faculty causes a seg fault where the listOfIDSThatExistInTree was never allocated
        delete masterStudent;

        cout<<"OLD TABLES DELETED"<<endl;

        //set the tables that were just cleared to the new tables that are the previous data tables:
        masterFaculty = new FacultyTable(*newFacultyTable);
        masterStudent = new StudentTable(*newStudentTable);

        cout<<"OLD TABLES SET TO PREVIOUS TABLES!"<<endl;

        //delete the new tables that were made to store the previous tables the database was going back to
        delete newFacultyTable;
        delete newStudentTable;

        cout<<"DID SOME MEMORY CLEANUP"<<endl;
        cout<<"ROLLBACK SUCCESS!"<<endl;

      }

    }

    //cout<<"ROLLBACK FAILURE!"<<endl;

    return false;

  }
  else if (response == 14) {

    //exit and save both tables to the text file
    //masterFaculty->writeToFile(*masterFaculty, "facultyTable.txt");
    //masterStudent->writeToFile(*masterStudent, "studentTable.txt");

    cout<<"GOODBYE"<<endl;
    return true;

  }
  else {

    cout<<"Invalid response given. The integer you enter must be between 1 and 14"<<endl;
    delete snapShotContainer;
    snapShotContainer = NULL;
    return false;

  }

}

/*
int DataBaseManager::promptUserForAnID(string messageTellingUserWhatInputIsNeeded, bool searchForIDInMasterFaculty) {

  cout<<messageTellingUserWhatInputIsNeeded<<endl;
  int userResponse;
  cin>>userResponse;

  if (cin.fail()) {

    cin.clear();
    cin.ignore();
    cout<<"Invalid input: you need to enter an integer ID."<<endl;
    return -1;

  }
  else if (searchForIDInMasterFaculty) {

    TreeNode<int, Faculty>* node = masterFaculty.find(userResponse);

    if (node != NULL) {

      return node->getKey();

    }
    else {

      cout<<"Sorry, but the faculty with the ID you gave does not exist in the current Database"<<endl;
      return -1;

    }

  }
  else {

    TreeNode<int, Student>* node = masterStudent.find(userResponse);

    if (node != NULL) {

      return node->getKey();

    }
    else {

      cout<<"Sorry, but the student with the ID you gave does not exist in the current Database"<<endl;
      return -1;

    }

  }

}*/
