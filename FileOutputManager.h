#ifndef FILE_OUTPUT_MANAGER_H
#define FILE_OUTPUT_MANAGER_H

#include <fstream>
#include <iostream>
#include "TreeNode.h"
#include "Student.h"
#include "Faculty.h"

template <typename DataType>

class FileOutputManager {

private:
  //std::ofstream fileToWriteTo;

public:
  FileOutputManager() {

  }

  ~FileOutputManager() {

    //delete fileToWriteTo;

  }

  void writeToFile(DataType& objectToWriteToFile, std::string nameOfFileToWriteTo){

    //std::ofstream fileToWriteTo(nameOfFileToWriteTo, std::ios::trunc);
    std::ofstream* fileToWriteTo = new std::ofstream(nameOfFileToWriteTo, std::ios::trunc);
    objectToWriteToFile.writeToFileUsingSpecficRules(fileToWriteTo, objectToWriteToFile.getRoot());
    fileToWriteTo->close();
    delete fileToWriteTo;

  }

};

#endif
