#include "Person.h"

Person::Person() {

}

Person::Person(unsigned int personID, std::string name, std::string level) {

  setPersonID(personID);
  setName(name);
  setLevel(level);

}

Person::~Person() {

}

const unsigned int& Person::getPersonID() const {

  return personID;

}

const std::string& Person::getName() const {

  return name;

}

const std::string& Person::getLevel() const{

  return level;

}

void Person::setPersonID(unsigned int personID) {

  this->personID = personID;

}

void Person::setName(std::string name){

  this->name = name;

}

void Person::setLevel(std::string level) {

  this->level = level;

}

const bool Person::operator == (Person otherPerson) {

  return personID == otherPerson.getPersonID();

}
