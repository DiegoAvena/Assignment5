#include "StudentTable.h"
//#include "FacultyTable.h"

using namespace std;

StudentTable::StudentTable():BinarySearchTree(){

  currentLineNumber = 1;
  numberOfFirstLineForDataSet = 1;

}

StudentTable::StudentTable(int rootKey, Student rootValue):BinarySearchTree(rootKey, rootValue){

  currentLineNumber = 1;
  numberOfFirstLineForDataSet = 1;

}

StudentTable::~StudentTable() {

  //output the contents of each node in this table to the text file, and than allow the base constructor to delete the tree:

}

void StudentTable::setUpTable(StudentTable& studentTableToBuild) {

  readFile("studentTable.txt", studentTableToBuild);

}

void StudentTable::writeToFileUsingSpecficRules(std::ofstream* fileToWriteTo, TreeNode<int, Student>* node) {

  if (node != NULL) {

    writeToFileUsingSpecficRules(fileToWriteTo, node->left);

    *fileToWriteTo<<node->getValue().getPersonID()<<endl;
    *fileToWriteTo<<node->getValue().getName()<<endl;
    *fileToWriteTo<<node->getValue().getLevel()<<endl;
    *fileToWriteTo<<node->getValue().getMajor()<<endl;
    *fileToWriteTo<<node->getValue().getStudentAdvisorID()<<endl;
    *fileToWriteTo<<node->getValue().getStudentGPA()<<endl;

    writeToFileUsingSpecficRules(fileToWriteTo, node->right);

  }

}


void StudentTable::changeStudentsAdvisor(FacultyTable& facultyTree) {

  int IDOfStudentToChangeAdvisorOf;
  int IDOfFacultyToChangeStudentAdvisorTo;

  //Ask user for the ID of which student they want to reassign the advisor of
  cout<<"Enter the ID of the student you wish to change the advisor of:"<<endl;
  cin>>IDOfStudentToChangeAdvisorOf;
  cin.ignore();

  if (cin.fail()) {

    cin.clear();
    cout<<"Invalid Input: you must enter an integer for the ID of the student you wish to change the advisor of"<<endl;
    return;

  }

  TreeNode<int, Student>* studentToChangeAdvisorFor = find(IDOfStudentToChangeAdvisorOf);
  if (studentToChangeAdvisorFor == NULL) {

    cout<<"Sorry, but the ID you entered is an ID for a student that does not exist in the current database."<<endl;
    return;

  }

  //Ask the user for the ID of the faculty member they want to reassign this student to:
  cout<<"Enter the ID of the faculty member you wish to assign this student to: "<<endl;
  cin>>IDOfFacultyToChangeStudentAdvisorTo;
  cin.ignore();

  if (cin.fail()) {

    cin.clear();
    cout<<"Invalid Input: You need to enter an integer ID for the faculty member you wish to reassign this student to"<<endl;
    return;

  }

  TreeNode<int, Faculty>* facultyToAssignThisStudentTo = facultyTree.find(IDOfFacultyToChangeStudentAdvisorTo);
  if (facultyToAssignThisStudentTo == NULL) {

    cout<<"Sorry, but the ID you entered is the ID of a faculty member that does not exist in the current database"<<endl;
    return;

  }

  //make sure this faculty is not already assigned to this student:
  if (facultyToAssignThisStudentTo->getValue().advisees->find(IDOfStudentToChangeAdvisorOf) != -1) {

    cout<<"The faculty member you chose to reassign this student to is already assigned to this student."<<endl;
    return;

  }

  ////Tell the previous advisor that they are no longer the advisor for this student:
  facultyTree.find(studentToChangeAdvisorFor->getValue().getStudentAdvisorID())->getValue().advisees->remove(studentToChangeAdvisorFor->getValue().getPersonID());

  //Perform the switch:
  studentToChangeAdvisorFor->getValue().setAdvisorID(IDOfFacultyToChangeStudentAdvisorTo);

  //tell the new advisor that they are now assigned to this student as an advisor:
  facultyTree.find(IDOfFacultyToChangeStudentAdvisorTo)->getValue().advisees->addFront(IDOfStudentToChangeAdvisorOf);

  cout<<"Student advisor has been changed"<<endl;

}

void StudentTable::initializeReferentialIntegrityOfTable(TreeNode<int, Student>* node, FacultyTable& treeToBaseReferenceOffOf) {

  if (node != NULL) {

    initializeReferentialIntegrityOfTable(node->left, treeToBaseReferenceOffOf);

    if ((treeToBaseReferenceOffOf.find(node->getValue().getStudentAdvisorID())) == false) {

      //this student is assigned an advisor that does not exist in the faculty tree:
      int randomNumber = rand() % treeToBaseReferenceOffOf.listOfIDSThatExistInTree.getSize();
      node->getValue().setAdvisorID(treeToBaseReferenceOffOf.listOfIDSThatExistInTree.findAt(randomNumber));

      bool needToAddStudentToAdvisorsList = true;
      for (int i = 0; i < treeToBaseReferenceOffOf.find(node->getValue().getStudentAdvisorID())->getValue().advisees->getSize(); i++) {

        if (node->getValue().getPersonID() == treeToBaseReferenceOffOf.find(node->getValue().getStudentAdvisorID())->getValue().advisees->findAt(i)) {

          needToAddStudentToAdvisorsList = false;

        }

      }

      if (needToAddStudentToAdvisorsList) {

        //this student was assigned to an existing faculty advisor but that faculty advisor needs to be notified to add this student to their list:
        treeToBaseReferenceOffOf.find(node->getValue().getStudentAdvisorID())->getValue().advisees->addFront(node->getValue().getPersonID());

      }

    }

    //by this point this student node has a valid advisee assigned to him or her, the line below signals that this is the case for this student node:
    node->getValue().setStudentHasBeenAssignedToAnAdviseeAlready(true);
    initializeReferentialIntegrityOfTable(node->right, treeToBaseReferenceOffOf);

  }

}


void StudentTable::printStudents(TreeNode<int, Student>* node, BinarySearchTree<int, Faculty>& tree) {

  if (node != NULL) {

    printStudents(node->left, tree);

    cout<<"------------------------------------------"<<endl;
    cout<<"Student ID: "<<node->getKey()<<endl;
    cout<<"Student Name: "<<node->getValue().getName()<<endl;
    cout<<"Student Level: "<<node->getValue().getLevel()<<endl;
    cout<<"Student Major: "<<node->getValue().getMajor()<<endl;
    cout<<"Student GPA: "<<node->getValue().getStudentGPA()<<endl;
    cout<<"Student advisor information: "<<endl;

    TreeNode<int, Faculty>* facultyNode = tree.find(node->getValue().getStudentAdvisorID());
    cout<<"   Advisor ID: "<<facultyNode->getValue().getPersonID()<<endl;
    cout<<"   Advisor Name: "<<facultyNode->getValue().getName()<<endl;
    cout<<"   Advisor Level: "<<facultyNode->getValue().getLevel()<<endl;
    cout<<"   Advisor department: "<<facultyNode->getValue().getDepartment()<<endl;

    /*cout<<"   Advisor Advisees: "<<endl;

    TreeNode<int, Student>* adviseeNode;

    for (int i = 0; i < facultyNode->getValue().advisees->getSize(); i++) {

      adviseeNode = find(facultyNode->getValue().advisees->findAt(i));

      cout<<"------------------------------------------"<<endl;
      cout<<"       Student ID: "<<adviseeNode->getKey()<<endl;
      cout<<"       Student Name: "<<adviseeNode->getValue().getName()<<endl;
      cout<<"       Student Level: "<<adviseeNode->getValue().getLevel()<<endl;
      cout<<"       Student Major: "<<adviseeNode->getValue().getMajor()<<endl;
      cout<<"       Student GPA: "<<adviseeNode->getValue().getStudentGPA()<<endl;
      cout<<"------------------------------------------"<<endl;

    }*/

    printStudents(node->right, tree);

  }

}

void StudentTable::printFacultyInformationForASpecificStudent(BinarySearchTree<int, Faculty>& tree) {

  cout<<"Enter the ID of the student you wish to see the Advisee information for."<<endl;
  int userResponse;
  cin>>userResponse;

  if (cin.fail()) {

    cin.clear();
    cin.ignore();
    cout<<"Invalid Input: you need to enter an integer ID"<<endl;

  }
  else {

    TreeNode<int, Student>* studentToPrintAdviseeInformationFor = find(userResponse);

    if (studentToPrintAdviseeInformationFor != NULL) {

      TreeNode<int, Faculty>* facultyToPrintInformationOf = tree.find(studentToPrintAdviseeInformationFor->getValue().getStudentAdvisorID());

      if (facultyToPrintInformationOf != NULL) {

        cout<<"Advisor ID: "<<facultyToPrintInformationOf->getValue().getPersonID()<<endl;
        cout<<"Advisor Name: "<<facultyToPrintInformationOf->getValue().getName()<<endl;
        cout<<"Advisor Level: "<<facultyToPrintInformationOf->getValue().getLevel()<<endl;
        cout<<"Advisor department: "<<facultyToPrintInformationOf->getValue().getDepartment()<<endl;
        cout<<"Advisor Advisees: "<<endl;

        //TreeNode<int, Student>* studentAdviseeToPrintInfoOf;

        for (int i = 0; i < facultyToPrintInformationOf->getValue().advisees->getSize(); i++) {

          cout<<"------------------------------------------"<<endl;
          studentToPrintAdviseeInformationFor = find(facultyToPrintInformationOf->getValue().advisees->findAt(i));
          cout<<"   Student ID: "<<studentToPrintAdviseeInformationFor->getKey()<<endl;
          cout<<"   Student Name: "<<studentToPrintAdviseeInformationFor->getValue().getName()<<endl;
          cout<<"   Student Level: "<<studentToPrintAdviseeInformationFor->getValue().getLevel()<<endl;
          cout<<"   Student Major: "<<studentToPrintAdviseeInformationFor->getValue().getMajor()<<endl;
          cout<<"   Student GPA: "<<studentToPrintAdviseeInformationFor->getValue().getStudentGPA()<<endl;
          cout<<"------------------------------------------"<<endl;

        }

      }

    }
    else {

      cout<<"Sorry, but the student with the ID you entered does not exist in the current database."<<endl;

    }

  }

}

void StudentTable::printASpecificStudent(BinarySearchTree<int, Faculty>& tree) {

  cout<<"Enter the ID of the student you wish to see the information of."<<endl;
  int userResponse;
  cin>>userResponse;

  if (cin.fail()) {

    cin.clear();
    cin.ignore();
    cout<<"Invalid Input: you need to enter an integer ID"<<endl;

  }
  else {

    TreeNode<int, Student>* studentNodeToPrintInformationOf = find(userResponse);

    if (studentNodeToPrintInformationOf != NULL) {

      cout<<"------------------------------------------"<<endl;
      cout<<"Student ID: "<<studentNodeToPrintInformationOf->getKey()<<endl;
      cout<<"Student Name: "<<studentNodeToPrintInformationOf->getValue().getName()<<endl;
      cout<<"Student Level: "<<studentNodeToPrintInformationOf->getValue().getLevel()<<endl;
      cout<<"Student Major: "<<studentNodeToPrintInformationOf->getValue().getMajor()<<endl;
      cout<<"Student GPA: "<<studentNodeToPrintInformationOf->getValue().getStudentGPA()<<endl;
      cout<<"Student advisor information: "<<endl;

      TreeNode<int, Faculty>* facultyNode = tree.find(studentNodeToPrintInformationOf->getValue().getStudentAdvisorID());

      if (facultyNode != NULL) {

        //TreeNode<int, Faculty>* facultyNode = tree.find(studentNodeToPrintInformationOf->getValue().getStudentAdvisorID());
        cout<<"   Advisor ID: "<<facultyNode->getValue().getPersonID()<<endl;
        cout<<"   Advisor Name: "<<facultyNode->getValue().getName()<<endl;
        cout<<"   Advisor Level: "<<facultyNode->getValue().getLevel()<<endl;
        cout<<"   Advisor department: "<<facultyNode->getValue().getDepartment()<<endl;

        /*cout<<"   Advisor Advisees: "<<endl;
        TreeNode<int, Student>* studentToPrintAdviseeInformationFor = find(userResponse);

        for (int i = 0; i < facultyNode->getValue().advisees->getSize(); i++) {

          cout<<"------------------------------------------"<<endl;
          studentToPrintAdviseeInformationFor = find(facultyNode->getValue().advisees->findAt(i));
          cout<<"       Student ID: "<<studentToPrintAdviseeInformationFor->getKey()<<endl;
          cout<<"       Student Name: "<<studentToPrintAdviseeInformationFor->getValue().getName()<<endl;
          cout<<"       Student Level: "<<studentToPrintAdviseeInformationFor->getValue().getLevel()<<endl;
          cout<<"       Student Major: "<<studentToPrintAdviseeInformationFor->getValue().getMajor()<<endl;
          cout<<"       Student GPA: "<<studentToPrintAdviseeInformationFor->getValue().getStudentGPA()<<endl;
          cout<<"------------------------------------------"<<endl;

        }*/

      }

      cout<<"------------------------------------------"<<endl;

    }
    else {

      cout<<"Sorry, but the student with the ID you entered does not exist in the current database."<<endl;

    }

  }

}

void StudentTable::removeAStudent(FacultyTable& facultyTree) {

  int IDOfStudentToRemove;
  cout<<"Enter the ID of the student you wish to remove from the current database"<<endl;
  cin>>IDOfStudentToRemove;
  cin.ignore();

  if (cin.fail()) {

    cin.clear();
    cout<<"Invalid Input: You must enter an integer ID for the student you wish to remove from the current database"<<endl;
    return;

  }

  TreeNode<int, Student>* studentToRemove = find(IDOfStudentToRemove);
  if (studentToRemove != NULL) {

    //find the advisor of this student to remove this student from their advisee list so that referential integrity is maintained:
    TreeNode<int, Faculty>* advisorOfThisStudent = facultyTree.find(studentToRemove->getValue().getStudentAdvisorID());
    advisorOfThisStudent->getValue().advisees->remove(IDOfStudentToRemove);

    //remove this student from the student table:
    erase(IDOfStudentToRemove);

  }
  else {

    cout<<"Sorry, but you entered the ID of a student that does not exist in the current database."<<endl;
    return;

  }

}

void StudentTable::addAStudent(FacultyTable& facultyTree) {

  int IDOfNewStudentToAdd;
  char nameOfNewStudentToAdd[256];
  char levelOfNewStudentToAdd[256];
  char majorOfNewStudentToAdd[256];
  double GPAOfNewStudentToAdd;
  int advisorIDOfNewStudentToAdd;

  cout<<"Enter an integer for the ID of the student you wish to add:"<<endl;
  cin>>IDOfNewStudentToAdd;
  cin.ignore();

  if (cin.fail()) {

    cout<<"Invalid Input: you must enter an integer for the student ID"<<endl;
    cin.clear();
    cin.ignore();
    return;

  }
  else if (find(IDOfNewStudentToAdd) != NULL) {

    //this ID is already in use by another student in the database:
    cout<<"Sorry, but the ID you entered is already in use by another student in the current database"<<endl;
    return;

  }

  cout<<"Enter the name of the new student you wish to add:"<<endl;
  cin.get(nameOfNewStudentToAdd, 256);
  cin.ignore();

  if (cin.fail()) {

    cout<<"Invalid Input: you failed to put a valid name for the student you wish to add"<<endl;
    cin.clear();
    return;

  }

  cout<<"Enter the level of the new student you wish to add:"<<endl;
  cin.get(levelOfNewStudentToAdd, 256);
  cin.ignore();

  if (cin.fail()) {

    cout<<"Invalid Input: you failed to put a valid level for the student you wish to add"<<endl;
    cin.clear();
    return;

  }

  cout<<"Enter the major of the new student you wish to add:"<<endl;
  cin.get(majorOfNewStudentToAdd, 256);
  cin.ignore();

  if (cin.fail()) {

    cout<<"Invalid Input: you failed to put a valid major for the student you wish to add"<<endl;
    cin.clear();
    return;

  }

  cout<<"Enter the GPA of the new student you wish to add:"<<endl;
  cin>>GPAOfNewStudentToAdd;
  cin.ignore();

  if (cin.fail()) {

    cout<<"Invalid Input: you failed to put a valid GPA for the student you wish to add"<<endl;
    cin.clear();
    return;

  }

  cout<<"Enter the advisor ID of the new student you wish to add:"<<endl;
  cin>>advisorIDOfNewStudentToAdd;
  cin.ignore();

  if (cin.fail()) {

    cout<<"Invalid Input: you failed to put a valid advisor ID for the student you wish to add"<<endl;
    cin.clear();
    return;

  }

  //maintain referential integrity:
  if (facultyTree.listOfIDSThatExistInTree.find(advisorIDOfNewStudentToAdd) == -1) {

    //this student has been given a faculty that does not actually exist in the current database, assign them to a random faculty member:
    int randomNumber = rand() % facultyTree.listOfIDSThatExistInTree.getSize();
    advisorIDOfNewStudentToAdd = facultyTree.listOfIDSThatExistInTree.findAt(randomNumber);

    //tell the advisor that they have been assigned to this student as an advisor:
    cout<<"STUDENT SET TO ADVISOR WITH ID: "<<advisorIDOfNewStudentToAdd<<endl;
    facultyTree.find(advisorIDOfNewStudentToAdd)->getValue().advisees->addFront(IDOfNewStudentToAdd);

  }

  Student newStudentToAdd(nameOfNewStudentToAdd, levelOfNewStudentToAdd, majorOfNewStudentToAdd, IDOfNewStudentToAdd, advisorIDOfNewStudentToAdd, GPAOfNewStudentToAdd);
  insert(newStudentToAdd.getPersonID(), newStudentToAdd);

}


void StudentTable::readFromFileWithSpecificRules(std::string line) {

  //Student studentToAddToTable;

  if (currentLineNumber == 1) {

    //this line contains the students id
    studentToAddToTable.setPersonID(stoi(line));

  }
  else if (currentLineNumber == 2) {

    //this line contains the student's name
    //cout<<line<<endl;
    studentToAddToTable.setName(line);

  }
  else if (currentLineNumber == 3) {

    //this line contains the student's level
    studentToAddToTable.setLevel(line);

  }
  else if (currentLineNumber == 4) {

    //this line contains the student's major
    studentToAddToTable.setMajor(line);

  }
  else if (currentLineNumber == 5) {

    //this line contains the student's advisor ID
    studentToAddToTable.setAdvisorID(stoi(line));

  }
  else if (currentLineNumber == 6) {

    //this line contains the student's gpa
    studentToAddToTable.setStudentGPA(stod(line));
    //currentLineNumber = 1;

  }

  if (currentLineNumber == 6) {

    currentLineNumber = 1;
    insert(studentToAddToTable.getPersonID(), studentToAddToTable);

  }
  else {

    currentLineNumber++;

  }

}
