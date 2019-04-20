#include "Faculty.h"

Faculty::Faculty() {

}

Faculty::Faculty(std::string name, std::string level, std::string department, unsigned int facultyID){

  setName(name);
  setLevel(level);
  setDepartment(department);
  setPersonID(facultyID);

}

Faculty::Faculty(std::string name, std::string level, std::string department, unsigned int facultyID, DoubleLinkedList<unsigned int> advisees){

  setName(name);
  setLevel(level);
  setDepartment(department);
  setPersonID(facultyID);
  this->advisees = advisees;

}

const std::string& Faculty::getDepartment() const {

  return department;

}

const DoubleLinkedList<unsigned int>& Faculty::getAdvisees() const {

  return advisees;

}


void Faculty::addAdvisee(unsigned int IDOfAdviseeToAdd) {

  advisees.addFront(IDOfAdviseeToAdd);
}

void Faculty::removeAdvisee(unsigned int IDOfAdviseeToRemove){

  advisees.remove(IDOfAdviseeToRemove);

}

void Faculty::setDepartment(std::string department){

  this->department = department;

}
