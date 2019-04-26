#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"

class Student: public Person {

private:

  std::string major;

  unsigned int advisorID;

  double studentGPA;

  bool studentHasBeenAssignedToAnAdviseeAlready;

public:
  Student();
  Student(std::string name, std::string level, std::string major, unsigned int studentID, unsigned int advisorID, double studentGPA);
  ~Student();

  const unsigned int& getStudentAdvisorID() const;
  const double& getStudentGPA() const;

  const std::string& getName() const;
  const std::string& getLevel() const;
  const std::string& getMajor() const;

  bool getStudentHasBeenAssignedToAnAdviseeAlready();
  void setStudentHasBeenAssignedToAnAdviseeAlready(bool studentHasBeenAssignedToAnAdviseeAlready);

  void setAdvisorID(unsigned int advisorID);
  void setStudentGPA(double studentGPA);
  void setMajor(std::string major);

};

#endif
