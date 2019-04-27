#ifndef FILE_OUTPUT_MANAGER_H
#define FILE_OUTPUT_MANAGER_H

#include <fstream>
#include <iostream>
#include "TreeNode.h"
#include "Student.h"
#include "Faculty.h"

template <typename DataType>

/*

-Allows for the writing to a file, using a method called writeToFileUsingSpecficRules() that must be
defined in the class using this class in order to follow more specific rules for how the data should be written

*/
class FileOutputManager {

public:

  //default constructor
  FileOutputManager() {

  }

  //destructor
  ~FileOutputManager() {

  }

  //writes to a file of the specified name, using the writeToFileUsingSpecficRules() defined in the class using this class to follow more specific rules
  void writeToFile(DataType& objectToWriteToFile, std::string nameOfFileToWriteTo){

    std::ofstream* fileToWriteTo = new std::ofstream(nameOfFileToWriteTo, std::ios::trunc);
    objectToWriteToFile.writeToFileUsingSpecficRules(fileToWriteTo, objectToWriteToFile.getRoot());
    fileToWriteTo->close();
    delete fileToWriteTo; //deallocate the memory allocated for fileToWriteTo

  }

};

#endif
