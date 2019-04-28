#include "Faculty.h"
using namespace std;

Faculty::Faculty() {

  advisees = new DoubleLinkedList<unsigned int>();

}

Faculty::Faculty(std::string name, std::string level, std::string department, unsigned int facultyID){

  setName(name);
  setLevel(level);
  setDepartment(department);
  setPersonID(facultyID);
  advisees = new DoubleLinkedList<unsigned int>();

}

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

Faculty::~Faculty() {

  //delete advisees;

}

const std::string& Faculty::getDepartment() const {

  return department;

}

void Faculty::printAdviseeIds() {

  advisees->printList();

}

void Faculty::addAdvisee(unsigned int IDOfAdviseeToAdd) {

  advisees->addFront(IDOfAdviseeToAdd);
}

void Faculty::removeAdvisee(unsigned int IDOfAdviseeToRemove) {

  advisees->remove(IDOfAdviseeToRemove);

}

void Faculty::setDepartment(std::string department){

  this->department = department;

}
