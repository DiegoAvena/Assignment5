#ifndef PERSON_H
#define PERSON_H

#include <iostream>

class Person {

protected:
  unsigned int personID;

  std::string name;
  std::string level;

public:
  Person();
  Person(unsigned int personID, std::string name, std::string level);

  ~Person();

  const unsigned int& getPersonID() const;

  const std::string& getName() const;
  const std::string& getLevel() const;

  void setPersonID(unsigned int personID);

  void setName(std::string name);
  void setLevel(std::string level);

  const bool operator == (Person otherPerson);

};

#endif
