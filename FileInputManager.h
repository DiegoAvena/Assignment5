#ifndef FILE_INPUT_MANAGER_H
#define FILE_INPUT_MANAGER_H

#include <fstream>
#include <iostream>
//#include "DataBaseManager.h"
//#include "FacultyTable.h"

template <typename dataType>

class FileInputManager {

protected:
  /*void readFromFileWithSpecificRules(std::string line, dataType& objectToBuildUsingTheTextFile) {

    std::cout<<"nothing being added to tree!"<<std::cout;


  }*/

public:

  //virtual void readFromFileWithSpecificRules(std::string line);

  FileInputManager() {

  }

  ~FileInputManager() {

  }

  void readFile(std::string fileName, dataType& objectToBuildUsingTheTextFile) {

    std::ifstream fileToReadFrom(fileName);
    //fileToReadFrom.exceptions(std::ifstream::failbit|std::ifstream::badbit);

    if (fileToReadFrom.is_open()) {

      std::string line;
      std::cout<<"FILE WITH NAME: "<<fileName<<"OPENED..."<<std::endl;

      while (getline(fileToReadFrom, line)) {

        //getline(fileToReadFrom, line);
        std::cout<<line<<std::endl;
        objectToBuildUsingTheTextFile.readFromFileWithSpecificRules(line);

      }

      /*string line;
      unsigned int currentLineNumber = 1;
      unsigned int numberOfFirstLineForDataSet = 1;

      if (fileName == "facultyTable.txt") {

        unsigned int lineWhereNumberOfAdviseesWas;
        unsigned int numberOfAdvisees;

        while (getLine(fileToReadFrom, line)) {

          if ((currentLineNumber - numberOfFirstLineForDataSet) < 4) {



          }
          else if ((currentLineNumber - numberOfFirstLineForDataSet) == 4) {

            numberOfAdvisees = stoi(line);

          }
          else if ((currentLineNumber - lineWhereNumberOfAdviseesWas) <= numberOfAdvisees) {



          }

          if () {




          }

        }

      }
      else {

        while (getLine(fileToReadFrom, line)) {



        }

      }*/

    }
    else {

      if (fileName == "facultyTable.txt") {

        std::cout<<"Sorry, but there is no facultyTable file to read from, initializing to an empty table instead."<<std::endl;

      }
      else {

        std::cout<<"Sorry, but there is no studentTable file to read from, initializing to an empty table instead."<<std::endl;

      }

    }


  }

};

#endif
