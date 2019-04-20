#include "Student.h"

Student::Student() {

}

Student::Student(std::string name, std::string level, std::string major, unsigned int studentID, unsigned int advisorID, double studentGPA) {

  setName(name);
  setLevel(level);
  setMajor(major);
  setPersonID(studentID);
  setAdvisorID(advisorID);
  setStudentGPA(studentGPA);

}

Student::~Student() {


}

const unsigned int& Student::getStudentAdvisorID() const {

  return advisorID;

}

const double& Student::getStudentGPA() const {

  return studentGPA;

}

const std::string& Student::getName() const {

  return name;

}

const std::string& Student::getLevel() const {

  return level;

}

const std::string& Student::getMajor() const {

  return major;

}

void Student::setAdvisorID(unsigned int advisorID) {

  this->advisorID = advisorID;

}

void Student::setStudentGPA(double studentGPA) {

  this->studentGPA = studentGPA;

}

void Student::setMajor(std::string major) {

  this->major = major;

}
