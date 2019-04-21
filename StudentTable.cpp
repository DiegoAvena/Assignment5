#include "StudentTable.h"
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

void StudentTable::printStudents(TreeNode<int, Student>* node) {

  if (node != NULL) {

    printStudents(node->left);
    cout<<"Student ID:"<<node->getKey()<<" | Student name: "<<node->getValue().getName()<<endl;
    printStudents(node->right);

  }

}

void StudentTable::readFromFileWithSpecificRules(std::string line) {

  //Student studentToAddToTable;

  if (currentLineNumber == 1) {

    //this line contains the students id
    studentToAddToTable.setPersonID(stoi(line));

  }
  else if (currentLineNumber == 2) {

    //this line contains the student's name
    cout<<line<<endl;
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
