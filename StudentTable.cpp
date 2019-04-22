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

    printStudents(node->right, tree);

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

        TreeNode<int, Faculty>* facultyNode = tree.find(studentNodeToPrintInformationOf->getValue().getStudentAdvisorID());
        cout<<"   Advisor ID: "<<facultyNode->getValue().getPersonID()<<endl;
        cout<<"   Advisor Name: "<<facultyNode->getValue().getName()<<endl;
        cout<<"   Advisor Level: "<<facultyNode->getValue().getLevel()<<endl;
        cout<<"   Advisor department: "<<facultyNode->getValue().getDepartment()<<endl;

      }

      cout<<"------------------------------------------"<<endl;

    }
    else {

      cout<<"Sorry, but the student with the ID you entered does not exist in the current database."<<endl;

    }

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
