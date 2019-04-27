#include <time.h>
#include "DataBaseManager.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

  srand(time(NULL)); //seeds the random number generator to insure that each time the program is executed, different values are produced: http://www.math.uaa.alaska.edu/~afkjm/csce211/fall2018/handouts/RandomFunctions.pdf

  DataBaseManager dataBaseManager;
  dataBaseManager.presentMenuToUser(); //this launches the program/database  

  return 0;
}
