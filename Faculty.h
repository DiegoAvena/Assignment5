#ifndef FACULTY_H
#define FACULTY_H

#include "Person.h"
#include "DoubleLinkedList.h"

class Faculty: public Person{

private:
  std::string department;
  DoubleLinkedList<unsigned int> advisees;

public:
  //  Student(std::string name, std::string level, std::string major, unsigned int studentID, unsigned int advisorID, double studentGPA);
  Faculty();
  Faculty(std::string name, std::string level, std::string department, unsigned int facultyID);
  Faculty(std::string name, std::string level, std::string department, unsigned int facultyID, DoubleLinkedList<unsigned int> advisees);

  const std::string& getDepartment() const;
  //const int getAdviseeWithID(unsigned int adviseeID);

  void addAdvisee(unsigned int IDOfAdviseeToAdd);
  void removeAdvisee(unsigned int IDOfAdviseeToRemove);

  const DoubleLinkedList<unsigned int>& getAdvisees() const;

  void setDepartment(std::string department);

};

#endif
