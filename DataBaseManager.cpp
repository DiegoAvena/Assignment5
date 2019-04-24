#include "DataBaseManager.h"
using namespace std;

DataBaseManager::DataBaseManager() {

}

DataBaseManager::~DataBaseManager() {

}

void DataBaseManager::presentMenuToUser() {

  masterStudent.setUpTable(masterStudent);
  masterFaculty.setUpTable(masterFaculty);

  masterStudent.initializeReferentialIntegrityOfTable(masterStudent.getRoot(), masterFaculty);
  masterFaculty.initializeReferentialIntegrityOfTable(masterFaculty.getRoot(), masterStudent);

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

    cout<<masterStudent.empty()<<endl;
    
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

bool DataBaseManager::determineWhichCommandToCarryOut(int response) {

  if (response == 1) {

    masterStudent.printStudents(masterStudent.getRoot(), masterFaculty);
    return false;

  }
  else if (response == 2) {

    masterFaculty.printFaculty(masterFaculty.getRoot(), masterStudent);
    return false;

  }
  else if (response == 3) {

    masterStudent.printASpecificStudent(masterFaculty);
    return false;

  }
  else if (response == 4) {

    masterFaculty.printASpecificFacultyMember(masterStudent);
    return false;

  }
  else if (response == 5) {

    masterStudent.printFacultyInformationForASpecificStudent(masterFaculty);
    return false;

  }
  else if (response == 6) {

    masterFaculty.printAdviseeInfoForSpecificFacultyMember(masterStudent);
    return false;

  }
  else if (response == 7) {

    masterStudent.addAStudent(masterFaculty);
    return false;

  }
  else if (response == 8) {

    //delete a student given the student ID
    masterStudent.removeAStudent(masterFaculty);
    return false;

  }
  else if (response == 9) {

    masterFaculty.AddAFacultyMember(masterStudent);
    return false;

  }
  else if (response == 10) {

    //delete a faculty given their ID
    return false;

  }
  else if (response == 11) {

    //change a student's advisor given the student ID and the new faculty ID
    return false;

  }
  else if (response == 12) {

    //remove an advisee from a faculty member given the IDs
    return false;

  }
  else if (response == 13) {

    //rollback
    return false;

  }
  else if (response == 14) {

    //exit and save both tables to the text file
    cout<<"GOODBYE"<<endl;
    return true;

  }
  else {

    cout<<"Invalid response given. The integer you enter must be between 1 and 14"<<endl;
    return false;

  }

}

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

}
