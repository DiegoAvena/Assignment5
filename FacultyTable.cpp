#include "FacultyTable.h"

using namespace std;

//Default constructor
FacultyTable::FacultyTable():BinarySearchTree(){

  //listOfAdviseeListsToDeleteLater = new DoubleLinkedList< DoubleLinkedList<unsigned int>* >();
  currentLineNumber = 1;
  commandModifiedTableSuccessfully = false;
  listOfIDSThatExistInTree = new DoubleLinkedList<int>();

}

//traverses the tree to copy it, used by the copy constructor
void FacultyTable::traverseTreeToCopyIt(TreeNode<int, Faculty>* node) {

  if (node != NULL) {

    traverseTreeToCopyIt(node->left);

    //copy this faculty node
    Faculty* copyOfFacultyNode = new Faculty(node->getValue().getName(), node->getValue().getLevel(), node->getValue().getDepartment(), node->getValue().getPersonID());

    //fill this faculty copy node with the correct advisees
    for (int i = 0; i < node->getValue().advisees->getSize(); i++) {

      copyOfFacultyNode->advisees->addFront(node->getValue().advisees->findAt(i));

    }

    insert(copyOfFacultyNode->getPersonID(), *copyOfFacultyNode);

    delete copyOfFacultyNode; //deallocate memory that was allocated for the copy of the current node

    traverseTreeToCopyIt(node->right);

  }

}

//copy constructor
FacultyTable::FacultyTable(const FacultyTable& tableToCopy) {

  commandModifiedTableSuccessfully = false;
  listOfIDSThatExistInTree = new DoubleLinkedList<int>();
  //listOfAdviseeListsToDeleteLater = new DoubleLinkedList< DoubleLinkedList< unsigned int>* >();

  for (int i = 0; i < tableToCopy.listOfIDSThatExistInTree->getSize(); i++) {

    listOfIDSThatExistInTree->addFront(tableToCopy.listOfIDSThatExistInTree->findAt(i));

  }

  traverseTreeToCopyIt(tableToCopy.getRoot());

}

//accessor method for the flag that signals if a command modified this faculty table
bool FacultyTable::getCommandModifiedTableSuccessfully() {

  return commandModifiedTableSuccessfully;

}

//mutator method for setting commandModifiedTableSuccessfully flag
void FacultyTable::setCommandModifiedTableSuccessfully(bool commandModifiedTableSuccessfully){

  this->commandModifiedTableSuccessfully = commandModifiedTableSuccessfully;

}

//the method that contains the more specific rules needed by the file fileOutputer to serialize this faculty table
void FacultyTable::writeToFileUsingSpecficRules(ofstream* fileToWriteTo, TreeNode<int, Faculty>* node) {

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

//overloaded constructor
FacultyTable::FacultyTable(int rootKey, Faculty rootValue):BinarySearchTree(rootKey, rootValue){}

//destructor
FacultyTable::~FacultyTable(){

  delete listOfIDSThatExistInTree;

  /*cout<<"DELETING LIST OF ADVISEES FOR THE FACULTY TO ADD TO TABLE OBJECT"<<endl;
  int sizeOfListOfAdviseeLists = listOfAdviseeListsToDeleteLater->getSize();
  for (int i = 0; i < sizeOfListOfAdviseeLists; i++) {

    delete listOfAdviseeListsToDeleteLater->findAt(i);
    cout<<"YIPPYAP"<<endl;
    //cout<<listOfAdviseeListsToDeleteLater->findAt(i)<<endl;

  }*/

  //delete listOfAdviseeListsToDeleteLater;
  //cout<<"DONE..."<<endl;

  deleteListOfAdviseesForEachFaculty(root);

}

//deletes the list of advisees that was dynamically allocated for every node in the faculty tree/table
void FacultyTable::deleteListOfAdviseesForEachFaculty(TreeNode<int, Faculty>* node) {

  if (node != NULL) {

    deleteListOfAdviseesForEachFaculty(node->left);
    delete node->getValue().advisees;
    deleteListOfAdviseesForEachFaculty(node->right);

  }

}

//adds a faculty member into the faculty table
void FacultyTable::AddAFacultyMember(BinarySearchTree<int, Student>& studentTreeReference) {

  //for info on cin.get(), I used: http://www.cplusplus.com/reference/istream/istream/get/

  //all of the data needed to make a faculty object
  int IDOfNewFaculty;

  /*

  -I use char here so that I can use cin.get. cin.get is used for these values because the user can enter a space,
  and reguler cin>> stops reading a line though if there is a space.
  I want to allow the user to add a spaces though for these fields, so I went with cin.get() for this
  method.

  -Information for cin.get() from: https://stackoverflow.com/questions/29630513/difference-between-cin-and-cin-get-for-char-array

  */
  char nameOfNewFaculty[256];
  char levelOfNewFaculty[256];
  char departmentOfNewFaculty[256];

  int IDOfNewFacultyAdvisee;

  //Ask the user for the id of the new faculty member they want to add:
  cout<<"Enter the ID of the new faculty member you wish to add:"<<endl;
  cin>>IDOfNewFaculty;
  cin.ignore(); //insures that cin does not skip over input lines when user is asked for input, so that user can actually enter the input

  if (cin.fail()) {

    //cin may fail in cases where user does not enter an integer id, so its error state needs to be cleared so that cin can be used again
    cin.clear();
    cout<<"Invalid Input: you must enter an integer ID for the faculty you are trying to add."<<endl;
    return;

  }

  if (find(IDOfNewFaculty) != NULL) {

    //there is a faculty member with this exact ID already in the tree: This faculty cannot be entered with this ID
    cout<<"Sorry, but the ID you gave is already in use by another faculty in the current database."<<endl;
    return;

  }

  //Ask the user for the name of the new faculty member they wish to add into the table
  cout<<"Enter the name of the new faculty member you wish to add: "<<endl;
  cin.get(nameOfNewFaculty, 256);
  cin.ignore(); //insures that cin does not skip over input lines when user is asked for input, so that user can actually enter the input

  if (cin.fail()) {

    //cin will fail if the user presses enter without entering anything, so the error state of cin will need to be cleared for it to be used again
    cout<<"Invalid Input: you did not enter a valid name for the new faculty you wish to add."<<endl;
    cin.clear();
    return;

  }

  //Ask the user for the level of the new faculty member they wish to add into the table
  cout<<"Enter the level of the new faculty member you wish to add: "<<endl;
  cin.get(levelOfNewFaculty, 256);
  cin.ignore(); //insures that cin does not skip over input lines when user is asked for input, so that user can actually enter the input

  if (cin.fail()) {

    //cin will fail if the user presses enter without entering anything, so the error state of cin will need to be cleared for it to be used again
    cout<<"Invalid Input: you did not enter a valid level for the new faculty you wish to add."<<endl;
    cin.clear();
    return;

  }

  //Ask the user for the department of the new faculty member they wish to add
  cout<<"Enter the department of the new faculty member you wish to add: "<<endl;
  cin.get(departmentOfNewFaculty, 256);
  cin.ignore(); //insures that cin does not skip over input lines when user is asked for input, so that user can actually enter the input

  if (cin.fail()) {

    //cin will fail if the user presses enter without entering anything, so the error state of cin will need to be cleared for it to be used again
    cout<<"Invalid Input: you did not enter a valid department for the new faculty you wish to add."<<endl;
    cin.clear();
    return;

  }

  //All the information needed to create a faculty object is ready:
  Faculty* newFacultyToAdd = new Faculty(nameOfNewFaculty, levelOfNewFaculty, departmentOfNewFaculty, IDOfNewFaculty);

  //prompt the user if they want to assign this new faculty member advisees and assign those advisees to this faculty member
  while (true) {

    cout<<"Enter a numerical ID for the Advisee you wish to add to this new faculty member, or you can enter -1 to stop and insert the faculty into the database."<<endl;
    cin>>IDOfNewFacultyAdvisee;
    cin.ignore();

    if (cin.fail()) {

      //cin may fail in cases where user does not enter an integer id, so its error state needs to be cleared so that cin can be used again
      cin.clear();
      cout<<"Invalid input: sorry, but the ID you enter must be an integer"<<endl;

      delete newFacultyToAdd;
      break;

    }
    else if (IDOfNewFacultyAdvisee < 0) {
      //user is done adding in advisees for this faculty member:

      insert(newFacultyToAdd->getPersonID(), *newFacultyToAdd);
      listOfIDSThatExistInTree->addFront(newFacultyToAdd->getPersonID());
      commandModifiedTableSuccessfully = true;

      delete newFacultyToAdd;
      cout<<"Faculty member added!"<<endl;
      break;

    }
    else {

      TreeNode<int, Student>* studentNode = studentTreeReference.find(IDOfNewFacultyAdvisee);

      if (studentNode != NULL) {

        if (newFacultyToAdd->advisees->find(studentNode->getValue().getPersonID()) == -1) {

          //this student is not in the advisors advisee list yet, add them in:
          newFacultyToAdd->addAdvisee(studentNode->getValue().getPersonID());
          cout<<"Student added to advisee list."<<endl;

        }
        else {

          cout<<"Student is already an advisee for this faculty advisor."<<endl;

        }

        if (studentNode->getValue().getStudentAdvisorID() != newFacultyToAdd->getPersonID()) {

          //remove this advisee from their previous advisor since a student should not have 2 advisors
          TreeNode<int, Faculty>* facultyToRemoveAdviseeFrom = find(studentNode->getValue().getStudentAdvisorID());

          if (facultyToRemoveAdviseeFrom != NULL) {

            facultyToRemoveAdviseeFrom->getValue().removeAdvisee(studentNode->getKey());

          }

          //reassign this student to this new faculty member:
          studentNode->getValue().setAdvisorID(newFacultyToAdd->getPersonID());

        }

      }
      else {

        //the user is trying to assign a student that does not exist in the database to this faculty member:
        cout<<"Sorry, that ID you entered for the advisee is an ID for a student that does not exist in the current database"<<endl;

      }

    }

  }

}

//prints the information for a specific faculty member
void FacultyTable::printASpecificFacultyMember(BinarySearchTree<int, Student>& tree) {

  //ask the user for the ID of the faculty member they wish to deal with:
  cout<<"Enter the ID of the faculty member you wish to see the information of:"<<endl;
  int userResponse;
  cin>>userResponse;
  cin.ignore(); //insures that cin does not skip over input lines when user is asked for input, so that user can actually enter the input

  if (cin.fail()) {

    //cin may fail in cases where user does not enter an integer id, so its error state needs to be cleared so that cin can be used again
    cin.clear();
    cout<<"Invalid input: You must enter an integer ID."<<endl;

  }
  else {

    TreeNode<int, Faculty>* facultyNodeToPrintInformationOf = find(userResponse);

    if (facultyNodeToPrintInformationOf == NULL) {

      //This faculty member does not exist in the current database:
      cout<<"Sorry, but the faculty with the ID you gave does not exist in the current database"<<endl;

    }
    else {

      //the faculty member exists in the current database:

      cout<<"------------------------------------------"<<endl;
      cout<<"Faculty ID: "<<facultyNodeToPrintInformationOf->getKey()<<endl;
      cout<<"Faculty Name: "<<facultyNodeToPrintInformationOf->getValue().getName()<<endl;
      cout<<"Faculty Level: "<<facultyNodeToPrintInformationOf->getValue().getLevel()<<endl;
      cout<<"Faculty Department: "<<facultyNodeToPrintInformationOf->getValue().getDepartment()<<endl;
      cout<<"Faculty Advisee Info: "<<endl;

      if (facultyNodeToPrintInformationOf->getValue().advisees->getSize() == 0) {

        cout<<"   N/A"<<endl;

      }
      else {

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

}

//prints all of the faculty members in the current database in ascending ID order
void FacultyTable::printFaculty(TreeNode<int, Faculty>* node, BinarySearchTree<int, Student>& tree) {

  //inorder traversal used to print faculty in order of ascending ID
  if (node != NULL) {

    printFaculty(node->left, tree);
    cout<<"------------------------------------------"<<endl;
    cout<<"Faculty ID: "<<node->getKey()<<endl;
    cout<<"Faculty Name: "<<node->getValue().getName()<<endl;
    cout<<"Faculty Level: "<<node->getValue().getLevel()<<endl;
    cout<<"Faculty Department: "<<node->getValue().getDepartment()<<endl;
    cout<<"Faculty Advisee Info: "<<endl;

    if (node->getValue().advisees->getSize() == 0) {

      //this faculty member has no advisees:
      cout<<" N/A"<<endl;

    }
    else {

      //this faculty member has advisees:
      for (int i = 0; i < node->getValue().advisees->getSize(); i++) {

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

    }

    printFaculty(node->right, tree);

  }

}

//prints all advisee info for all advisees for a specific faculty member
void FacultyTable::printAdviseeInfoForSpecificFacultyMember(BinarySearchTree<int, Student>& tree) {

  //ask the user for the ID of the faculty member they wish to deal with:
  cout<<"Enter the ID of the faculty you wish to see the Advisee information for."<<endl;
  int userResponse;
  cin>>userResponse;
  cin.ignore();

  if (cin.fail()) {

    //cin may fail in cases where user does not enter an integer id, so its error state needs to be cleared so that cin can be used again
    cin.clear();
    cout<<"Invalid Input: You must enter an integer for the ID"<<endl;

  }
  else {

    TreeNode<int, Faculty>* facultyNode = find(userResponse);

    if (facultyNode != NULL) {
      //the faculty node the user wants to deal with exists in the current database:

      TreeNode<int, Student>* adviseeNode;

      if (facultyNode->getValue().advisees->getSize() == 0) {

        //faculty member has no advisees:
        cout<<"   N/A"<<endl;

      }
      else {

        //faculty member has advisees:

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

    }
    else {

      //the faculty member the user wants to deal with does not exist in the current database:
      cout<<"Sorry, but the faculty with the ID you entered does not exist in the current database"<<endl;

    }

  }


}

//initializes the referential integrity for this faculty table/tree right when the program starts
void FacultyTable::initializeReferentialIntegrityOfTable(TreeNode<int, Faculty>* node, BinarySearchTree<int, Student>& treeToBaseReferenceOffOf) {

  if (node != NULL) {

    initializeReferentialIntegrityOfTable(node->left, treeToBaseReferenceOffOf);

    DoubleLinkedList<int> listOfAdviseesToRemove;
    int numberOfAdviseesToRemove = 0;

    for (int i = 0; i < node->getValue().advisees->getSize(); i++) {

      //the advisee set for this Faculty member:
      TreeNode<int, Student>* studentNode = treeToBaseReferenceOffOf.find(node->getValue().advisees->findAt(i));

      if (studentNode == NULL) {

        //the faculty has an advisee that does not exist in the student table:
        listOfAdviseesToRemove.addFront(node->getValue().advisees->findAt(i));

      }
      else if (studentNode->getValue().getStudentAdvisorID() != node->getValue().getPersonID()) {

        //This student has a different faculty assigned to them already
        listOfAdviseesToRemove.addFront(node->getValue().advisees->findAt(i));

      }

    }

    //remove the advisees that need to be removed for this faculty node:
    for (int i = 0; i < listOfAdviseesToRemove.getSize(); i++) {

      node->getValue().advisees->remove(listOfAdviseesToRemove.findAt(i));

    }

    initializeReferentialIntegrityOfTable(node->right, treeToBaseReferenceOffOf);

  }

}

//removes an advisee for a faculty member:
void FacultyTable::removeAnAdvisee(BinarySearchTree<int, Student>& studentTreeReference) {

  int IDOfFacultyToRemoveAdviseeFor;
  int IDOfAdviseeToRemove;

  //get the ID of the faculty the user wishes to remove an advisee for:
  cout<<"Enter the ID for the faculty you wish to remove an advisee from"<<endl;

  cin>>IDOfFacultyToRemoveAdviseeFor;
  cin.ignore();

  if (cin.fail()) {

    //cin will fail if the user does not enter an integer, so the error state needs to be cleared in order for cin to be used again
    cin.clear();
    cout<<"Invalid Input: You must enter an integer ID for the Faculty you wish to remove an advisee for"<<endl;
    return;

  }

  TreeNode<int, Faculty>* facultyToRemoveAdviseeFor = find(IDOfFacultyToRemoveAdviseeFor);
  if (facultyToRemoveAdviseeFor == NULL) {

    //the faculty member the user wants to deal with does not exist in the current database
    cout<<"Sorry, but the ID you gave is the ID of a faculty member that does not exist in the current database."<<endl;
    return;

  }

  //get the ID of the advisee the the user wishes to remove:
  cout<<"Enter the ID for the advisee you wish to remove from this faculty:"<<endl;
  cin>>IDOfAdviseeToRemove;
  cin.ignore();

  if (cin.fail()) {

    //cin will fail if the user does not enter an integer, so the error state needs to be cleared in order for cin to be used again
    cin.clear();
    cout<<"Invalid Input: You need to enter an integer ID for the advisee you wish to remove from this faculty member"<<endl;
    return;

  }

  TreeNode<int, Student>* adviseeToRemove = studentTreeReference.find(IDOfAdviseeToRemove);
  if (adviseeToRemove == NULL) {

    //the advisee the user wants to remove from this advisor does not exist in the current database
    cout<<"Sorry, but the ID you inserted is the ID of a student that does not exist in the current database"<<endl;
    return;

  }

  //check that the advisee the user wishes to remove from this faculty member is actually assigned to this faculty member:
  if (facultyToRemoveAdviseeFor->getValue().advisees->find(IDOfAdviseeToRemove) == -1) {

    //this advisee is not assigned to this faculty member:
    cout<<"Sorry, but the advisee you wish to remove from this faculty member is not assigned to this faculty member."<<endl;
    return;

  }

  //Remove this advisee from this faculty member:
  facultyToRemoveAdviseeFor->getValue().advisees->remove(IDOfAdviseeToRemove);

  //automatically assign this advisee to another advisor:
  while (true) {

    /*

    -This part of this method will not even be reached if the faculty table
    is empty because then the ID the user gave for the faculty member would have resulted in
    an faculty member that does not exist in the current table, causing this command to abort, so there
    is no need to check if listOfIDSThatExistInTree has a size equal to 0.

    */
    int randomNumber = rand() % listOfIDSThatExistInTree->getSize();

    if (listOfIDSThatExistInTree->getSize() == 1) {

      /*

      -There is only 1 faculty member in the tree, and this is the member for which
      this advisee is be removed for, so there will be no other advisor to reassign this advisee to besides this one,
      but the user just said to remove this advisee for this advisor so he or she cannot be reassigned to this faculty member; thus,
      in this case there is no one to reassign this student to and they will be advisorless for now until assigned by a user.

      */
      adviseeToRemove->getValue().setAdvisorID(-1);
      break;

    }
    else if (listOfIDSThatExistInTree->findAt(randomNumber) != IDOfFacultyToRemoveAdviseeFor) {

      //this is an advisor that is not the advisor the student was just removed from, assign them to this advisor:
      adviseeToRemove->getValue().setAdvisorID(listOfIDSThatExistInTree->findAt(randomNumber));

      //tell the new advisor that they have been assigned to this student as an advisor:
      find(adviseeToRemove->getValue().getStudentAdvisorID())->getValue().advisees->addFront(IDOfAdviseeToRemove);

      break;

    }

  }

  commandModifiedTableSuccessfully = true; //signal to the program that this command modified the database so that a snapshot of the database prior to these changes can be saved for potential rollback
  cout<<"Advisee removed and automatically reassigned to advisor with ID "<<adviseeToRemove->getValue().getStudentAdvisorID()<<endl;

}

//sets up the faculty table at the start of the program by reading through the studentTable.txt file
void FacultyTable::setUpTable(FacultyTable& objectToBuildUsingTheTextFile) {

  //Faculty table inherited from FileInputManager in order to access this method:
  readFile("facultyTable.txt", objectToBuildUsingTheTextFile);

}

//removes a faculty member from the database
void FacultyTable::removeAFacultyMember(BinarySearchTree<int, Student>& studentTreeReference) {

  int IDOfFacultyToRemove;
  cout<<"Enter the ID of the faculty member you wish to remove from the database"<<endl;
  cin>>IDOfFacultyToRemove;
  cin.ignore();

  if (cin.fail()) {

    //cin will fail if the user does not enter an integer
    cin.clear();
    cout<<"Invalid Input: You must enter an integer for the ID of the faculty you wish to remove"<<endl;
    return;

  }
  else {

    //get the faculty member the user wants to remove
    TreeNode<int, Faculty>* facultyNodeToRemove = find(IDOfFacultyToRemove);

    if (facultyNodeToRemove != NULL) {

      //remove the ID of the faculty that is about to be deleted from the list of faculty IDs currently in the tree
      listOfIDSThatExistInTree->remove(IDOfFacultyToRemove);

      //Reassign each of the advisees for this faculty member to a new advisor
      if (listOfIDSThatExistInTree->empty() == false) {

        //there are still faculties that can be assigned to the advisees of this faculty
        for (int i = 0; i < facultyNodeToRemove->getValue().advisees->getSize(); i++) {

          int IDOfAdviseeToReassign = facultyNodeToRemove->getValue().advisees->findAt(i);

          int randomNumber = rand() % listOfIDSThatExistInTree->getSize(); //randomly reassign:

          TreeNode<int, Student>* advisee = studentTreeReference.find(IDOfAdviseeToReassign);
          advisee->getValue().setAdvisorID(listOfIDSThatExistInTree->findAt(randomNumber));

          //tell the advisor being assigned to this new advisee that they have been assigned to this new advisee:
          int IDOfAdvisorToAssignAdviseeTo = listOfIDSThatExistInTree->findAt(randomNumber);

          find(IDOfAdvisorToAssignAdviseeTo)->getValue().addAdvisee(IDOfAdviseeToReassign);

        }

      }
      else {

        //Tell student advisee that there is no advisors left for them to be assigned to:
        for (int i = 0; i < facultyNodeToRemove->getValue().advisees->getSize(); i++) {

          int IDOfAdviseeToReassign = facultyNodeToRemove->getValue().advisees->findAt(i);

          studentTreeReference.find(IDOfAdviseeToReassign)->getValue().setAdvisorID(-1);

        }

      }

      //erase the faculty from the tree
      cout<<"Faculty member removed from database."<<endl;

      delete facultyNodeToRemove->getValue().advisees; //makes sure the memory allocated by the Faculty class for the advisee list is freed
      erase(IDOfFacultyToRemove);

      commandModifiedTableSuccessfully = true; //signal to program that database was changed so that a snapshot of the database prior to the change can be saved for potential rollback

    }
    else {

      //the user wants to remove a faculty member that does not exist in the current database
      cout<<"Sorry, but the ID of the faculty member you wish to remove does not exist in the currrent database"<<endl;
      return;

    }

  }

}

//reads from the file opened by FileInputManager and correctly makes the faculty objects following the rules set for the facultyTable.txt file
void FacultyTable::readFromFileWithSpecificRules(string line) {

  if (currentLineNumber == 1) {

    //this is the faculty's id
    facultyToAddToTable = new Faculty();
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
    numberOfAdvisees = stoi(line);

  }
  else if ((currentLineNumber - 5) <= numberOfAdvisees) {

    //this line has the id of a advisee
    facultyToAddToTable->addAdvisee(stoi(line));

  }

  if (((currentLineNumber - 5) == numberOfAdvisees)) {

    //we were on the last line representing data for this faculty, the object is now ready to be added into the tree, and everything should be reset for next faculty:
    currentLineNumber = 1;
    numberOfAdvisees = 0;

    listOfIDSThatExistInTree->addFront(facultyToAddToTable->getPersonID());
    insert(facultyToAddToTable->getPersonID(), *facultyToAddToTable);

    //listOfAdviseeListsToDeleteLater->addFront(facultyToAddToTable->advisees);

    /*

    -no need to delete the list of advisees that was attached to this faculty object because doing so
    causes a seg fault later when these lists are deleted for the copy of
    this faculty object that was placed into the table, so the faculty copy added into the table
    still points at this same advisee list so it is deleted by the method deleteListOfAdviseesForEachFaculty. This means there
    will be no memory leak.

    */

    delete facultyToAddToTable;

  }
  else {

    currentLineNumber++;

  }

}
