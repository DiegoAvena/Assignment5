#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"

/*

-Contains the components that make up a student for this database. Extends from
Person to use its name, personID, and level members, since these are shared between
student and faculty objects.

*/
class Student: public Person {

private:

  std::string major; //the major of this student

  unsigned int advisorID; //the ID of the advisor for this student

  double studentGPA; //the gpa of this student

public:
  Student(); //default constructor

  Student(std::string name, std::string level, std::string major, unsigned int studentID, unsigned int advisorID, double studentGPA); //overloaded constructor

  ~Student(); //destructor

  const unsigned int& getStudentAdvisorID() const; //accessor method for getting the student advisor ID
  const double& getStudentGPA() const; //accessor method for getting the student's gpa

  const std::string& getMajor() const; //accessor method for getting the major of the student

  void setAdvisorID(unsigned int advisorID); //mutator method for setting the advisor id
  void setStudentGPA(double studentGPA); //mutator method for setting the student's gpa
  void setMajor(std::string major); //mutator method for setting the student's major

};

#endif
