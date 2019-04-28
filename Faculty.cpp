#include "Faculty.h"
using namespace std;

//default constructor
Faculty::Faculty() {

  advisees = new DoubleLinkedList<unsigned int>();

}

//overloaded constructor
Faculty::Faculty(std::string name, std::string level, std::string department, unsigned int facultyID){

  setName(name);
  setLevel(level);
  setDepartment(department);
  setPersonID(facultyID);
  advisees = new DoubleLinkedList<unsigned int>();

}

//overloaded constructor
Faculty::Faculty(std::string name, std::string level, std::string department, unsigned int facultyID, int* arrayOfAdvisees, int numberOfAdvisees){

  setName(name);
  setLevel(level);
  setDepartment(department);
  setPersonID(facultyID);

  advisees = new DoubleLinkedList<unsigned int>();
  for (int i  = 0; i < numberOfAdvisees; i++) {

    cout<<"Adding "<<arrayOfAdvisees[i]<<" to list"<<endl;
    advisees->addFront(arrayOfAdvisees[i]);

  }

}

//destructor
Faculty::~Faculty() {

  /*

  -The memory allocated for the list of advisees here is
  freed by the classes that make objects of this class, since deleting
  this here causes a pointer being freed was not allocated
  error to be thrown.

  */

}

//accessor method for getting the department this faculty member is in
const std::string& Faculty::getDepartment() const {

  return department;

}

//adds an advisee to this advisors advisee list
void Faculty::addAdvisee(unsigned int IDOfAdviseeToAdd) {

  advisees->addFront(IDOfAdviseeToAdd);
}

//removes an advisee from this advisors list of advisees
void Faculty::removeAdvisee(unsigned int IDOfAdviseeToRemove) {

  advisees->remove(IDOfAdviseeToRemove);

}

//mutator method for setting the department of the faculty member
void Faculty::setDepartment(std::string department){

  this->department = department;

}
