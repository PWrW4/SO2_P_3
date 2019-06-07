#include <string>
#include <vector>
#include "Room.hpp"

class Person;

class Classroom : public Room
{
public:
    Classroom(std::string name, int capacity);
    Classroom();
    ~Classroom();

    Person *professor;
    std::vector<Person*> students;



    int setProfessor(Person *professor);
    int freeProfessor();
    int addStudent(Person *student);
    int deleteStudent(Person *student);
};