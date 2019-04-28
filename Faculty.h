#ifndef FACULTY_H
#define FACULTY_H

#include "Person.h"
#include "DoubleLinkedList.h"

/*

-Extends from the generic person class to build upon it by
defining components more specific to a faculty person, such as their department
and advisees

*/
class Faculty: public Person{

private:
  std::string department; //the department this faculty member is in

public:
  Faculty(); //default constructor

  Faculty(std::string name, std::string level, std::string department, unsigned int facultyID); //overloaded constructor

  Faculty(std::string name, std::string level, std::string department, unsigned int facultyID, int* arrayOfAdvisees, int numberOfAdvisees); //overloaded constructor

  ~Faculty(); //destructor

  DoubleLinkedList<unsigned int>* advisees; //the list of advisees this faculty member has

  const std::string& getDepartment() const; //accessor method for getting the department this faculty member is in

  void addAdvisee(unsigned int IDOfAdviseeToAdd); //adds an advisee to this advisors advisee list

  void removeAdvisee(unsigned int IDOfAdviseeToRemove); //removes an advisee from this advisors list of advisees

  void setDepartment(std::string department); //mutator method for setting the department of the faculty member

};

#endif
