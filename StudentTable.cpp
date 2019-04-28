#include "StudentTable.h"
//#include "FacultyTable.h"

using namespace std;

//default constructor
StudentTable::StudentTable():BinarySearchTree(){

  currentLineNumber = 1;
  commandModifiedTableSuccessfully = false;

}

//overloaded constructor, sets the root of the tree using rootKey and rootValue
StudentTable::StudentTable(int rootKey, Student rootValue):BinarySearchTree(rootKey, rootValue){

  currentLineNumber = 1;
  commandModifiedTableSuccessfully = false;

}

//destructor
StudentTable::~StudentTable() {

}

//copy constructor
StudentTable::StudentTable(StudentTable& tableToCopy) {

  commandModifiedTableSuccessfully = false;
  traverseTreeToCopyIt(tableToCopy.getRoot());

}

//accessor method for commandModifiedTableSuccessfully
bool StudentTable::getCommandModifiedTableSuccessfully() {

  return commandModifiedTableSuccessfully;

}

//Mutator method for commandModifiedTableSuccessfully
void StudentTable::setCommandModifiedTableSuccessfully(bool commandModifiedTableSuccessfully) {

  this->commandModifiedTableSuccessfully = commandModifiedTableSuccessfully;

}

//traverses the entire tree in order to copy its nodes into a new tree, used by the copy constructor
void StudentTable::traverseTreeToCopyIt(TreeNode<int, Student>* node) {

  if (node != NULL) {

    traverseTreeToCopyIt(node->left);

    //std::cout<<"Inserting node"<<std::endl;
    Student* student = new Student(node->getValue().getName(), node->getValue().getLevel(), node->getValue().getMajor(), node->getValue().getPersonID(), node->getValue().getStudentAdvisorID(), node->getValue().getStudentGPA());
    insert(student->getPersonID(), *student);
    delete student;

    traverseTreeToCopyIt(node->right);

  }

}

//initializes the table by reading over the setUpTable.txt file so that Student nodes can be made from its data and added into this student tree
void StudentTable::setUpTable(StudentTable& studentTableToBuild) {

  //Class extended from FileInputManager in order to use this method to read over a file
  readFile("studentTable.txt", studentTableToBuild);

}

//Allows the FileOutputManager to write back to a file following the rules set for how a studentTable.txt file should be organized.
void StudentTable::writeToFileUsingSpecficRules(std::ofstream* fileToWriteTo, TreeNode<int, Student>* node) {

  //uses inorder traversal so that student nodes are written onto the file by ascending student ID order
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

//Changes a students advisor provided the student ID given is valid and the faculty ID given is valid
void StudentTable::changeStudentsAdvisor(FacultyTable& facultyTree) {

  int IDOfStudentToChangeAdvisorOf; //store the ID of the student the user wants to work with
  int IDOfFacultyToChangeStudentAdvisorTo; //store the ID of the faculty member the user wants to work with

  //Ask user for the ID of which student they want to reassign the advisor of
  cout<<"Enter the ID of the student you wish to change the advisor of:"<<endl;
  cin>>IDOfStudentToChangeAdvisorOf;
  cin.ignore(); //prevents the next input from being skipped over

  //in cases where the user does not input an integer ID, cin will be placed into an error state that needs to be cleared before it can be used again
  if (cin.fail()) {

    cin.clear(); //clear the error state of cin so that it can be used to obtain input again
    cout<<"Invalid Input: you must enter an integer for the ID of the student you wish to change the advisor of"<<endl;
    return; //exit the command

  }

  TreeNode<int, Student>* studentToChangeAdvisorFor = find(IDOfStudentToChangeAdvisorOf);

  if (studentToChangeAdvisorFor == NULL) {

    //The student given is not a real student in the database so the command should exit
    cout<<"Sorry, but the ID you entered is an ID for a student that does not exist in the current database."<<endl;
    return; //exit the command

  }

  //Ask the user for the ID of the faculty member they want to reassign this student to:
  cout<<"Enter the ID of the faculty member you wish to assign this student to: "<<endl;
  cin>>IDOfFacultyToChangeStudentAdvisorTo;
  cin.ignore(); //prevents the next input from being skipped over

  //in cases where the user does not input an integer ID, cin will be placed into an error state that needs to be cleared before it can be used again
  if (cin.fail()) {

    cin.clear();  //clear the error state of cin so that it can be used to obtain input again
    cout<<"Invalid Input: You need to enter an integer ID for the faculty member you wish to reassign this student to"<<endl;
    return; //exit the command

  }

  TreeNode<int, Faculty>* facultyToAssignThisStudentTo = facultyTree.find(IDOfFacultyToChangeStudentAdvisorTo);
  if (facultyToAssignThisStudentTo == NULL) {

    //the user is trying to deal with a faculty member that does not exit in the current database
    cout<<"Sorry, but the ID you entered is the ID of a faculty member that does not exist in the current database"<<endl;
    return;

  }

  //By this point, the facultyToAssignThisStudentTo is for sure in the tree, so there is no need to worry about getting seg faults here by trying to access its members

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

  commandModifiedTableSuccessfully = true; //the command worked, so set the flag so that the program knows to save the snapshot taken prior to this change
  cout<<"Student advisor has been changed"<<endl;

}

//insures that upon the start of the program, every student is assigned to a faculty member that does exist in the faculty table,
void StudentTable::initializeReferentialIntegrityOfTable(TreeNode<int, Student>* node, FacultyTable& treeToBaseReferenceOffOf) {

  if (node != NULL) {

    initializeReferentialIntegrityOfTable(node->left, treeToBaseReferenceOffOf);

    TreeNode<int, Faculty>* facultyAdvisorForThisStudent = treeToBaseReferenceOffOf.find(node->getValue().getStudentAdvisorID());

    if ((facultyAdvisorForThisStudent == NULL) && (treeToBaseReferenceOffOf.empty() == false)) {

      //this student is assigned an advisor that does not exist in the faculty tree, and the faculty tree is not empty, so there are advisors that can be assigned to this student:
      int randomNumber = rand() % treeToBaseReferenceOffOf.listOfIDSThatExistInTree->getSize(); //generate a random number between 0 and (the number of faculties in the faculty table - 1) that will be used to randomly assign this student to a faculty member in the faculty table

      node->getValue().setAdvisorID(treeToBaseReferenceOffOf.listOfIDSThatExistInTree->findAt(randomNumber));

      //since the ID for the advisor was pulled out of the listOfIDSThatExistInTree, then there is for sure a faculty member with this ID sinze this list keeps track of this in the tree so there is no need to worry about seg faults:
      facultyAdvisorForThisStudent = treeToBaseReferenceOffOf.find(node->getValue().getStudentAdvisorID());

      bool needToAddStudentToAdvisorsList = true;
      for (int i = 0; i < facultyAdvisorForThisStudent->getValue().advisees->getSize(); i++) {

        if (node->getValue().getPersonID() == facultyAdvisorForThisStudent->getValue().advisees->findAt(i)) {

          //the student is already assigned to this faculty member, do not add student into this advisor's list of advisees
          cout<<"Advisor does not need to be notified that they have a new advisee..."<<endl;
          needToAddStudentToAdvisorsList = false;

        }

      }

      if (needToAddStudentToAdvisorsList) {

        //this student was assigned to an existing faculty advisor but that faculty advisor needs to be notified to add this student to their list:
        cout<<"Faculty now has "<<facultyAdvisorForThisStudent->getValue().advisees->getSize()<<" advisees assigned to them"<<endl;
        facultyAdvisorForThisStudent->getValue().advisees->addFront(node->getValue().getPersonID());

      }

    }
    else if (facultyAdvisorForThisStudent != NULL) {

      if (facultyAdvisorForThisStudent->getValue().advisees->find(node->getValue().getPersonID()) == -1) {

        //the advisee has a faculty advisor that exists in the faculty tree, but that advisor needs to be notified that they are assigned to this student:
        facultyAdvisorForThisStudent->getValue().advisees->addFront(node->getValue().getPersonID());

      }

    }

    //by this point this student node has a valid advisee assigned to him or her, the line below signals that this is the case for this student node:
    initializeReferentialIntegrityOfTable(node->right, treeToBaseReferenceOffOf);

  }

}

//prints the information of every student in the studentTable, including the information of their advisor, by ascending student ID
void StudentTable::printStudents(TreeNode<int, Student>* node, BinarySearchTree<int, Faculty>& tree) {

  //used inorder traversal so that students are printed in ascending student ID order
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

    if (facultyNode != NULL) {

      //the student has an advisor assigned to them that we can see info of
      cout<<"   Advisor ID: "<<facultyNode->getValue().getPersonID()<<endl;
      cout<<"   Advisor Name: "<<facultyNode->getValue().getName()<<endl;
      cout<<"   Advisor Level: "<<facultyNode->getValue().getLevel()<<endl;
      cout<<"   Advisor department: "<<facultyNode->getValue().getDepartment()<<endl;

    }
    else {

      //the student does not have an advisor:
      cout<<"   N/A"<<endl;

    }

    printStudents(node->right, tree);

  }

}

//prints the advisor info for a specific student
void StudentTable::printFacultyInformationForASpecificStudent(BinarySearchTree<int, Faculty>& tree) {

  //ask user for the id of the student they want to deal with
  cout<<"Enter the ID of the student you wish to see the Advisee information for."<<endl;
  int userResponse;
  cin>>userResponse;
  cin.ignore(); //insures that cin does not skip over input lines when user is asked for input, so that user can actually enter the input

  if (cin.fail()) {

    //cin may fail in cases where user does not enter an integer id, so its error state needs to be cleared so that cin can be used again
    cin.clear();
    cout<<"Invalid Input: you need to enter an integer ID"<<endl;

    //command exits/aborts if this case occurs

  }
  else {

    TreeNode<int, Student>* studentToPrintAdviseeInformationFor = find(userResponse);

    if (studentToPrintAdviseeInformationFor != NULL) {

      //the student the user wants to deal with is a student that exists in the current database

      TreeNode<int, Faculty>* facultyToPrintInformationOf = tree.find(studentToPrintAdviseeInformationFor->getValue().getStudentAdvisorID());

      if (facultyToPrintInformationOf != NULL) {

        //the student has an advisor:
        cout<<"Advisor ID: "<<facultyToPrintInformationOf->getValue().getPersonID()<<endl;
        cout<<"Advisor Name: "<<facultyToPrintInformationOf->getValue().getName()<<endl;
        cout<<"Advisor Level: "<<facultyToPrintInformationOf->getValue().getLevel()<<endl;
        cout<<"Advisor department: "<<facultyToPrintInformationOf->getValue().getDepartment()<<endl;
        cout<<"Advisor Advisees: "<<endl;

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
      else {

        //student does not have an advisor
        cout<<"   N/A"<<endl;

      }

    }
    else {

      //the student the user wants to deal with does not exist in the current database, command exits/aborts if this is the case
      cout<<"Sorry, but the student with the ID you entered does not exist in the current database."<<endl;

    }

  }

}

//prints the information for a specific student
void StudentTable::printASpecificStudent(BinarySearchTree<int, Faculty>& tree) {

  //ask the user for the ID of the student they want to deal with
  cout<<"Enter the ID of the student you wish to see the information of."<<endl;
  int userResponse;
  cin>>userResponse;
  cin.ignore(); //insures that cin does not skip over input lines when user is asked for input, so that user can actually enter the input

  if (cin.fail()) {

    //cin may fail in cases where user does not enter an integer id, so its error state needs to be cleared so that cin can be used again
    cin.clear();
    cout<<"Invalid Input: you need to enter an integer ID"<<endl;

  }
  else {

    TreeNode<int, Student>* studentNodeToPrintInformationOf = find(userResponse);

    if (studentNodeToPrintInformationOf != NULL) {
      //the student the user wants to deal with exists in the current database:

      cout<<"------------------------------------------"<<endl;
      cout<<"Student ID: "<<studentNodeToPrintInformationOf->getKey()<<endl;
      cout<<"Student Name: "<<studentNodeToPrintInformationOf->getValue().getName()<<endl;
      cout<<"Student Level: "<<studentNodeToPrintInformationOf->getValue().getLevel()<<endl;
      cout<<"Student Major: "<<studentNodeToPrintInformationOf->getValue().getMajor()<<endl;
      cout<<"Student GPA: "<<studentNodeToPrintInformationOf->getValue().getStudentGPA()<<endl;
      cout<<"Student advisor information: "<<endl;

      TreeNode<int, Faculty>* facultyNode = tree.find(studentNodeToPrintInformationOf->getValue().getStudentAdvisorID());

      if (facultyNode != NULL) {

        //the student has an advisor:
        cout<<"   Advisor ID: "<<facultyNode->getValue().getPersonID()<<endl;
        cout<<"   Advisor Name: "<<facultyNode->getValue().getName()<<endl;
        cout<<"   Advisor Level: "<<facultyNode->getValue().getLevel()<<endl;
        cout<<"   Advisor department: "<<facultyNode->getValue().getDepartment()<<endl;

      }
      else {

        //no advisor information to print out:
        cout<<"N/A"<<endl;

      }

      cout<<"------------------------------------------"<<endl;

    }
    else {

      //the student the user wants to deal with does not exist in the current database
      cout<<"Sorry, but the student with the ID you entered does not exist in the current database."<<endl;

    }

  }

}

//removes a student from the student table provided the user enters valid Student and faculty IDs
void StudentTable::removeAStudent(FacultyTable& facultyTree) {

  int IDOfStudentToRemove; //Stores the ID of the student the user wants to remove
  cout<<"Enter the ID of the student you wish to remove from the current database"<<endl;
  cin>>IDOfStudentToRemove;
  cin.ignore(); //insures that cin does not skip over input lines when user is asked for input, so that user can actually enter the input

  if (cin.fail()) {

    //cin may fail in cases where user does not enter an integer id, so its error state needs to be cleared so that cin can be used again
    cin.clear();
    cout<<"Invalid Input: You must enter an integer ID for the student you wish to remove from the current database"<<endl;
    return;

  }

  TreeNode<int, Student>* studentToRemove = find(IDOfStudentToRemove);
  if (studentToRemove != NULL) {
    //the student the user wants to remove is in the StudentTable

    //find the advisor of this student to remove this student from their advisee list so that referential integrity is maintained:
    TreeNode<int, Faculty>* advisorOfThisStudent = facultyTree.find(studentToRemove->getValue().getStudentAdvisorID());

    if (advisorOfThisStudent != NULL) {

      //student had an advisor who needs to be notified that they are no longer an advisor for this student:
      advisorOfThisStudent->getValue().advisees->remove(IDOfStudentToRemove);

    }

    //signal to the program that this command successfully changed the database so that the snapshot made prior to the change can be saved for a potential rollback
    commandModifiedTableSuccessfully = true;

    //remove this student from the student table:
    erase(IDOfStudentToRemove);

  }
  else {

    //the student the user wants to remove does not exist in the current database
    cout<<"Sorry, but you entered the ID of a student that does not exist in the current database."<<endl;
    return;

  }

}

//adds a student to the database
void StudentTable::addAStudent(FacultyTable& facultyTree) {

  //all of the data needed to build a Student object
  int IDOfNewStudentToAdd;

  /*

  -I use char here so that I can use cin.get. cin.get is used for these values because the user can enter a space,
  and reguler cin>> stops reading a line though if there is a space.
  I want to allow the user to add a space in between first in last names though, so I went with cin.get() for this
  method.

  -Information for cin.get() from: https://stackoverflow.com/questions/29630513/difference-between-cin-and-cin-get-for-char-array

  */
  char nameOfNewStudentToAdd[256];
  char levelOfNewStudentToAdd[256];
  char majorOfNewStudentToAdd[256];

  double GPAOfNewStudentToAdd;
  int advisorIDOfNewStudentToAdd;

  //ask the user for the ID of the student they want to enter
  cout<<"Enter an integer for the ID of the student you wish to add:"<<endl;
  cin>>IDOfNewStudentToAdd;
  cin.ignore();  //insures that cin does not skip over input lines when user is asked for input, so that user can actually enter the input

  if (cin.fail()) {

    //cin may fail in cases where user does not enter an integer id, so its error state needs to be cleared so that cin can be used again
    cout<<"Invalid Input: you must enter an integer for the student ID"<<endl;
    cin.clear();
    return; //exit the command

  }
  else if (find(IDOfNewStudentToAdd) != NULL) {

    //this ID is already in use by another student in the database:
    cout<<"Sorry, but the ID you entered is already in use by another student in the current database"<<endl;
    return; //exit the command

  }

  //ask for the name of the student the user wants to insert
  cout<<"Enter the name of the new student you wish to add:"<<endl;
  cin.get(nameOfNewStudentToAdd, 256);
  cin.ignore(); //insures that cin does not skip over input lines when user is asked for input, so that user can actually enter the input

  if (cin.fail()) {

    //cin will fail in cases where the user pressed enter without entering any characters, so this error state needs to be cleared if cin is to be used again:
    cout<<"Invalid Input: you failed to put a valid name for the student you wish to add"<<endl;
    cin.clear();
    return; //exit/abort the command

  }

  //ask the user for the level of the student they want to enter:
  cout<<"Enter the level of the new student you wish to add:"<<endl;
  cin.get(levelOfNewStudentToAdd, 256);
  cin.ignore(); //insures that cin does not skip over input lines when user is asked for input, so that user can actually enter the input

  if (cin.fail()) {

    //cin will fail in cases where the user pressed enter without entering any characters, so this error state needs to be cleared if cin is to be used again:
    cout<<"Invalid Input: you failed to put a valid level for the student you wish to add"<<endl;
    cin.clear();
    return;

  }

  //Ask the user for the major of the student they want to insert into the tree
  cout<<"Enter the major of the new student you wish to add:"<<endl;
  cin.get(majorOfNewStudentToAdd, 256);
  cin.ignore(); //insures that cin does not skip over input lines when user is asked for input, so that user can actually enter the input

  if (cin.fail()) {

    //cin will fail in cases where the user pressed enter without entering any characters, so this error state needs to be cleared if cin is to be used again:
    cout<<"Invalid Input: you failed to put a valid major for the student you wish to add"<<endl;
    cin.clear();
    return;

  }

  //ask the user for the gpa of the student they want to insert
  cout<<"Enter the GPA of the new student you wish to add:"<<endl;
  cin>>GPAOfNewStudentToAdd;
  cin.ignore(); //insures that cin does not skip over input lines when user is asked for input, so that user can actually enter the input

  if (cin.fail()) {

    //cin may fail in cases where user does not enter an numerical value for the gpa, so its error state needs to be cleared so that cin can be used again
    cout<<"Invalid Input: you failed to put a valid GPA for the student you wish to add"<<endl;
    cin.clear();
    return; //exit/abort the command

  }

  //ask the user for the advisor ID of the student they wish to add
  cout<<"Enter the advisor ID of the new student you wish to add:"<<endl;
  cin>>advisorIDOfNewStudentToAdd;
  cin.ignore(); //insures that cin does not skip over input lines when user is asked for input, so that user can actually enter the input

  if (cin.fail()) {

    //cin may fail in cases where user does not enter an integer id, so its error state needs to be cleared so that cin can be used again
    cout<<"Invalid Input: you failed to put a valid advisor ID for the student you wish to add"<<endl;
    cin.clear();
    return; //exit/abort the command

  }

  //maintain referential integrity:
  int studentHasAFakeAdvisor = facultyTree.listOfIDSThatExistInTree->find(advisorIDOfNewStudentToAdd);
  if ((/*facultyTree.listOfIDSThatExistInTree->find(advisorIDOfNewStudentToAdd)*/studentHasAFakeAdvisor == -1) && (facultyTree.empty() == false)) {

    //this student has been given a faculty that does not actually exist in the current database, and there are advisors in the faculty tree, assign them to a random faculty member:
    int randomNumber = rand() % facultyTree.listOfIDSThatExistInTree->getSize();
    advisorIDOfNewStudentToAdd = facultyTree.listOfIDSThatExistInTree->findAt(randomNumber);

    //tell the advisor that they have been assigned to this student as an advisor:
    cout<<"STUDENT SET TO ADVISOR WITH ID: "<<advisorIDOfNewStudentToAdd<<endl;
    facultyTree.find(advisorIDOfNewStudentToAdd)->getValue().advisees->addFront(IDOfNewStudentToAdd);

  }
  else if (studentHasAFakeAdvisor == -1) {

    //the faculty table is empty, so there are no advisors to assign this student to, set their advisor ID to -1:
    advisorIDOfNewStudentToAdd = -1;

  }

  Student newStudentToAdd(nameOfNewStudentToAdd, levelOfNewStudentToAdd, majorOfNewStudentToAdd, IDOfNewStudentToAdd, advisorIDOfNewStudentToAdd, GPAOfNewStudentToAdd);
  insert(newStudentToAdd.getPersonID(), newStudentToAdd);
  commandModifiedTableSuccessfully = true; //tell the program that this command modifed the table, so that the snapshot taken prior to these changes can be saved for potential rollback

}

//allows the text read from the file using FileInputManager to be saved into the correct memory slots for the student object, so that it is made correctly:
void StudentTable::readFromFileWithSpecificRules(std::string line) {

  if (currentLineNumber == 1) {

    //this line contains the students id
    studentToAddToTable.setPersonID(stoi(line));

  }
  else if (currentLineNumber == 2) {

    //this line contains the student's name
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

  }

  if (currentLineNumber == 6) {

    /*

    -It only takes 6 lines of text
    to make a student object, so once line 6 is read,
    a student object is made and currentLineNumber is set back to 1
    so that another student object can potentially be made

    */
    currentLineNumber = 1;
    insert(studentToAddToTable.getPersonID(), studentToAddToTable);

  }
  else {

    currentLineNumber++;

  }

}
