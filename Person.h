#ifndef PERSON_H
#define PERSON_H

#include <iostream>

/*

-Contains the generic components for a person in this database,
such as id, name, and their level

*/
class Person {

protected:
  unsigned int personID; //the ID of this person

  std::string name; //the name of this person

  std::string level; //the level of this person

public:
  Person(); //default constructor

  Person(unsigned int personID, std::string name, std::string level); //overloaded constructor

  ~Person(); //destructor

  const unsigned int& getPersonID() const; //returns a reference to the ID of this person

  const std::string& getName() const; //returns a reference to the name of this person

  const std::string& getLevel() const; //returns a reference to the level of this person

  void setPersonID(unsigned int personID); //mutator method for setting the id of this person

  void setName(std::string name); //mutator method for setting the name of this person

  void setLevel(std::string level); //mutator method for setting the level of this person

  const bool operator == (Person otherPerson); //overloaded operator for comparing 2 Person objects

};

#endif
