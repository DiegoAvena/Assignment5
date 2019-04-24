#include "FacultyTable.h"

using namespace std;

//NOTE LINE 466: MIGHT BE A MEMORY LEAK!

FacultyTable::FacultyTable():BinarySearchTree(){

  facultyToAddToTable = new Faculty();
  currentLineNumber = 1;
  numberOfFirstLineForDataSet = 1;

}

void FacultyTable::writeToFileUsingSpecficRules(ofstream* fileToWriteTo, TreeNode<int, Faculty>* node) {

  //serializer = new ofstream("facultyTable.txt");
  if (node != NULL) {

    writeToFileUsingSpecficRules(fileToWriteTo, node->left);

    *fileToWriteTo <<node->getValue().getPersonID()<<endl; //write the ID of this faculty
    *fileToWriteTo <<node->getValue().getName()<<endl; //write the name of the faculty
    *fileToWriteTo <<node->getValue().getLevel()<<endl; //write the level of the faculty
    *fileToWriteTo <<node->getValue().getDepartment()<<endl; //write the department of the faculty
    *fileToWriteTo <<node->getValue().advisees->getSize()<<endl; //write the amount of advisees this faculty has

    //write all of the Advisee IDs down for this faculty member:
    for (int i = 0; i < node->getValue().advisees->getSize(); i++) {

      *fileToWriteTo<<node->getValue().advisees->findAt(i)<<endl;

    }

    writeToFileUsingSpecficRules(fileToWriteTo, node->right);

  }

}

FacultyTable::FacultyTable(int rootKey, Faculty rootValue):BinarySearchTree(rootKey, rootValue){}

FacultyTable::~FacultyTable(){

  //delete facultyToAddToTable;
  //cout<<"Delete anything for the faculty table"<<endl;
  deleteListOfAdviseesForEachFaculty(root);
  //delete serializer;

}

void FacultyTable::deleteListOfAdviseesForEachFaculty(TreeNode<int, Faculty>* node) {

  if (node != NULL) {

    deleteListOfAdviseesForEachFaculty(node->left);
    delete node->getValue().advisees;
    deleteListOfAdviseesForEachFaculty(node->right);

  }

}

void FacultyTable::AddAFacultyMember(BinarySearchTree<int, Student>& studentTreeReference) {

  //for info on cin.get(), I used: http://www.cplusplus.com/reference/istream/istream/get/
  int IDOfNewFaculty;
  char nameOfNewFaculty[256];
  char levelOfNewFaculty[256];
  char departmentOfNewFaculty[256];
  int IDOfNewFacultyAdvisee;

  cout<<"Enter the ID of the new faculty member you wish to add:"<<endl;
  cin>>IDOfNewFaculty;
  cin.ignore();

  if (cin.fail()) {

    cin.clear();
    cout<<"Invalid Input: you must enter an integer ID for the faculty you are trying to add."<<endl;
    return;

  }

  if (find(IDOfNewFaculty) != NULL) {

    //there is a faculty member with this exact ID already in the tree: This faculty cannot be entered with this ID
    cout<<"Sorry, but the ID you gave is already in use by another faculty in the current database."<<endl;
    return;

  }


  cout<<"Enter the name of the new faculty member you wish to add: "<<endl;
  cin.get(nameOfNewFaculty, 256);

  if (cin.fail()) {

    cout<<"Invalid Input: you did not enter a valid name for the new faculty you wish to add."<<endl;
    cin.ignore();
    cin.clear();
    return;

  }

  cin.ignore();

  cout<<"Enter the level of the new faculty member you wish to add: "<<endl;
  cin.get(levelOfNewFaculty, 256);

  if (cin.fail()) {

    cout<<"Invalid Input: you did not enter a valid level for the new faculty you wish to add."<<endl;
    cin.ignore();
    cin.clear();
    return;

  }

  cin.ignore();


  cout<<"Enter the department of the new faculty member you wish to add: "<<endl;
  cin.get(departmentOfNewFaculty, 256);

  if (cin.fail()) {

    cout<<"Invalid Input: you did not enter a valid department for the new faculty you wish to add."<<endl;
    cin.ignore();
    cin.clear();
    return;

  }

  cin.ignore();

  Faculty* newFacultyToAdd = new Faculty(nameOfNewFaculty, levelOfNewFaculty, departmentOfNewFaculty, IDOfNewFaculty);

  while (true) {

    cout<<"Enter a numerical ID for the Advisee you wish to add to this new faculty member, or you can enter -1 to stop and insert the faculty into the database."<<endl;
    cin>>IDOfNewFacultyAdvisee;

    if (cin.fail()) {

      cin.clear();
      cin.ignore();
      cout<<"Invalid input: sorry, but the ID you enter must be an integer"<<endl;

      delete newFacultyToAdd;
      break;

    }
    else if (IDOfNewFacultyAdvisee < 0) {

      insert(newFacultyToAdd->getPersonID(), *newFacultyToAdd);
      listOfIDSThatExistInTree.addFront(newFacultyToAdd->getPersonID());

      delete newFacultyToAdd;
      cout<<"Faculty member added!"<<endl;
      break;

    }
    else {

      TreeNode<int, Student>* studentNode = studentTreeReference.find(IDOfNewFacultyAdvisee);

      if (studentNode != NULL) {

        //remove this advisee from their previous advisor since a student should not have 2 advisors
        TreeNode<int, Faculty>* facultyToRemoveAdviseeFrom = find(studentNode->getValue().getStudentAdvisorID());
        facultyToRemoveAdviseeFrom->getValue().removeAdvisee(studentNode->getKey());

        //automatically reassigns this student to this new faculty member:
        studentNode->getValue().setAdvisorID(newFacultyToAdd->getPersonID());
        newFacultyToAdd->addAdvisee(studentNode->getValue().getPersonID());

        cout<<"Student added to advisee list"<<endl;

      }
      else {

        cout<<"Sorry, that ID you entered for the advisee is an ID for a student that does not exist in the current database"<<endl;

      }

    }

  }

}

void FacultyTable::printASpecificFacultyMember(BinarySearchTree<int, Student>& tree) {

  //TreeNode<int, Faculty>* nodeToPrint = find(keyOfNodeToPrint);
  cout<<"Enter the ID of the faculty member you wish to see the information of:"<<endl;
  int userResponse;
  cin>>userResponse;

  if (cin.fail()) {

    cin.clear();
    cin.ignore();
    cout<<"Invalid input: You must enter an integer ID."<<endl;

  }
  else {

    TreeNode<int, Faculty>* facultyNodeToPrintInformationOf = find(userResponse);

    if (facultyNodeToPrintInformationOf == NULL) {

      cout<<"Sorry, but the faculty with the ID you gave does not exist in the current database"<<endl;

    }
    else {

      cout<<"------------------------------------------"<<endl;
      cout<<"Faculty ID: "<<facultyNodeToPrintInformationOf->getKey()<<endl;
      cout<<"Faculty Name: "<<facultyNodeToPrintInformationOf->getValue().getName()<<endl;
      cout<<"Faculty Level: "<<facultyNodeToPrintInformationOf->getValue().getLevel()<<endl;
      cout<<"Faculty Department: "<<facultyNodeToPrintInformationOf->getValue().getDepartment()<<endl;
      cout<<"Faculty Advisee Info: "<<endl;

      //TreeNode<int, Student>* adviseeNode =
      for (int i = 0; i < facultyNodeToPrintInformationOf->getValue().advisees->getSize(); i++) {

        TreeNode<int, Student>* adviseeNode = tree.find(facultyNodeToPrintInformationOf->getValue().advisees->findAt(i));

        if (adviseeNode != NULL) {

          cout<<"   ------------------------------------------"<<endl;
          cout<<"   Advisee ID: "<<adviseeNode->getValue().getPersonID()<<endl;
          cout<<"   Advisee Name: "<<adviseeNode->getValue().getName()<<endl;
          cout<<"   Advisee Level: "<<adviseeNode->getValue().getLevel()<<endl;
          cout<<"   Advisee Major: "<<adviseeNode->getValue().getMajor()<<endl;
          cout<<"   Advisee GPA: "<<adviseeNode->getValue().getStudentGPA()<<endl;
          cout<<"   ------------------------------------------"<<endl;

        }

      }

    }


  }

}

void FacultyTable::printFaculty(TreeNode<int, Faculty>* node, BinarySearchTree<int, Student>& tree) {

  if (node != NULL) {

    printFaculty(node->left, tree);
    cout<<"------------------------------------------"<<endl;
    cout<<"Faculty ID: "<<node->getKey()<<endl;
    cout<<"Faculty Name: "<<node->getValue().getName()<<endl;
    cout<<"Faculty Level: "<<node->getValue().getLevel()<<endl;
    cout<<"Faculty Department: "<<node->getValue().getDepartment()<<endl;
    cout<<"Faculty Advisee Info: "<<endl;

    for (int i = 0; i < node->getValue().advisees->getSize(); i++) {
      cout<<"List size: "<<node->getValue().advisees->getSize()<<endl;
      TreeNode<int, Student>* adviseeNode = tree.find(node->getValue().advisees->findAt(i));

      if (node != NULL) {

        cout<<"   ------------------------------------------"<<endl;
        cout<<"   Advisee ID: "<<adviseeNode->getValue().getPersonID()<<endl;
        cout<<"   Advisee Name: "<<adviseeNode->getValue().getName()<<endl;
        cout<<"   Advisee Level: "<<adviseeNode->getValue().getLevel()<<endl;
        cout<<"   Advisee Major: "<<adviseeNode->getValue().getMajor()<<endl;
        cout<<"   Advisee GPA: "<<adviseeNode->getValue().getStudentGPA()<<endl;
        cout<<"   ------------------------------------------"<<endl;

      }

    }

    printFaculty(node->right, tree);

  }

}

void FacultyTable::printAdviseeInfoForSpecificFacultyMember(BinarySearchTree<int, Student>& tree) {

  cout<<"Enter the ID of the faculty you wish to see the Advisee information for."<<endl;
  int userResponse;
  cin>>userResponse;

  if (cin.fail()) {

    cin.clear();
    cin.ignore();
    cout<<"Invalid Input: You must enter an integer for the ID"<<endl;

  }
  else {

    TreeNode<int, Faculty>* facultyNode = find(userResponse);

    if (facultyNode != NULL) {

      TreeNode<int, Student>* adviseeNode;

      for (int i = 0; i < facultyNode->getValue().advisees->getSize(); i++) {

        adviseeNode = tree.find(facultyNode->getValue().advisees->findAt(i));

        cout<<"   ------------------------------------------"<<endl;
        cout<<"   Advisee ID: "<<adviseeNode->getValue().getPersonID()<<endl;
        cout<<"   Advisee Name: "<<adviseeNode->getValue().getName()<<endl;
        cout<<"   Advisee Level: "<<adviseeNode->getValue().getLevel()<<endl;
        cout<<"   Advisee Major: "<<adviseeNode->getValue().getMajor()<<endl;
        cout<<"   Advisee GPA: "<<adviseeNode->getValue().getStudentGPA()<<endl;
        cout<<"   ------------------------------------------"<<endl;

      }

    }
    else {

      cout<<"Sorry, but the faculty with the ID you entered does not exist in the current database"<<endl;

    }

  }


}


int FacultyTable::getCurrentLineNumber(){

  return currentLineNumber;

}

int FacultyTable::getNumberOfFirstLineForDataSet() {

  return numberOfFirstLineForDataSet;

}

int FacultyTable::getNumberOfLineWhereNumberOfAdviseesWasAt() {

  return numberOfLineWhereNumberOfAdviseesWasAt;

}

int FacultyTable::getNumberOfAdvisees() {

  return numberOfAdvisees;

}

void FacultyTable::setCurrentLineNumber(int currentLineNumber) {

  this->currentLineNumber = currentLineNumber;

}

void FacultyTable::setNumberOfFirstLineForDataSet(int numberOfFirstLineForDataSet) {

  this->numberOfFirstLineForDataSet = numberOfFirstLineForDataSet;

}

void FacultyTable::setNunberOfLineWhereNumberOfAdviseesWasAt(int numberOfLineWhereNumberOfAdviseesWasAt) {

  this->numberOfLineWhereNumberOfAdviseesWasAt = numberOfLineWhereNumberOfAdviseesWasAt;

}

void FacultyTable::setNumberOfAdvisees(int numberOfAdvisees) {

  this->numberOfAdvisees = numberOfAdvisees;

}

void FacultyTable::initializeReferentialIntegrityOfTable(TreeNode<int, Faculty>* node, BinarySearchTree<int, Student>& treeToBaseReferenceOffOf) {

  if (node != NULL) {

    initializeReferentialIntegrityOfTable(node->left, treeToBaseReferenceOffOf);

    DoubleLinkedList<int> listOfAdviseesToRemove;
    int numberOfAdviseesToRemove = 0;

    for (int i = 0; i < node->getValue().advisees->getSize(); i++) {

      cout<<"Checking for fake advisee"<<endl;

      if (treeToBaseReferenceOffOf.find(node->getValue().advisees->findAt(i)) == NULL) {

        //the faculty has an advisee that does not exist in the student table:
        cout<<"Removing fake advisee"<<endl;
        listOfAdviseesToRemove.addFront(node->getValue().advisees->findAt(i));

      }
      else if (treeToBaseReferenceOffOf.find(node->getValue().advisees->findAt(i))->getValue().getStudentAdvisorID() != node->getValue().getPersonID()) {

        cout<<"This student has a different faculty assigned to them already!"<<endl;
        listOfAdviseesToRemove.addFront(node->getValue().advisees->findAt(i));

      }

    }

    cout<<"setting referential integrity"<<endl;

    for (int i = 0; i < listOfAdviseesToRemove.getSize(); i++) {

      node->getValue().advisees->remove(listOfAdviseesToRemove.findAt(i));

    }

    cout<<"referential integrity set!"<<endl;

    initializeReferentialIntegrityOfTable(node->right, treeToBaseReferenceOffOf);

  }

}

void FacultyTable::removeAnAdvisee(BinarySearchTree<int, Student>& studentTreeReference) {

  int IDOfFacultyToRemoveAdviseeFor;
  int IDOfAdviseeToRemove;

  //get the ID of the faculty the user wishes to remove an advisee for:
  cout<<"Enter the ID for the faculty you wish to remove an advisee from"<<endl;

  cin>>IDOfFacultyToRemoveAdviseeFor;
  cin.ignore();

  if (cin.fail()) {

    cin.clear();
    cout<<"Invalid Input: You must enter an integer ID for the Faculty you wish to remove an advisee for"<<endl;
    return;

  }

  TreeNode<int, Faculty>* facultyToRemoveAdviseeFor = find(IDOfFacultyToRemoveAdviseeFor);
  if (facultyToRemoveAdviseeFor == NULL) {

    cout<<"Sorry, but the ID you gave is the ID of a faculty member that does not exist in the current database."<<endl;
    return;

  }

  //get the ID of the advisee the the user wishes to remove:
  cout<<"Enter the ID for the advisee you wish to remove from this faculty:"<<endl;
  cin>>IDOfAdviseeToRemove;
  cin.ignore();

  if (cin.fail()) {

    cin.clear();
    cout<<"Invalid Input: You need to enter an integer ID for the advisee you wish to remove from this faculty member"<<endl;
    return;

  }

  TreeNode<int, Student>* adviseeToRemove = studentTreeReference.find(IDOfAdviseeToRemove);
  if (adviseeToRemove == NULL) {

    cout<<"Sorry, but the ID you inserted is the ID of a student that does not exist in the current database"<<endl;
    return;

  }

  //check that the advisee the user wishes to remove from this faculty member is actually assigned to this faculty member:
  if (facultyToRemoveAdviseeFor->getValue().advisees->find(IDOfAdviseeToRemove) == -1) {

    //this advisee is not assigned to this faculty member:
    cout<<"Sorry, but teh advisee you wish to remove from this faculty member is not assigned to this faculty member."<<endl;
    return;

  }

  //Remove this advisee from this faculty member:
  facultyToRemoveAdviseeFor->getValue().advisees->remove(IDOfAdviseeToRemove);

  //automatically assign this advisee to another advisor:
  while (true) {

    int randomNumber = rand() % listOfIDSThatExistInTree.getSize();
    if (listOfIDSThatExistInTree.findAt(randomNumber) != IDOfFacultyToRemoveAdviseeFor) {

      //this is an advisor that is not the advisor the student was just removed from, assign them to this advisor:
      adviseeToRemove->getValue().setAdvisorID(listOfIDSThatExistInTree.findAt(randomNumber));

      //tell the new advisor that they have been assigned to this student as an advisor:
      find(adviseeToRemove->getValue().getStudentAdvisorID())->getValue().advisees->addFront(IDOfAdviseeToRemove);

      break;

    }

  }

  cout<<"Advisee removed and automatically reassigned to advisor with ID "<<adviseeToRemove->getValue().getStudentAdvisorID()<<endl;

}

void FacultyTable::setUpTable(FacultyTable& objectToBuildUsingTheTextFile) {

  readFile("facultyTable.txt", objectToBuildUsingTheTextFile);

}

void FacultyTable::removeAFacultyMember(BinarySearchTree<int, Student>& studentTreeReference) {

  int IDOfFacultyToRemove;
  cout<<"Enter the ID of the faculty member you wish to remove from the database"<<endl;
  cin>>IDOfFacultyToRemove;

  if (cin.fail()) {

    cin.clear();
    cout<<"Invalid Input: You must enter an integer for the ID of the faculty you wish to remove"<<endl;
    return;

  }
  else {

    TreeNode<int, Faculty>* facultyNodeToRemove = find(IDOfFacultyToRemove);

    if (facultyNodeToRemove != NULL) {

      //remove the ID of the faculty that is about to be deleted from the list of faculty IDs currently in the tree
      listOfIDSThatExistInTree.remove(IDOfFacultyToRemove);

      //Reassign each of the advisees for this faculty member to a new advisor
      if (listOfIDSThatExistInTree.empty() == false) {

        //there are still faculties that can be assigned to the advisees of this faculty
        for (int i = 0; i < facultyNodeToRemove->getValue().advisees->getSize(); i++) {

          int IDOfAdviseeToReassign = facultyNodeToRemove->getValue().advisees->findAt(i);

          int randomNumber = rand() % listOfIDSThatExistInTree.getSize(); //randomly reassign:
          studentTreeReference.find(IDOfAdviseeToReassign)->getValue().setAdvisorID(listOfIDSThatExistInTree.findAt(randomNumber));

          //tell the advisor being assigned to this new advisee that they have been assigned to this new advisee:
          int IDOfAdvisorToAssignAdviseeTo = listOfIDSThatExistInTree.findAt(randomNumber);
          find(IDOfAdvisorToAssignAdviseeTo)->getValue().addAdvisee(IDOfAdviseeToReassign);

        }

      }

      //erase the faculty from the tree
      cout<<"Faculty member removed from database."<<endl;
      erase(IDOfFacultyToRemove);

    }
    else {

      cout<<"Sorry, but the ID of the faculty member you wish to remove does not exist in the currrent database"<<endl;
      return;

    }

  }

}

void FacultyTable::readFromFileWithSpecificRules(string line) {

  //std::cout<<objectToBuildUsingTheTextFile.getCurrentLineNumber()<<std::endl;
  //cout<<"Creating faculty..."<<endl;
  if (currentLineNumber == 1) {

    //this is the faculty's id
    //cout<<"Faculty ID"<<endl;
    facultyToAddToTable->setPersonID(stoi(line));

  }
  else if (currentLineNumber == 2) {

    //this is the faculty's name
    //cout<<"Faculty name"<<endl;
    facultyToAddToTable->setName(line);

  }
  else if (currentLineNumber == 3) {

    //this is the faculty's level
    //cout<<"Faculty level"<<endl;
    facultyToAddToTable->setLevel(line);

  }
  else if (currentLineNumber == 4) {

    //this is the faculty's department
    //cout<<"faculty department"<<endl;
    facultyToAddToTable->setDepartment(line);


  }
  else if (currentLineNumber == 5) {

    //this is the line that contains the number of numberOfAdvisees this faculty has:
    //std::cout<<"Faculty ID: "<<stoi(line)<<std::endl;
    //cout<<"Number of advisees"<<endl;
    numberOfAdvisees = stoi(line);

  }
  else if ((currentLineNumber - 5) <= numberOfAdvisees) {

    //this line has the id of a advisee
    //cout<<"Adding advisee"<<endl;
    facultyToAddToTable->addAdvisee(stoi(line));

  }

  if (((currentLineNumber - 5) == numberOfAdvisees)) {

    //cout<<"Adding faculty..."<<endl;
    //we were on the last line representing data for this faculty, the object is now ready to be added into the tree, and everything should be reset for next faculty:
    //std::cout<<currentLineNumber<<std::endl;

    //std::cout<<"Inserting faculty into tree..."<<std::endl;
    //objectToBuildUsingTheTextFile.setCurrentLineNumber(1);
    currentLineNumber = 1;
    numberOfAdvisees = 0;
    //objectToBuildUsingTheTextFile.setNumberOfAdvisees(0);
    std::cout<<"Number of Advisees: "<<facultyToAddToTable->advisees->getSize()<<std::endl;

    int arrayOfAdvisees[facultyToAddToTable->advisees->getSize()];

    for (int i = 0; i < facultyToAddToTable->advisees->getSize(); i++) {

      //std::cout<<facultyToAddToTable->advisees->findAt(i)<<std::endl;
      arrayOfAdvisees[i] = facultyToAddToTable->advisees->findAt(i);

    }

    listOfIDSThatExistInTree.addFront(facultyToAddToTable->getPersonID());
    insert(facultyToAddToTable->getPersonID(), /*Faculty(facultyToAddToTable.getName(), facultyToAddToTable.getLevel(), facultyToAddToTable.getDepartment(), facultyToAddToTable.getPersonID(), arrayOfAdvisees, facultyToAddToTable.getAdvisees().getSize())*/*facultyToAddToTable);
    //delete facultyToAddToTable->advisees;
    delete facultyToAddToTable;
    facultyToAddToTable = new Faculty();

    //cout<<"Faculty added!"<<endl;

  }
  else {

    currentLineNumber++;

  }

}
