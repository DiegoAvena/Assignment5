#include "Student.h"

 //default constructor
Student::Student() {

}

//overloaded constructor
Student::Student(std::string name, std::string level, std::string major, unsigned int studentID, unsigned int advisorID, double studentGPA) {

  setName(name);
  setLevel(level);
  setMajor(major);
  setPersonID(studentID);
  setAdvisorID(advisorID);
  setStudentGPA(studentGPA);

}

//destructor
Student::~Student() {


}

//accessor method for getting the student advisor ID
const unsigned int& Student::getStudentAdvisorID() const {

  return advisorID;

}

//accessor method for getting the student's gpa
const double& Student::getStudentGPA() const {

  return studentGPA;

}

//accessor method for getting the major of the student
const std::string& Student::getMajor() const {

  return major;

}

//mutator method for setting the advisor id
void Student::setAdvisorID(unsigned int advisorID) {

  this->advisorID = advisorID;

}

//mutator method for setting the student's gpa
void Student::setStudentGPA(double studentGPA) {

  this->studentGPA = studentGPA;

}

//mutator method for setting the student's major
void Student::setMajor(std::string major) {

  this->major = major;

}
