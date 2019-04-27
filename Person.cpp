#include "Person.h"

//default constructor
Person::Person() {

}

//overloaded constructor
Person::Person(unsigned int personID, std::string name, std::string level) {

  setPersonID(personID);
  setName(name);
  setLevel(level);

}

//destructor
Person::~Person() {

}

//returns a reference to the ID of this person
const unsigned int& Person::getPersonID() const {

  return personID;

}

//returns a reference to the name of this person
const std::string& Person::getName() const {

  return name;

}

//returns a reference to the level of this person
const std::string& Person::getLevel() const{

  return level;

}

//mutator method for setting the id of this person
void Person::setPersonID(unsigned int personID) {

  this->personID = personID;

}

//mutator method for setting the name of this person
void Person::setName(std::string name){

  this->name = name;

}

//mutator method for setting the level of this person
void Person::setLevel(std::string level) {

  this->level = level;

}

//overloaded operator for comparing 2 Person objects
const bool Person::operator == (Person otherPerson) {

  return personID == otherPerson.getPersonID();

}
