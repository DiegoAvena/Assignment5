#include <iostream>
//#include "Student.h"
//#include "Faculty.h"
#include "FacultyTable.h"
#include "StudentTable.h"

using namespace std;

int main(int argc, char const *argv[]) {
  /*
  Student studentA("Diego Avena", "Sophmore", "CPSC", 2299333, 1022111, 3.8);
  Student studentB("Micho urizo", "Sophmore", "CPSC", 2299606, 1022111, 3.9);

  cout<<"Student A profile"<<endl;
  cout<<"Name: "<<studentA.getName()<<endl;
  cout<<"Level: "<<studentA.getLevel()<<endl;
  cout<<"Major: "<<studentA.getMajor()<<endl;
  cout<<"ID: "<<studentA.getPersonID()<<endl;
  cout<<"Advisor's ID: "<<studentA.getStudentAdvisorID()<<endl;
  cout<<"GPA"<<studentA.getStudentGPA()<<endl;
  cout<<endl;

  cout<<"Student B profile"<<endl;
  cout<<"Name: "<<studentB.getName()<<endl;
  cout<<"Level: "<<studentB.getLevel()<<endl;
  cout<<"Major: "<<studentB.getMajor()<<endl;
  cout<<"ID: "<<studentB.getPersonID()<<endl;
  cout<<"Advisor's ID: "<<studentB.getStudentAdvisorID()<<endl;
  cout<<"GPA"<<studentB.getStudentGPA()<<endl;
  cout<<endl;

  if (studentA == studentB) {

    cout<<"Student A is the same student as student B."<<endl;

  }
  else {

    cout<<"Student A is not the same student as student B"<<endl;

  }

  Faculty facultyA("Dr. W", "lecturer", "Department of CPSC", 11002999);
  facultyA.addAdvisee(studentA.getPersonID());
  facultyA.addAdvisee(studentB.getPersonID());

  cout<<"faculty A profile"<<endl;
  cout<<"Name: "<<facultyA.getName()<<endl;
  cout<<"Level: "<<facultyA.getLevel()<<endl;
  cout<<"Department: "<<facultyA.getDepartment()<<endl;
  cout<<"ID: "<<facultyA.getPersonID()<<endl;

  cout<<"Faculty has the following advisees: "<<endl;
  for (int i = 0; i < facultyA.getAdvisees().getSize(); i++) {

    cout<<facultyA.getAdvisees().findAt(i)<<endl;

  }

  Faculty facultyB("Dr. A", "lecturer", "Department of CPSC", 11002009);
  cout<<"faculty B profile"<<endl;
  cout<<"Name: "<<facultyB.getName()<<endl;
  cout<<"Level: "<<facultyB.getLevel()<<endl;
  cout<<"Department: "<<facultyB.getDepartment()<<endl;
  cout<<"ID: "<<facultyB.getPersonID()<<endl;

  if (facultyA == facultyB) {

    cout<<"Faculty A is the same faculty as faculty B."<<endl;

  }
  else {

    cout<<"Faculty A is not the same faculty as faculty B"<<endl;

  }

  cout<<endl;
  */
  FacultyTable facultyTable;
  facultyTable.setUpTable(facultyTable);
  facultyTable.printFaculty(facultyTable.getRoot());

  StudentTable studentTable;
  studentTable.setUpTable(studentTable);
  studentTable.printStudents(studentTable.getRoot());

  return 0;
}
