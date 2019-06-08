#include <vector>
#include <iostream>
#include <algorithm>
#include "Room.hpp"
#include "Person.hpp"

using namespace std;

    Room::Room(std::string name, int capacity, RoomType type, vector <Person*> people)
    {
        this->name = name;
        this->capacity = capacity;
        this->type = type;
        this->people = people;
    }
	Room::Room(std::string name, int capacity, RoomType type)
    {
        this->name = name;
        this->capacity = capacity;
        this->type = type;
    }
    Room::Room(int capacity, RoomType type)
    {
        this->name = "room";
        this->capacity = capacity;
        this->type = type;
    }
    Room::Room() {}
	Room::~Room() {}

    int Room::addPerson(Person * person)
    {
        if(people.size()==capacity)
        {
            cout<<"brak miejsc w "<<name<<"!\n";
            return -1;
        }
        people.push_back(person);
        int result;
        if(person->type==PersonType::E_Student)
            result = addStudent(person);
        else
            result = addWorker(person);
        if(result<0)
            return result;
        else
            return 0;
    }

	int Room::delPerson(Person * person)
    {
        if(people.size()==0)
        {
            cout<<"nikogo nie ma w "<<name<<"!\n";
            return -1;
        }
        vector<Person*>::iterator it = find(people.begin(), people.end(),person);
        if(it == people.end() && people.back() != person)
        {
            cout<<"osoba nieobecna w "<<name<<"!\n";
            return -1;
        }
        people.erase(it);
        int result;
        if(person->type==PersonType::E_Student)
            result = deleteStudent(person);
        else
            result = deleteWorker(person);
        if(result<0)
            return result;
        else
            return 0;
        return 0;
    }

    int Room::addStudent(Person *student)
    {
        if(students.size()==capacity-1)
        {
            cout<<"brak miejsc dla studentow w"<<name<<"!\n";
            return -1;
        }
        students.push_back(student);
        return 0;
    }

    int Room::deleteStudent(Person *student)
    {
        if(students.size()==0)
        {
            cout<<"nie ma studentow w pomieszczeniu "<<name<<"!\n";
            return -1;
        }
        vector<Person*>::iterator it = find(students.begin(), students.end(), student);
        if(it == students.end() && students.back() != student)
        {
            cout<<"student nieobecny w "<<name<<"!\n";
            return -1;
        }
        students.erase(it);
        return 0;
    }

    int Room::addWorker(Person *worker)
    {
        if(workers.size()==capacity-1)
        {
            cout<<"brak miejsc dla pracownikow w"<<name<<"!\n";
            return -1;
        }
        workers.push_back(worker);
        return 0;
    }

    int Room::deleteWorker(Person *worker)
    {
        if(workers.size()==0)
        {
            cout<<"nie ma pracownikow w pomieszczeniu "<<name<<"!\n";
            return -1;
        }
        vector<Person*>::iterator it = find(workers.begin(), workers.end(), worker);
        if(it == workers.end() && workers.back() != worker)
        {
            cout<<"pracownik nieobecny w "<<name<<"!\n";
            return -1;
        }
        workers.erase(it);
        return 0;
    }

    void Room::Print()
    {
        cout<<name<<", "<<type<<", "<<capacity<<endl;
        PrintPeople();
    }
    
    void Room::PrintPeople()
    {
        cout<<"list of people in "<<name<<":\n";
        for(int i=0; i<people.size();i++)
        {
            cout<<people[i]<<endl;
        }
    }

    void Room::virtual_function(){}