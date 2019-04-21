#include "FacultyTable.h"

using namespace std;

FacultyTable::FacultyTable():BinarySearchTree(){

  facultyToAddToTable = new Faculty();
  //listOfFacultyToDelete = new DoubleLinkedList<Faculty>();

  currentLineNumber = 1;
  numberOfFirstLineForDataSet = 1;

}

FacultyTable::FacultyTable(int rootKey, Faculty rootValue):BinarySearchTree(rootKey, rootValue){}

FacultyTable::~FacultyTable(){

  //delete facultyToAddToTable;
  //cout<<"Delete anything for the faculty table"<<endl;
  deleteListOfAdviseesForEachFaculty(root);

}

void FacultyTable::deleteListOfAdviseesForEachFaculty(TreeNode<int, Faculty>* node) {

  if (node != NULL) {

    deleteListOfAdviseesForEachFaculty(node->left);
    delete node->getValue().advisees;
    //std::cout<<"Deleting lists allocated for each faculty in the tree..."<<std::endl;
    deleteListOfAdviseesForEachFaculty(node->right);

  }

}


void FacultyTable::printFaculty(TreeNode<int, Faculty>* node) {

  if (node != NULL) {

    printFaculty(node->left);
    cout<<"Faculty ID: "<<node->getKey()<<endl;
    cout<<"Advisees: "<<endl;
    node->getValue().printAdviseeIds();
    printFaculty(node->right);

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

/*Faculty FacultyTable::getFacultyToAddToTable() {

  return facultyToAddToTable;

}*/

void FacultyTable::setUpTable(FacultyTable& objectToBuildUsingTheTextFile) {

  readFile("facultyTable.txt", objectToBuildUsingTheTextFile);

}

void FacultyTable::readFromFileWithSpecificRules(string line) {

  //std::cout<<objectToBuildUsingTheTextFile.getCurrentLineNumber()<<std::endl;
  if (currentLineNumber == 1) {

    //this is the faculty's id
    //std::cout<<"Faculty ID: "<<stoi(line)<<std::endl;
    facultyToAddToTable->setPersonID(stoi(line));

  }
  else if (currentLineNumber == 2) {

    //this is the faculty's name
    facultyToAddToTable->setName(line);

  }
  else if (currentLineNumber == 3) {

    //this is the faculty's level
    facultyToAddToTable->setLevel(line);

  }
  else if (currentLineNumber == 4) {

    //this is the faculty's department
    facultyToAddToTable->setDepartment(line);


  }
  else if (currentLineNumber == 5) {

    //this is the line that contains the number of numberOfAdvisees this faculty has:
    //std::cout<<"Faculty ID: "<<stoi(line)<<std::endl;
    numberOfAdvisees = stoi(line);

  }
  else if ((currentLineNumber - 5) <= numberOfAdvisees) {

    //this line has the id of a advisee
    facultyToAddToTable->addAdvisee(stoi(line));

  }

  if (((currentLineNumber - 5) == numberOfAdvisees)) {

    //we were on the last line representing data for this faculty, the object is now ready to be added into the tree, and everything should be reset for next faculty:
    //std::cout<<currentLineNumber<<std::endl;

    //std::cout<<"Inserting faculty into tree..."<<std::endl;
    //objectToBuildUsingTheTextFile.setCurrentLineNumber(1);
    currentLineNumber = 1;
    numberOfAdvisees = 0;
    //objectToBuildUsingTheTextFile.setNumberOfAdvisees(0);
    //std::cout<<"Number of Advisees: "<<facultyToAddToTable->advisees->getSize()<<std::endl;

    int arrayOfAdvisees[facultyToAddToTable->advisees->getSize()];

    for (int i = 0; i < facultyToAddToTable->advisees->getSize(); i++) {

      //std::cout<<facultyToAddToTable->advisees->findAt(i)<<std::endl;
      arrayOfAdvisees[i] = facultyToAddToTable->advisees->findAt(i);

    }

    insert(facultyToAddToTable->getPersonID(), /*Faculty(facultyToAddToTable.getName(), facultyToAddToTable.getLevel(), facultyToAddToTable.getDepartment(), facultyToAddToTable.getPersonID(), arrayOfAdvisees, facultyToAddToTable.getAdvisees().getSize())*/*facultyToAddToTable);
    //delete facultyToAddToTable->advisees;
    delete facultyToAddToTable;
    facultyToAddToTable = new Faculty();

  }
  else {

    currentLineNumber++;

  }


}
